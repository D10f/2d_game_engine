#ifndef _ANIMATION_COMPONENT_H
#define _ANIMATION_COMPONENT_H

#include <SDL2/SDL.h>
#include <cstdint>

class AnimationComponent
{
  public:
    uint32_t m_totalFrames;
    uint32_t m_currentFrame;
    uint32_t m_frameSpeedRate;
    uint32_t m_startTime;
    bool m_isLooping;

    AnimationComponent(uint32_t totalFrames = 1, uint32_t frameSpeedRate = 1, bool isLooping = true)
        : m_totalFrames(totalFrames), m_currentFrame(1), m_frameSpeedRate(frameSpeedRate), m_startTime(SDL_GetTicks()),
          m_isLooping(isLooping)
    {
    }
};

#endif
