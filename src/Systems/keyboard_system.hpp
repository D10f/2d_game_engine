#ifndef _KEYBOARD_MOVEMENT_SYSTEM_H
#define _KEYBOARD_MOVEMENT_SYSTEM_H

#include "Components/transform_component.hpp"
#include "Events/keypress_event.hpp"
#include "core/ecs/system.hpp"
#include "core/events/event_bus.hpp"

class KeyboardMovementSystem : public System
{
  private:
    void onKeyPress(KeyPressEvent &event);

  public:
    KeyboardMovementSystem() = default;

    void subscribeToEvents(std::unique_ptr<EventBus> &eventBus);

    void update(float deltaTime);
};

#endif
