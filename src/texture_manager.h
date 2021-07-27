#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "./game.h"

class Texture_Manager {
  public:
    static SDL_Texture* load_texture(const char* filename); // SDL expects C-style string
    static void draw(
      SDL_Texture* texture,
      SDL_Rect source_rect,
      SDL_Rect dest_rect,
      SDL_RendererFlip flip
    );
};

#endif
