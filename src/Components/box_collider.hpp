#ifndef _BOX_COLLIDER_COMPONENT_H
#define _BOX_COLLIDER_COMPONENT_H

#include "glm/glm.hpp"
#include <cstdint>

class BoxColliderComponent
{
  public:
    int32_t m_width;
    int32_t m_height;
    bool m_isColliding;
    glm::vec2 m_offset;

    BoxColliderComponent(int32_t width = 0, int32_t height = 0, glm::vec2 offset = glm::vec2(0))
        : m_width(width), m_height(height), m_offset(offset), m_isColliding(false)
    {
    }
};

#endif
