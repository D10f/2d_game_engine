#include "Systems/debug_system.hpp"
#include "Components/box_collider.hpp"
#include "Components/transform_component.hpp"
#include "core/ecs/registry.hpp"

DebugSystem::DebugSystem()
{
    requireComponent<TransformComponent>();
    requireComponent<BoxColliderComponent>();
}

void DebugSystem::update(SDL_Renderer *renderer)
{
    for (const auto &entity : getEntities())
    {
        const auto &transform = entity.m_registry->getComponent<TransformComponent>(entity);
        const auto &boxCollider = entity.m_registry->getComponent<BoxColliderComponent>(entity);

        SDL_Rect rect = {static_cast<int>(transform.m_position.x), static_cast<int>(transform.m_position.y),
                         boxCollider.m_width, boxCollider.m_height};

        if (boxCollider.m_isColliding)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }

        SDL_RenderDrawRect(renderer, &rect);
    }
}
