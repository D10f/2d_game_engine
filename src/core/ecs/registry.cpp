#include "core/ecs/registry.hpp"

Entity Registry::createEntity()
{
    auto entityId = static_cast<int>(m_totalEntities++);

    Entity newEntity(entityId, this);
    /* newEntity.registry = this; */

    m_addEntitiesBatch.insert(newEntity);

    if (entityId >= m_componentSignatures.size())
        m_componentSignatures.resize(entityId + 1);

    /* Logger::log("New entity created with id of: " + std::to_string(entityId)); */

    return newEntity;
}

void Registry::addEntityToSystem(Entity entity)
{
    const auto entityId = entity.getId();
    const auto &entityComponentsSignature = m_componentSignatures[entityId];

    for (const auto &system : m_systems)
    {
        const auto systemComponentSignature = system.second->getComponentSignature();

        if ((entityComponentsSignature & systemComponentSignature) == systemComponentSignature)
            system.second->addEntity(entity);

        /**
         *  the std::bitset has an == operator that compares all individual bits of
         * both bitsets, but we only want to check if the bits from the entity
         * signature match the ones from system signature, which would indicate that
         *  the system should handle this entity:
         *
         *  if (entityComponentsSignature == systemComponentSignature)
         *  system.second->addEntity(entity);
         */
    }
}

void Registry::update()
{
    for (const auto entity : m_addEntitiesBatch)
        addEntityToSystem(entity);

    m_addEntitiesBatch.clear();

    // TODO: Remove entities in batch
}
