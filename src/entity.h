#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "./entity_manager.h"
#include "./component.h"

class Entity_Manager;
class Component;

class Entity {

  private:
    Entity_Manager& manager;
    bool active;
    std::vector<Component*> components;
    std::map<const std::type_info*, Component*> component_type_map;

  public:
    std::string name;
    Entity(Entity_Manager& manager);
    Entity(Entity_Manager& manager, std::string name);
    void update(float delta_time);
    void render();
    void destroy();
    bool is_active() const;
    void get_info() const;

    template <typename T, typename... TArgs>
    T& add_component(TArgs&&... args) {
      T* new_component(new T(std::forward<TArgs>(args)...));
      new_component->owner = this;
      components.emplace_back(new_component);
      component_type_map[&typeid(*new_component)] = new_component;
      new_component->initialize();
      return *new_component;
    }

    template <typename T>
    T* get_component() {
      return static_cast<T*>(component_type_map[&typeid(T)]);
    }

    template <typename T>
    bool has_component() const {
      return component_type_map.count(&typeid(T));
    }
};

#endif
