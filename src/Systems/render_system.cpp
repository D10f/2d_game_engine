#include "Systems/render_system.hpp"
#include "Logger/Logger.hpp"
#include <memory>

RenderSystem::RenderSystem()
{
    requireComponent<TransformComponent>();
    requireComponent<SpriteComponent>();
}

void RenderSystem::update(SDL_Renderer *renderer)
{
    for (const auto &entity : getEntities())
    {
        const auto &transform = entity.m_registry->getComponent<TransformComponent>(entity);
        const auto &sprite = entity.m_registry->getComponent<SpriteComponent>(entity);

        SDL_Rect entityRect = {static_cast<int>(transform.m_position.x), static_cast<int>(transform.m_position.y),
                               static_cast<int>(sprite.m_width), static_cast<int>(sprite.m_height)};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &entityRect);

        /* Logger::log("Entity id(" + std::to_string(entity.getId()) + ") updated to position " + */
        /*             std::to_string(transform.m_position.x) + ", " + std::to_string(transform.m_position.y) + "."); */
    }
}
