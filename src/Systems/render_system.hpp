#ifndef _RENDER_SYSTEM_H
#define _RENDER_SYSTEM_H

#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "core/ecs/registry.hpp"
#include "core/ecs/system.hpp"
#include <SDL2/SDL.h>

class RenderSystem : public System
{
  public:
    RenderSystem();

    void update(SDL_Renderer *renderer);
};

#endif
