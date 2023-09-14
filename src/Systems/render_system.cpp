#include "Systems/render_system.hpp"
#include "Logger/Logger.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <algorithm>
#include <memory>
#include <unordered_map>

RenderSystem::RenderSystem()
{
    requireComponent<TransformComponent>();
    requireComponent<SpriteComponent>();
}

struct RenderObj
{
    TransformComponent *transform;
    SpriteComponent *sprite;
};

bool sortByLayerIdx(RenderObj &a, RenderObj &b)
{
    return a.sprite->m_zIndex < b.sprite->m_zIndex;
}

void RenderSystem::update(SDL_Renderer *renderer, std::unique_ptr<AssetStore> &assetStore)
{
    std::vector<RenderObj> deferredEntities;

    for (const auto &entity : getEntities())
    {
        auto &transform = entity.m_registry->getComponent<TransformComponent>(entity);
        auto &sprite = entity.m_registry->getComponent<SpriteComponent>(entity);

        if (sprite.m_zIndex > 1)
        {
            RenderObj deferredObj = {&transform, &sprite};
            deferredEntities.push_back(deferredObj);
            continue;
        }

        auto *texture = assetStore->getTexture(sprite.m_textureId);
        render(renderer, texture, transform, sprite);
    }

    std::sort(deferredEntities.begin(), deferredEntities.end(), &sortByLayerIdx);

    for (const auto &obj : deferredEntities)
    {
        auto *texture = assetStore->getTexture(obj.sprite->m_textureId);
        render(renderer, texture, *obj.transform, *obj.sprite);
    }
}

void RenderSystem::render(SDL_Renderer *renderer, SDL_Texture *texture, TransformComponent &transform,
                          SpriteComponent &sprite)
{
    SDL_Rect srcRect = sprite.srcRect;
    SDL_Rect dstRect = {static_cast<int>(transform.m_position.x), static_cast<int>(transform.m_position.y),
                        static_cast<int>(sprite.m_width * transform.m_scale.x),
                        static_cast<int>(sprite.m_height * transform.m_scale.y)};

    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, transform.m_rotation, nullptr, SDL_FLIP_NONE);
}
