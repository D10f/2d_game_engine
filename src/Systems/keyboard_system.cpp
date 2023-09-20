#include "Systems/keyboard_system.hpp"
#include "Events/keypress_event.hpp"
#include "Logger/Logger.hpp"
#include <SDL2/SDL_keyboard.h>

void KeyboardMovementSystem::onKeyPress(KeyPressEvent &event)
{
    std::string keyCode = std::to_string(event.symbol);
    Logger::log("KeyPress event emitted with key: " + keyCode + " " + SDL_GetKeyName(event.symbol));
}

void KeyboardMovementSystem::subscribeToEvents(std::unique_ptr<EventBus> &eventBus)
{
    eventBus->SubscribeToEvent<KeyPressEvent>(this, &KeyboardMovementSystem::onKeyPress);
}

void KeyboardMovementSystem::update(float deltaTime)
{
}
