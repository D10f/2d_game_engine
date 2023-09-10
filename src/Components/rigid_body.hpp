#ifndef _RIGID_BODY_COMPONENT_H
#define _RIGID_BODY_COMPONENT_H

#include "glm/glm.hpp"

class RigidBodyComponent
{
  public:
    glm::vec2 m_velocity;

    RigidBodyComponent(glm::vec2 velocity) : m_velocity(velocity)
    {
    }
};

#endif
