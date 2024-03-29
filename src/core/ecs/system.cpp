#include "core/ecs/system.hpp"
#include "Logger/Logger.hpp"
#include "core/ecs/entity.hpp"
#include <algorithm>

void System::addEntity(const Entity &entity)
{
    m_entities.push_back(entity);
}

void System::removeEntity(Entity entity)
{
    // This is the ... "modern" C++ way...
    /* m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), */
    /*                                 [&entity](Entity other) { return entity.getId() == other.getId(); }), */
    /*                  m_entities.end()); */

    for (auto entityAtIdx = m_entities.begin(); entityAtIdx != m_entities.end(); entityAtIdx++)
    {
        if (entityAtIdx->getId() == entity.getId())
        {
            m_entities.erase(entityAtIdx);
            break;
        }
    }
}

std::vector<Entity> System::getEntities() const
{
    return m_entities;
}

Signature System::getComponentSignature() const
{
    return m_componentSignature;
}
