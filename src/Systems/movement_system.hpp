#ifndef _MOVEMENT_SYSTEM_H
#define _MOVEMENT_SYSTEM_H

#include "Components/rigid_body.hpp"
#include "Components/transform_component.hpp"
#include "core/ecs/registry.hpp"
#include "core/ecs/system.hpp"

class MovementSystem : public System
{
  public:
    MovementSystem();

    void update();
};

#endif
