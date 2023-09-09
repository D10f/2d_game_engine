#ifndef _TRANSFORM_COMPONENT_H
#define _TRANSFORM_COMPONENT_H

#include "glm/glm.hpp"

class TransformComponent
{
  public:
    glm::vec2 m_position;
    glm::vec2 m_scale;
    double m_rotation;

    TransformComponent(glm::vec2 position, glm::vec2 scale, double rotation)
        : m_position(position), m_scale(scale), m_rotation(rotation){};
};

#endif
