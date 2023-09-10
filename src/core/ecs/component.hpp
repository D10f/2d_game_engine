#ifndef _CORE_COMPONENT_H
#define _CORE_COMPONENT_H

#include <cstddef>
#include <cstdint>

class IComponent
{
  protected:
    inline static size_t m_nextId = 0;
};

template <typename TComponent> class Component : public IComponent
{
  public:
    static size_t getId()
    {
        static auto id = m_nextId++;
        return id;
    }
};

#endif
