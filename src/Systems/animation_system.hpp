#ifndef _ANIMATION_SYSTEM_H
#define _ANIMATION_SYSTEM_H

#include "core/ecs/system.hpp"

class AnimationSystem : public System
{
  public:
    AnimationSystem();

    void update(float deltaTime);
};

#endif
