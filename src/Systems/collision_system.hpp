#ifndef _COLLISION_SYSTEM_H
#define _COLLISION_SYSTEM_H

#include "core/ecs/system.hpp"
#include "core/events/event_bus.hpp"

class CollisionSystem : public System
{

  public:
    CollisionSystem();

    void update(std::unique_ptr<EventBus> &eventBus);
};

#endif
