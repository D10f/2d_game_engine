#ifndef _COLLISION_SYSTEM_H
#define _COLLISION_SYSTEM_H

#include "core/ecs/system.hpp"

class CollisionSystem : public System
{

  public:
    CollisionSystem();

    void update(float deltaTime);
};

#endif
