#ifndef _CORE_SYSTEM_H
#define _CORE_SYSTEM_H

#include "core/Entity/Entity.hpp"
#include "core/ecs/component.hpp"
#include <bitset>
#include <vector>

const size_t MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

class System
{
  private:
    Signature m_componentSignature;
    std::vector<Entity> m_entities;

  public:
    System() = default;
    ~System() = default;

    void addEntity(const Entity &entity);
    void removeEntity(const Entity &entity);
    [[nodiscard]] std::vector<Entity> getEntities() const;
    [[nodiscard]] Signature getComponentSignature() const;
    template <typename TComponent> void requireComponent();
};

template <typename TComponent> void System::requireComponent()
{
    const auto componentId = Component<TComponent>::getId();
    m_componentSignature.set(componentId);
}

#endif
