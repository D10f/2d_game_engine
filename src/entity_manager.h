#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include "./entity.h"
#include "./component.h"

class Entity;

class Entity_Manager {
  private:
    std::vector<Entity*> entities;
  public:
    void clear_data();
    void update(float delta_time);
    void render();
    bool has_entities();
    Entity& add_entity(std::string entity_name);
    std::vector<Entity*> get_entities() const;
    unsigned int get_entity_count();

    void print_entities() const;
};

#endif
