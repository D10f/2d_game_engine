#include <iostream>
#include "./entity.h"

Entity::Entity(Entity_Manager& manager): manager(manager) {
  this->active = true;
}

Entity::Entity(Entity_Manager& manager, std::string name): manager(manager), name(name) {
  this->active = true;
}

void Entity::update(float delta_time) {
  for (auto& component: components) {
    component->update(delta_time);
  }
}

void Entity::render() {
  for (auto& component: components) {
    component->render();
  }
}

void Entity::destroy() {
  this->active = false;
}

bool Entity::is_active() const {
  return this->active;
}

void Entity::get_info() const {
  std::cout << "Entity Name: " << this->name << std::endl;
  for (auto component: components) {
    std::cout << component << std::endl;
  }
}
