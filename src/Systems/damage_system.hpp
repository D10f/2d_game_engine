#ifndef _DAMAGE_SYSTEM_H
#define _DAMAGE_SYSTEM_H

#include "Events/collision_event.hpp"
#include "core/ecs/registry.hpp"
#include "core/ecs/system.hpp"
#include "core/events/event_bus.hpp"

class DamageSystem : public System
{
  private:
    Registry *m_registry;
    void onCollision(CollisionEvent &event);

  public:
    DamageSystem();

    void subscribeToEvents(std::unique_ptr<EventBus> &eventBus);

    void update();
};

#endif
