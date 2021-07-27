#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <SDL2/SDL.h>
#include "../game.h"
#include "../entity_manager.h"
#include "../component.h"
#include "../../lib/glm/glm.hpp"

class Transform_Component: public Component {
  public:
    glm::vec2 pos;
    glm::vec2 vel;
    int width;
    int height;
    int scale;

    Transform_Component(int px, int py, int vx, int vy, int w, int h, int s);
    void initialize() override;
    void update(float delta_time) override;
    void render() override;
};

#endif
