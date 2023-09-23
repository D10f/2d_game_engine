#include "Systems/camera_movement_system.hpp"
#include "Components/camera_follow_component.hpp"
#include "Components/transform_component.hpp"
#include "Game/Game.hpp"
#include "core/ecs/registry.hpp"
#include "modules/map.hpp"

CameraFollowSystem::CameraFollowSystem()
{
    requireComponent<TransformComponent>();
    requireComponent<CameraFollowComponent>();
}

void CameraFollowSystem::update(SDL_Rect &camera)
{
    for (const auto entity : getEntities())
    {
        auto &transform = entity.m_registry->getComponent<TransformComponent>(entity);

        if (transform.m_position.x + (camera.w / 2) < Map::m_width)
            camera.x = transform.m_position.x - (Game::m_windowWidth / 2);

        if (transform.m_position.y + (camera.h / 2) < Map::m_height)
            camera.y = transform.m_position.y - (Game::m_windowHeight / 2);

        // Keep camera rectangle view inside the screen limits
        camera.x = camera.x < 0 ? 0 : camera.x;
        camera.y = camera.y < 0 ? 0 : camera.y;
        camera.x = camera.x > camera.w ? camera.w : camera.x;
        camera.y = camera.y > camera.h ? camera.h : camera.y;
        /* camera.x = (camera.x + camera.w > Map::m_width) ? Map::m_width - camera.w : camera.x; */
        /* camera.y = (camera.y + camera.h > Map::m_height) ? Map::m_height - camera.h : camera.y; */
    }
}
