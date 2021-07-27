#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./entity.h"
#include "./component.h"
#include "./entity_manager.h"

class Asset_Manager;

class Game {
  private:
    bool game_loop_running;
    SDL_Window *window;
  public:
    Game();
    ~Game();
    int last_frame_ticks{};
    static SDL_Renderer *renderer;
    static Asset_Manager* asset_manager;
    void load_level(int level);
    bool is_running() const;
    void initialize(int width, int height);
    void process_input();
    float calculate_delta_time();
    void update();
    void render();
    void destroy();
};

#endif
