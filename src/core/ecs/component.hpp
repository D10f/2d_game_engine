#ifndef _CORE_COMPONENT_H
#define _CORE_COMPONENT_H

#include <cstdint>

class IComponent
{
  protected:
    static uint32_t m_nextId;
};

template <typename TComponent> class Component : public IComponent
{
    static uint32_t getId()
    {
        static auto id = m_nextId++;
        return id;
    }
};

#endif
