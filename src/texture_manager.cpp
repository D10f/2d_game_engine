#include "./texture_manager.h"

// Calls SDL to load a resource (filename) and returns it as an Texture obj
SDL_Texture* Texture_Manager::load_texture(const char* filename){
  SDL_Surface* surface = IMG_Load(filename);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}

void Texture_Manager::draw(
  SDL_Texture* texture,
  SDL_Rect source_rect,
  SDL_Rect dest_rect,
  SDL_RendererFlip flip
) {
  SDL_RenderCopyEx(Game::renderer, texture, &source_rect, &dest_rect, 0.0, NULL, flip);
}
