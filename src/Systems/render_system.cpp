#include "Systems/render_system.hpp"
#include "Logger/Logger.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <memory>

RenderSystem::RenderSystem()
{
    requireComponent<TransformComponent>();
    requireComponent<SpriteComponent>();
}

void RenderSystem::update(SDL_Renderer *renderer, std::unique_ptr<AssetStore> &assetStore)
{
    for (const auto &entity : getEntities())
    {
        const auto &transform = entity.m_registry->getComponent<TransformComponent>(entity);
        const auto &sprite = entity.m_registry->getComponent<SpriteComponent>(entity);
        auto *texture = assetStore->getTexture(sprite.m_textureId);

        SDL_Rect srcRect = sprite.srcRect;
        SDL_Rect dstRect = {static_cast<int>(transform.m_position.x), static_cast<int>(transform.m_position.y),
                            static_cast<int>(sprite.m_width * transform.m_scale.x),
                            static_cast<int>(sprite.m_height * transform.m_scale.y)};

        SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, transform.m_rotation, nullptr, SDL_FLIP_NONE);
        /* SDL_Rect entityRect = {static_cast<int>(transform.m_position.x), static_cast<int>(transform.m_position.y), */
        /*                        static_cast<int>(sprite.m_width), static_cast<int>(sprite.m_height)}; */

        /* SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); */
        /* SDL_RenderFillRect(renderer, &entityRect); */

        /* Logger::log("Entity id(" + std::to_string(entity.getId()) + ") updated to position " + */
        /*             std::to_string(transform.m_position.x) + ", " + std::to_string(transform.m_position.y) + "."); */
    }
}
