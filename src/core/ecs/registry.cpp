#include "core/ecs/registry.hpp"

Entity Registry::createEntity()
{
    uint32_t entityId = m_totalEntities++;

    Entity newEntity(entityId);

    m_addEntitiesBatch.insert(newEntity);

    Logger::log("New entity created with id of: " + std::to_string(entityId));

    return newEntity;
}

void Registry::addEntityToSystem(Entity entity)
{
}

void Registry::update()
{
    // TODO: Add entities in batch
    // TODO: Remove entities in batch
}
