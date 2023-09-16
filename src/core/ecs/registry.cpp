#include "core/ecs/registry.hpp"
#include "core/ecs/component.hpp"
#include "utils/pool.h"

Entity Registry::createEntity()
{
    uint32_t entityId = 0;

    if (m_freeIds.empty())
    {
        entityId = static_cast<int>(m_totalEntities++);

        if (entityId >= m_componentSignatures.size())
            m_componentSignatures.resize(entityId + 1);
    }
    else
    {
        entityId = m_freeIds.front();
        m_freeIds.pop_front();
    }

    Entity newEntity(static_cast<int>(entityId), this);
    m_addEntitiesBatch.insert(newEntity);
    /* newEntity.registry = this; */

    /* Logger::log("New entity created with id of: " + std::to_string(entityId)); */

    return newEntity;
}

void Registry::destroyEntity(Entity entity)
{
    m_removeEntitiesBatch.insert(entity);
}

void Registry::addEntityToSystems(Entity entity)
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

void Registry::removeEntityFromSystems(Entity entity)
{
    for (const auto &system : m_systems)
        system.second->removeEntity(entity);
}

void Registry::update()
{
    for (const auto entity : m_addEntitiesBatch)
        addEntityToSystems(entity);

    m_addEntitiesBatch.clear();

    for (const auto entity : m_removeEntitiesBatch)
    {
        const auto entityId = entity.getId();
        /* auto entitySignature = m_componentSignatures[entityId]; */

        /* int componentId = 0; */
        /* while (entitySignature.any()) */
        /* { */
        /*     if (entitySignature[componentId]) */
        /*     { */
        /*         auto componentPool = std::static_pointer_cast<Pool<IComponent>>(m_componentPools[componentId]); */
        /*         componentPool->unset(entityId); */
        /*         componentId = 0; */
        /*         continue; */
        /*     } */
        /*     componentId++; */
        /* } */

        removeEntityFromSystems(entity);
        m_freeIds.push_back(entityId);
        m_componentSignatures[entityId].reset();
    }

    m_removeEntitiesBatch.clear();
}
