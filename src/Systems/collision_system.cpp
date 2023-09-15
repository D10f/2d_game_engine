#include "Components/box_collider.hpp"
#include "Components/transform_component.hpp"
#include "Logger/Logger.hpp"
#include "Systems/collider_system.hpp"
#include "core/ecs/registry.hpp"
#include "utils/aabb_collision.hpp"
#include <string>

CollisionSystem::CollisionSystem()
{
    requireComponent<TransformComponent>();
    requireComponent<BoxColliderComponent>();
}

void CollisionSystem::update(float /*deltaTime*/)
{
    const auto &entities = getEntities();
    const auto totalSize = entities.size();

    /* for (const auto &entity : getEntities()) */
    /* for (int i = 0; i < totalSize; i++) */
    for (auto i = entities.begin(); i != entities.end(); i++)
    {
        const auto entityA = *i;
        const auto &transformA = entityA.m_registry->getComponent<TransformComponent>(entityA);
        auto &boxColliderA = entityA.m_registry->getComponent<BoxColliderComponent>(entityA);

        /* for (const auto &other : getEntities()) */
        /* for (int j = i + 1; j < totalSize; j++) */
        for (auto j = i + 1; j != entities.end(); j++)
        {
            const auto entityB = *j;
            const auto &transformB = entityB.m_registry->getComponent<TransformComponent>(entityB);
            auto &boxColliderB = entityB.m_registry->getComponent<BoxColliderComponent>(entityB);

            if (checkAABBCollision(transformA.m_position.x + boxColliderA.m_offset.x,
                                   transformA.m_position.y + boxColliderA.m_offset.y, boxColliderA.m_width,
                                   boxColliderA.m_height, transformB.m_position.x + boxColliderB.m_offset.x,
                                   transformB.m_position.y + boxColliderB.m_offset.y, boxColliderB.m_width,
                                   boxColliderB.m_height))
            {
                boxColliderA.m_isColliding = true;
                boxColliderB.m_isColliding = true;
                Logger::log("Collision between " + std::to_string(entityA.getId()) + "and " +
                            std::to_string(entityB.getId()));
            }
            else
            {
                boxColliderA.m_isColliding = false;
                boxColliderB.m_isColliding = false;
            }
        }
    }
}
