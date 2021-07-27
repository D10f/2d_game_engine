#include <iostream>
#include "./constants.h"
#include "./game.h"
#include "./asset_manager.h"
#include "./components/transform_component.h"
#include "./components/sprite_component.h"
#include "./entity_manager.h"
#include "../lib/glm/glm.hpp"

Entity_Manager manager;
Asset_Manager* Game::asset_manager = new Asset_Manager(&manager);
SDL_Renderer* Game::renderer;

Game::Game() {
  this->game_loop_running = false;
}

Game::~Game() {}

bool Game::is_running() const {
  return this->game_loop_running;
}

void Game::initialize(int width, int height) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error during initialization" << std::endl;
    return;
  }

  // char* title, int x, int y, int w, int h, Uint32 flags
  window = SDL_CreateWindow(
    "This is the title",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    width,
    height,
    SDL_WINDOW_RESIZABLE
  );

  if (!window) {
    std::cerr << "Error during creation of the window" << std::endl;
    return;
  }

  // SDL_Window window, int index, Uint32 flags
  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    std::cerr << "Error during creation of the renderer" << std::endl;
    return;
  }

  load_level(0);

  game_loop_running = true;

  return;
}

void Game::load_level(int level) {

  /* Load assets, and add them onto the asset manager */
  std::string tank_image = "./assets/images/tank-big-right.png";
  std::string heli_image = "./assets/images/chopper-spritesheet.png";

  Game::asset_manager->add_texture("tank-image", tank_image.c_str());
  Game::asset_manager->add_texture("heli-image", heli_image.c_str());

  /* Add entities onto the entity manager */
  Entity& tank(manager.add_entity("tank"));
  tank.add_component<Transform_Component>(0, 0, 20, 20, 32, 32, 1);
  tank.add_component<Sprite_Component>("tank-image");

  Entity& helicopter(manager.add_entity("helicopter"));
  helicopter.add_component<Transform_Component>(240, 100, 0, 0, 32, 32, 1);
  helicopter.add_component<Sprite_Component>("heli-image");
  // helicopter.add_component<Sprite_Component>("heli-image", 2, 90, true, false);

  /*
  int total = std::rand() % 6 + 1;
  for (int i = 1; i <= total; i++) {
    int px = std::rand() % WINDOW_WIDTH;
    int py = std::rand() % WINDOW_HEIGHT;
    int vx = std::rand() % 100 - 50;
    int vy = std::rand() % 100 - 50;
    std::string name = "Particle-" + std::to_string(i);

    Entity& new_entity(manager.add_entity(name));
    new_entity.add_component<Transform_Component>(px, py, vx, vy, 24, 24, 1);
  }

  manager.print_entities();
  */
}

void Game::process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      game_loop_running = false; break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        game_loop_running = false;
      }
    break;
  }
}

float Game::calculate_delta_time() {
  // number of milliseconds since the SDL library initialized
  int current_frame_ticks = SDL_GetTicks();

  // Check if an "artifical delay" is required to reach the desired time to
  // paint the next frame (TARGET_FRAME_TIME or ~16.67ms)
  int time_to_wait = TARGET_FRAME_TIME - (current_frame_ticks - last_frame_ticks);
  if (time_to_wait > 0 && time_to_wait < TARGET_FRAME_TIME) {
    SDL_Delay(time_to_wait);
  }

  // Calculate delta time: difference in ticks since last frame in seconds
  float delta_time = (current_frame_ticks - last_frame_ticks) / 1000.0f;

  // Contrain delta_time to a max value, and save variable
  delta_time = (delta_time > 0.05f) ? 0.05f : delta_time;

  // Set the new ticks of the current frame, to be used in the next
  last_frame_ticks = current_frame_ticks;

  return delta_time;
}

void Game::update() {

  float delta_time = this->calculate_delta_time();

  // TODO: call entity_manager to update all entities
  manager.update(delta_time);
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);

  // Clear the back buffer
  SDL_RenderClear(renderer);

  // TODO: Call entity_manager to render all entities
  if (!manager.has_entities()) {
    return;
  }

  manager.render();

  // Swap the back and front buffers
  SDL_RenderPresent(renderer);
}

void Game::destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
