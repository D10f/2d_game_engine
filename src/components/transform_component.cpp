#include <iostream>
#include "./transform_component.h"

Transform_Component::Transform_Component(int px, int py, int vx, int vy, int w, int h, int s){
  pos = glm::vec2(px, py);
  vel = glm::vec2(vx, vy);
  width  = w;
  height = h;
  scale  = s;
}

void Transform_Component::initialize() {};

void Transform_Component::update(float delta_time) {
  pos.x += vel.x * delta_time;
  pos.y += vel.y * delta_time;
}

void Transform_Component::render() {
  // SDL_Rect transform_rect = {
  //   (int) pos.x,
  //   (int) pos.y,
  //   (int) width,
  //   (int) height
  // };
  // SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
  // SDL_RenderFillRect(Game::renderer, &transform_rect);
}
