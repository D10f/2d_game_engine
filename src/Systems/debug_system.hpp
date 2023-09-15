#ifndef _DEBUG_SYSTEM_H
#define _DEBUG_SYSTEM_H

#include "core/ecs/system.hpp"
#include <SDL2/SDL.h>

class DebugSystem : public System
{

  public:
    DebugSystem();

    void update(SDL_Renderer *renderer);
};

#endif
