#include "Systems/movement_system.hpp"
#include "Logger/Logger.hpp"
#include <memory>

MovementSystem::MovementSystem()
{
    requireComponent<TransformComponent>();
    requireComponent<RigidBodyComponent>();
}

void MovementSystem::update()
{
    for (const auto &entity : getEntities())
    {
        auto &transform = entity.m_registry->getComponent<TransformComponent>(entity);
        const auto &rigidBody = entity.m_registry->getComponent<RigidBodyComponent>(entity);

        transform.m_position.x += rigidBody.m_velocity.x;
        transform.m_position.y += rigidBody.m_velocity.y;

        Logger::log("Entity id(" + std::to_string(entity.getId()) + ") updated to position " +
                    std::to_string(transform.m_position.x) + ", " + std::to_string(transform.m_position.y) + ".");
    }
}
