#ifndef _CORE_ENTITY_H
#define _CORE_ENTITY_H

#include <cstdint>

class Entity
{
  private:
    uint32_t m_id;

  public:
    Entity(uint32_t id);
    [[nodiscard]] uint32_t getId() const;

    bool operator==(const Entity &other) const
    {
        return m_id == other.getId();
    }
};

#endif
