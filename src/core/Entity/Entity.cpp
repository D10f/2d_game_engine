#include "core/Entity/Entity.hpp"

Entity::Entity(int32_t id) : m_id(id)
{
}

int32_t Entity::getId() const
{
    return m_id;
}
