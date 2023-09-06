#ifndef _GAME_H
#define _GAME_H

#include <SDL2/SDL.h>

#define FPS 60
#define TARGET_FRAME_TIME 1000 / FPS

class Game
{
  private:
    bool m_isRunning;
    uint32_t m_ticksLastFrame;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

  public:
    size_t m_windowWidth;
    size_t m_windowHeight;

    Game();

    ~Game();

    void run();

    [[nodiscard]] bool isRunning() const;

    void processInput();

    void update();

    void render();
};

#endif
