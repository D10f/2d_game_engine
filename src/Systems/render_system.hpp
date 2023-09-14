#ifndef _RENDER_SYSTEM_H
#define _RENDER_SYSTEM_H

#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "core/assets/asset_store.h"
#include "core/ecs/registry.hpp"
#include "core/ecs/system.hpp"
#include <SDL2/SDL.h>
#include <memory>

class RenderSystem : public System
{
  public:
    RenderSystem();

    void update(SDL_Renderer *renderer, std::unique_ptr<AssetStore> &assetStore);
    void render(SDL_Renderer *renderer, SDL_Texture *texture, TransformComponent &transform, SpriteComponent &sprite);
};

#endif
