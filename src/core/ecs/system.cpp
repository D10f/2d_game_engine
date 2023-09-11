#include "core/System/System.hpp"
#include "core/Entity/Entity.hpp"
#include <algorithm>

void System::addEntity(const Entity &entity)
{
    m_entities.push_back(entity);
}

void System::removeEntity(const Entity &entity)
{
    // This is the ... "modern" C++ way...
    /* m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), */
    /*                                 [&entity](Entity other) { return entity.getId() == other.getId(); }), */
    /*                  m_entities.end()); */

    for (const auto &entityAtIdx = m_entities.begin(); entityAtIdx != m_entities.end();)
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
