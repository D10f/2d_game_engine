#ifndef _CORE_REGISTRY_H
#define _CORE_REGISTRY_H

#include "Logger/Logger.hpp"
#include "core/System/System.hpp"
#include "core/ecs/component.hpp"
#include "utils/pool.h"
#include <cstdint>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>

class Registry
{
  private:
    /**
     * Keeps track of the total number of entities added to the scene.
     */
    uint32_t m_totalEntities = 0;

    /**
     * Vector of pointers to a pool of components. Each pool contains a different type of component.
     */
    std::vector<IPool *> m_componentPools;

    /**
     * Vector of all the entity's component signatures. The index of the vector is going to be the entity's id.
     */
    std::vector<Signature> m_componentSignatures;

    /**
     * Map of active systems, indexed by their type.
     */
    std::unordered_map<std::type_index, System *> m_systems;

    /**
     * Entities awaiting creation in the next call to update.
     */
    std::set<Entity> m_addEntitiesBatch;

    /**
     * Entities awaiting deletion in the next call to update.
     */
    std::set<Entity> m_removeEntitiesBatch;

  public:
    Registry() = default;

    void update();

    Entity createEntity();

    template <typename T, typename... TArgs> void addComponent(Entity entity, TArgs &&...args);

    IComponent &getComponent(Entity entity) const;
    System addSystem();
    void addEntityToSystem(Entity entity);
};

template <typename T, typename... TArgs> void Registry::addComponent(Entity entity, TArgs &&...args)
{
    const auto componentId = Component<T>::getId();
    const auto entityId = entity.getId();
    const auto *componentPool = m_componentPools[componentId] || new Pool<T>();

    // Check if the component id is greater than the current size of component pools.
    if (componentId >= m_componentPools.size())
        m_componentPools.resize(componentId + 1, nullptr);

    // If a component pool does not exist for this component type.
    /* if (!m_componentPools[componentId]) */
    /* { */
    /*     auto *newComponentPool = new Pool<T>(); */
    /*     m_componentPools[componentId] = newComponentPool; */
    /* } */

    /* // Extract the pool for the current compnent type. */
    /* auto *componentPool = m_componentPools[componentId]; */

    if (!m_componentPools[componentId])
        m_componentPools[componentId] = componentPool;

    // Check if the entity id is greater than the current size of the component type's pool.
    if (entityId >= componentPool->size())
        componentPool->resize(m_totalEntities);

    // Create a new component, dynamically.
    T newComponent(std::forward<TArgs>(args)...);

    // Update the
    componentPool->set(entityId, newComponent);

    // Update the entity's component signature.
    m_componentSignatures[entityId].set(componentId);
}

#endif
