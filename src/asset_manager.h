#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>
#include "./texture_manager.h"
#include "./entity_manager.h"

class Asset_Manager {
  private:
    Entity_Manager* manager;
    std::map<std::string, SDL_Texture*> textures; // maps a string with a texture
  public:
    Asset_Manager(Entity_Manager* manager);
    ~Asset_Manager();

    void clear_data();
    void add_texture(std::string texture_id, const char* filename);
    SDL_Texture* get_texture(std::string texture_id);
};

#endif
