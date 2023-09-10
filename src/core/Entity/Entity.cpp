#include "core/Entity/Entity.hpp"

Entity::Entity(int32_t id, Registry *registry) : m_id(id), m_registry(registry)
{
}

int32_t Entity::getId() const
{
    return m_id;
}
