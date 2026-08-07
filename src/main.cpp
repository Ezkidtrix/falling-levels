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

    if (!settings.enabled) return;
    if (LevelEditorLayer::get() != nullptr) return;

    CCArray* objects = this->m_objects;
    if (!objects) return;

    PlayerObject* player = this->m_player1;
    if (!player) return;

    CCPoint playerPos = player->getPosition();

    for (int i = 0; i < objects->count(); i++) {
      GameObject* obj = static_cast<GameObject*>(objects->objectAtIndex(i));
      if (!obj) continue;

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