#include "./entity_manager.h"

void Entity_Manager::clear_data() {
  for (auto& entity: entities) {
    entity->destroy();
  }
}

bool Entity_Manager::has_entities() {
  return entities.size() != 0;
}

void Entity_Manager::update(float delta_time) {
  for (auto& entity: entities) {
    entity->update(delta_time);
  }
}

void Entity_Manager::render() {
  for (auto& entity: entities) {
    entity->render();
  }
}

Entity& Entity_Manager::add_entity(std::string entity_name) {
  Entity *entity = new Entity(*this, entity_name);
  entities.emplace_back(entity);
  return *entity;
}

std::vector<Entity*> Entity_Manager::get_entities() const {
  return this->entities;
}

unsigned int Entity_Manager::get_entity_count() {
  return entities.size();
}

void Entity_Manager::print_entities() const {
  for (auto& entt: entities) {
    entt->get_info();
  }
}
