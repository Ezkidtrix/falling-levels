#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

class $modify(GJBaseGameLayer) {
  void update(float dt) {
    GJBaseGameLayer::update(dt);

    CCArray* objects = this->m_objects;
    if (!objects) return;

    PlayerObject* player = this->m_player1;
    if (!player) return;

    CCPoint playerPos = player->getPosition();

    for (int i = 0; i < objects->count(); i++) {
      GameObject* obj = static_cast<GameObject*>(objects->objectAtIndex(i));
      if (!obj) continue;

      CCPoint objPos = obj->getPosition();
      
    }
  }
};