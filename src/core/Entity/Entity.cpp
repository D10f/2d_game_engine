#include "core/Entity/Entity.hpp"

Entity::Entity(uint32_t id) : m_id(id)
{
}

uint32_t Entity::getId() const
{
    return m_id;
}
