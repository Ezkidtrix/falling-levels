#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/loader/Mod.hpp>
#include <math.h>

using namespace geode::prelude;

struct Settings {
  bool enabled = true;

  float fallSpeed = 0.5;
  float fallOffset = 100.0;
};
static Settings settings;

class $modify(GJBaseGameLayer) {
  void update(float dt) {
    GJBaseGameLayer::update(dt);
    if (!settings.enabled || m_isEditor || m_objects || m_player1) return;

    CCPoint playerPos = m_player1->getPosition();

    for (auto obj : CCArrayExt<GameObject*>(m_objects)) {
      CCPoint objPos = obj->getPosition();
      float distance = std::abs(std::min(0.0f, playerPos.x - objPos.x + settings.fallOffset));

      float newY = objPos.y + (distance * settings.fallSpeed);
      if (objPos.y == newY) continue;
      
      obj->setPositionY(newY);
    }
  }
};

$on_mod(Loaded) {
  settings.enabled = Mod::get()->getSettingValue<bool>("enabled");

  settings.fallSpeed = Mod::get()->getSettingValue<float>("fall-speed");
  settings.fallOffset = Mod::get()->getSettingValue<float>("fall-offset");

  listenForSettingChanges<bool>("enabled", [](bool value) {
    settings.enabled = value;
  });

  listenForSettingChanges<float>("fall-speed", [](float value) {
    settings.fallSpeed = value;
  });
  listenForSettingChanges<float>("fall-offset", [](float value) {
    settings.fallOffset = value;
  });
}