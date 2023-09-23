#ifndef _CAMERA_MOVEMENT_SYSTEM_H
#define _CAMERA_MOVEMENT_SYSTEM_H

#include "core/ecs/system.hpp"
#include <SDL2/SDL_rect.h>

class CameraFollowSystem : public System
{
  public:
    CameraFollowSystem();

    void update(SDL_Rect &camera);
};

#endif
