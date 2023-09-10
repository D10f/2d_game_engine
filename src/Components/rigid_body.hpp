#ifndef _RIGID_BODY_COMPONENT_H
#define _RIGID_BODY_COMPONENT_H

#include "glm/glm.hpp"

class RigidBodyComponent
{
  public:
    glm::vec2 m_velocity;

    RigidBodyComponent(glm::vec2 velocity = glm::vec2(0, 0)) : m_velocity(velocity)
    {
    }
};

#endif
