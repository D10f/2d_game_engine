#include "Systems/keyboard_system.hpp"
#include "Components/keyboard_controlled_component.hpp"
#include "Components/rigid_body.hpp"
#include "Components/sprite_component.hpp"
#include "Logger/Logger.hpp"
#include "core/ecs/registry.hpp"
#include <SDL2/SDL_keyboard.h>

KeyboardMovementSystem::KeyboardMovementSystem()
{
    requireComponent<KeyboardControlledComponent>();

    // Should be optional. If made optional, check for existence first
    requireComponent<SpriteComponent>();
    requireComponent<RigidBodyComponent>();
}

void KeyboardMovementSystem::onKeyPress(KeyPressEvent &event)
{
    /* std::string keyCode = std::to_string(event.symbol); */
    /* Logger::log("KeyPress event emitted with key: " + keyCode + " " + SDL_GetKeyName(event.symbol)); */

    for (const auto &entity : getEntities())
    {
        const auto &keyboardControl = entity.m_registry->getComponent<KeyboardControlledComponent>(entity);
        auto &sprite = entity.m_registry->getComponent<SpriteComponent>(entity);
        auto &rigidBody = entity.m_registry->getComponent<RigidBodyComponent>(entity);

        switch (event.symbol)
        {
        case SDLK_UP:
        case SDLK_w:
            sprite.srcRect.y = static_cast<int>(0 * sprite.m_height);
            rigidBody.m_velocity.y = keyboardControl.m_upVelocity.y;
            rigidBody.m_velocity.x = keyboardControl.m_upVelocity.x;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            sprite.srcRect.y = static_cast<int>(1 * sprite.m_height);
            rigidBody.m_velocity.y = keyboardControl.m_rightVelocity.y;
            rigidBody.m_velocity.x = keyboardControl.m_rightVelocity.x;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            sprite.srcRect.y = static_cast<int>(2 * sprite.m_height);
            rigidBody.m_velocity.y = keyboardControl.m_downVelocity.y;
            rigidBody.m_velocity.x = keyboardControl.m_downVelocity.x;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            sprite.srcRect.y = static_cast<int>(3 * sprite.m_height);
            rigidBody.m_velocity.y = keyboardControl.m_leftVelocity.y;
            rigidBody.m_velocity.x = keyboardControl.m_leftVelocity.x;
            break;
        }
    }
}

void KeyboardMovementSystem::onKeyRelease(KeyReleaseEvent &event)
{
    /* std::string keyCode = std::to_string(event.symbol); */
    /* Logger::log("KeyPress event emitted with key: " + keyCode + " " + SDL_GetKeyName(event.symbol)); */

    for (const auto &entity : getEntities())
    {
        const auto &keyboardControl = entity.m_registry->getComponent<KeyboardControlledComponent>(entity);
        auto &sprite = entity.m_registry->getComponent<SpriteComponent>(entity);
        auto &rigidBody = entity.m_registry->getComponent<RigidBodyComponent>(entity);

        switch (event.symbol)
        {
        case SDLK_UP:
        case SDLK_RIGHT:
        case SDLK_DOWN:
        case SDLK_LEFT:
        case SDLK_w:
        case SDLK_d:
        case SDLK_s:
        case SDLK_a:
            rigidBody.m_velocity.y = 0;
            rigidBody.m_velocity.x = 0;
            break;
        }
    }
}

void KeyboardMovementSystem::subscribeToEvents(std::unique_ptr<EventBus> &eventBus)
{
    eventBus->SubscribeToEvent<KeyPressEvent>(this, &KeyboardMovementSystem::onKeyPress);
    eventBus->SubscribeToEvent<KeyReleaseEvent>(this, &KeyboardMovementSystem::onKeyRelease);
}

void KeyboardMovementSystem::update(float deltaTime)
{
}
