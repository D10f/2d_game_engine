#ifndef _COLLISION_EVENT_H
#define _COLLISION_EVENT_H

#include "core/ecs/entity.hpp"
#include "core/events/event.hpp"

class CollisionEvent : public Event
{
  public:
    Entity a;
    Entity b;

    CollisionEvent(Entity a, Entity b) : a(a), b(b)
    {
    }
};

#endif
