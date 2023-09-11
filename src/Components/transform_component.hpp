#ifndef _TRANSFORM_COMPONENT_H
#define _TRANSFORM_COMPONENT_H

#include "glm/glm.hpp"

class TransformComponent
{
  public:
    glm::vec2 m_position;
    glm::vec2 m_scale;
    double m_rotation;

    /* TransformComponent(glm::vec2 position, glm::vec2 scale, double rotation) */
    /*     : m_position(position), m_scale(scale), m_rotation(rotation){}; */

    TransformComponent(glm::vec2 position = glm::vec2(0, 0), glm::vec2 scale = glm::vec2(1, 1), double rotation = 0.0)
        : m_position(position), m_scale(scale), m_rotation(rotation){};
};

#endif
