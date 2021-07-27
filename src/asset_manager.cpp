#include "./asset_manager.h"

Asset_Manager::Asset_Manager(Entity_Manager* manager) : manager(manager) {}

void Asset_Manager::clear_data() {
  textures.clear();
}

void Asset_Manager::add_texture(std::string texture_id, const char* filename) {
  textures.emplace(texture_id, Texture_Manager::load_texture(filename));
}

SDL_Texture* Asset_Manager::get_texture(std::string texture_id) {
  return textures[texture_id];
}
