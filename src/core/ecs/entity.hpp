#ifndef _CORE_ENTITY_H
#define _CORE_ENTITY_H

#include <cstdint>
#include <memory>

class Entity
{
  private:
    int32_t m_id;

  public:
    Entity(int32_t id, class Registry *registry);

    class Registry *m_registry;
    // Hold reference to the owner class (updated to be provided in constructor)
    /* class Registry *registry; */

    [[nodiscard]] int32_t getId() const;

    bool operator==(const Entity &other) const
    {
        return m_id == other.getId();
    }
    bool operator<(const Entity other) const
    {
        return m_id < other.getId();
    }
    bool operator>(const Entity other) const
    {
        return m_id > other.getId();
    }
};

#endif
