#ifndef _GAME_H
#define _GAME_H

#include "core/assets/asset_store.h"
#include "core/ecs/registry.hpp"
#include <SDL2/SDL.h>
#include <memory>

#define FPS 60
#define TARGET_FRAME_TIME 1000 / FPS

class Game
{
  private:
    bool m_isRunning;
    bool m_isDebugging;
    int32_t m_ticksLastFrame;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    std::shared_ptr<Registry> m_registry;
    std::unique_ptr<AssetStore> m_assetStore;

  public:
    size_t m_windowWidth;
    size_t m_windowHeight;

    Game();

    ~Game();

    void run();

    [[nodiscard]] bool isRunning() const;

    void setup();

    void loadLevel(uint8_t level);

    void processInput();

    void update();

    void render();
};

#endif
