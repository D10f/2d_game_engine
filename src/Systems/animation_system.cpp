#include "Systems/animation_system.hpp"
#include "Components/animation_component.hpp"
#include "Components/sprite_component.hpp"
#include "core/ecs/registry.hpp"

AnimationSystem::AnimationSystem()
{
    requireComponent<SpriteComponent>();
    requireComponent<AnimationComponent>();
}

void AnimationSystem::update(float /*deltaTime*/)
{
    for (const auto &entity : getEntities())
    {
        auto &sprite = entity.m_registry->getComponent<SpriteComponent>(entity);
        auto &animation = entity.m_registry->getComponent<AnimationComponent>(entity);

        /* if (!animation.m_isLooping) */
        /*     return; */

        auto timeRunning = SDL_GetTicks() * animation.m_frameSpeedRate / 1000.0;
        animation.m_currentFrame = static_cast<int>(timeRunning) % animation.m_totalFrames;

        /* animation.m_currentFrame = (animation.m_currentFrame + 1) % animation.m_totalFrames; */
        sprite.srcRect.x = static_cast<int>(animation.m_currentFrame * sprite.m_width);
    }
}
