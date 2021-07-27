#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
  public:
    Entity* owner;
    // ~Component();
    virtual void initialize(){};
    virtual void update(float){};
    virtual void render(){};
};

#endif
