#include "Systems/damage_system.hpp"
#include "Components/box_collider.hpp"
#include "Events/collision_event.hpp"
#include "Logger/Logger.hpp"
#include "core/ecs/entity.hpp"
#include "core/events/event_bus.hpp"
#include <utility>

DamageSystem::DamageSystem()
{
    requireComponent<BoxColliderComponent>();
}

void DamageSystem::onCollision(CollisionEvent &event)
{
    Logger::log("Collision detected between entities " + std::to_string(event.a.getId()) + " and " +
                std::to_string(event.b.getId()));

    event.a.m_registry->destroyEntity(event.a);
    event.b.m_registry->destroyEntity(event.b);
}

void DamageSystem::subscribeToEvents(std::unique_ptr<EventBus> &eventBus)
{
    eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
}

void DamageSystem::update()
{
}
