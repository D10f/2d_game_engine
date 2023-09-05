#include "Game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

Game::Game() : m_isRunning(false), m_window(nullptr), m_renderer(nullptr), m_windowWidth(960), m_windowHeight(540)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }

    // Use this to properly set display window at fullscreen.
    // Note the call to SDL_SetWindowFullscreen below.
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    /* m_windowWidth = displayMode.w; */
    /* m_windowHeight = displayMode.h; */

    m_window = SDL_CreateWindow("Window Title Goes Here", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight), SDL_WINDOW_SHOWN);

    if (m_window == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (m_renderer == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
    }

    SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    /* SDL_RenderSetLogicalSize(m_renderer, static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight)); */
}

Game::~Game()
{
    std::cout << "Destructor called" << std::endl;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::run()
{
    m_isRunning = true;
    while (m_isRunning)
    {
        processInput();
        update();
        render();
    }
}

bool Game::isRunning() const
{
    return m_isRunning;
}

void Game::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                m_isRunning = false;
            break;
        }
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

void Game::update()
{
}
