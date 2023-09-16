#ifndef _CORE_REGISTRY_H
#define _CORE_REGISTRY_H

#include <cstdint>
#include <deque>
#include <memory>
#include <set>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Logger/Logger.hpp"
#include "core/ecs/component.hpp"
#include "core/ecs/system.hpp"
#include "utils/pool.h"

class Registry
{
  private:
    /**
     * Keeps track of the total number of entities added to the scene.
     */
    uint32_t m_totalEntities = 0;

    /**
     * Vector of pointers to a pool of components. Each pool contains a different
     * type of component.
     */
    std::vector<std::shared_ptr<IPool>> m_componentPools;

    /**
     * Vector of all the entity's component signatures. The index of the vector
     * is going to be the entity's id.
     */
    std::vector<Signature> m_componentSignatures;

    /**
     * Map of active systems, indexed by their type.
     */
    std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems;

    /**
     * Entities awaiting creation in the next call to update.
     */
    std::set<Entity> m_addEntitiesBatch;

    /**
     * Entities awaiting deletion in the next call to update.
     */
    std::set<Entity> m_removeEntitiesBatch;

    /**
     * List of entity ids that are free to reuse.
     */
    std::deque<uint32_t> m_freeIds;

  public:
    Registry() = default;

    void update();

    Entity createEntity();

    void destroyEntity(Entity entity);

    template <typename T, typename... TArgs> void addComponent(Entity entity, TArgs &&...args);

    template <typename T> void removeComponent(Entity entity);

    template <typename T> bool hasComponent(Entity entity) const;

    template <typename T> T &getComponent(Entity entity) const;

    template <typename T, typename... TArgs> std::shared_ptr<System> addSystem(TArgs... args);

    template <typename T> void removeSystem();

    template <typename T> bool hasSystem() const;

    template <typename T> T &getSystem() const;

    System addSystem();

    void addEntityToSystems(Entity entity);
    void removeEntityFromSystems(Entity entity);
};

template <typename T, typename... TArgs> void Registry::addComponent(Entity entity, TArgs &&...args)
{
    const auto componentId = Component<T>::getId();
    const auto entityId = entity.getId();

    if (componentId >= m_componentPools.size())
        m_componentPools.resize(componentId + 1, nullptr);

    if (!m_componentPools[componentId])
    {
        const auto newComponentPool = std::make_shared<Pool<T>>();
        m_componentPools[componentId] = newComponentPool;
    }

    const auto componentPool = std::static_pointer_cast<Pool<T>>(m_componentPools[componentId]);

    if (entityId >= componentPool->size())
        componentPool->resize(m_totalEntities);

    T newComponent = T(std::forward<TArgs>(args)...);

    componentPool->set(entityId, newComponent);

    m_componentSignatures[entityId].set(componentId);
}

/* template <typename TComponent, typename... TArgs> void Registry::addComponent(Entity entity, TArgs &&...args) */
/* { */
/*     const auto componentId = Component<TComponent>::getId(); */
/*     const auto entityId = entity.getId(); */

/*     if (componentId >= m_componentPools.size()) */
/*     { */
/*         m_componentPools.resize(componentId + 1, nullptr); */
/*     } */

/*     if (!m_componentPools[componentId]) */
/*     { */
/*         std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>(); */
/*         m_componentPools[componentId] = newComponentPool; */
/*     } */

/*     std::shared_ptr<Pool<TComponent>> componentPool = */
/*         std::static_pointer_cast<Pool<TComponent>>(m_componentPools[componentId]); */

/*     if (entityId >= componentPool->size()) */
/*     { */
/*         componentPool->resize(m_totalEntities); */
/*     } */

/*     /1* auto newComponent = *1/ */
/*     /1*     std::make_shared<TComponent>(std::forward<TArgs>(args)...); *1/ */

/*     TComponent newComponent(std::forward<TArgs>(args)...); */

/*     componentPool->set(entityId, newComponent); */

/*     m_componentSignatures[entityId].set(componentId); */
/* } */

template <typename T> void Registry::removeComponent(Entity entity)
{
    const auto componentId = Component<T>::getId();
    const auto entityId = entity.getId();
    m_componentSignatures[entityId].set(componentId, false);
}

template <typename T> bool Registry::hasComponent(Entity entity) const
{
    const auto componentId = Component<T>::getId();
    const auto entityId = entity.getId();
    return m_componentSignatures[entityId].test(componentId);
}

template <typename T> T &Registry::getComponent(Entity entity) const
{
    const auto componentId = Component<T>::getId();
    const auto entityId = entity.getId();
    auto componentPool = std::static_pointer_cast<Pool<T>>(m_componentPools[componentId]);
    return componentPool->get(entityId);
}

template <typename T, typename... TArgs> std::shared_ptr<System> Registry::addSystem(TArgs... args)
{
    std::shared_ptr<T> newSystem = std::make_shared<T>(std::forward<TArgs>(args)...);
    m_systems.insert(std::make_pair(std::type_index(typeid(T)), newSystem));
    /* why not -->> m_systems.insert(std::type_index(typeid(newSystem)),
     * newSystem); */
    return newSystem;
}

template <typename T> void Registry::removeSystem()
{
    const auto system = m_systems.find(std::type_index(typeid(T)));
    m_systems.erase(system);
}

template <typename T> bool Registry::hasSystem() const
{
    return (m_systems.find(std::type_index(typeid(T))) != m_systems.end());
    /* why not -->> (m_systems.find(std::type_index(typeid(T))) == nullptr) */
}

template <typename T> T &Registry::getSystem() const
{
    auto itrPtr = m_systems.find(std::type_index(typeid(T)));
    return *(std::static_pointer_cast<T>(itrPtr->second));
    /* why not -->> return m_systems.find(std::type_index(typeid(T)))->second; */
}

#endif
