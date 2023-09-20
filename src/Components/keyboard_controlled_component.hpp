#ifndef _KEYBOARD_CONTROLLED_COMPONENT_H
#define _KEYBOARD_CONTROLLED_COMPONENT_H

#include "glm/glm.hpp"
#include <SDL2/SDL.h>

class KeyboardControlledComponent
{
  public:
    glm::vec2 m_upVelocity;
    glm::vec2 m_rightVelocity;
    glm::vec2 m_downVelocity;
    glm::vec2 m_leftVelocity;

    KeyboardControlledComponent(glm::vec2 up = glm::vec2(0, 0), glm::vec2 right = glm::vec2(0, 0),
                                glm::vec2 down = glm::vec2(0, 0), glm::vec2 left = glm::vec2(0, 0))
        : m_upVelocity(up), m_rightVelocity(right), m_downVelocity(down), m_leftVelocity(left)
    {
    }
};

#endif
