#include "Game/Game.hpp"
#include "Components/animation_component.hpp"
#include "Components/box_collider.hpp"
#include "Components/camera_follow_component.hpp"
#include "Components/keyboard_controlled_component.hpp"
#include "Components/rigid_body.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Events/key_press_event.hpp"
#include "Events/key_release_event.hpp"
#include "Logger/Logger.hpp"
#include "Systems/animation_system.hpp"
#include "Systems/camera_movement_system.hpp"
#include "Systems/collision_system.hpp"
#include "Systems/damage_system.hpp"
#include "Systems/debug_system.hpp"
#include "Systems/keyboard_system.hpp"
#include "Systems/movement_system.hpp"
#include "Systems/render_system.hpp"
#include "core/assets/asset_store.h"
#include "core/ecs/registry.hpp"
#include "glm/fwd.hpp"
#include "modules/map.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

size_t Game::m_windowWidth = 960;
size_t Game::m_windowHeight = 540;

Game::Game() : m_isRunning(false), m_isDebugging(true), m_window(nullptr), m_renderer(nullptr), m_ticksLastFrame(0)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Logger::error(SDL_GetError());
        return;
    }

    // Use this to properly set display window at fullscreen.
    /* SDL_DisplayMode displayMode; */
    /* SDL_GetCurrentDisplayMode(0, &displayMode); */
    /* m_windowWidth = displayMode.w; */
    /* m_windowHeight = displayMode.h; */

    m_window = SDL_CreateWindow("Window Title Goes Here", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight), SDL_WINDOW_SHOWN);

    if (m_window == nullptr)
    {
        Logger::error(SDL_GetError());
        SDL_Quit();
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (m_renderer == nullptr)
    {
        Logger::error(SDL_GetError());
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
    }

    // We can also force fullscreen window but scaling down the dimensions to a set width and height.
    // For that use a combination of SDL_SetWindowFullscreen and SDL_RenderSetLogicalSize.
    /* SDL_DisplayMode displayMode; */
    /* SDL_GetCurrentDisplayMode(0, &displayMode); */
    /* SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP); */
    /* SDL_RenderSetLogicalSize(m_renderer, static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight)); */

    m_registry = std::make_shared<Registry>();
    m_assetStore = std::make_unique<AssetStore>();
    m_eventBus = std::make_unique<EventBus>();
    m_camera.x = 0;
    m_camera.y = 0;
    m_camera.w = static_cast<int>(m_windowWidth);
    m_camera.h = static_cast<int>(m_windowHeight);

    setup();
}

Game::~Game()
{
    Logger::log("Destructor called");
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

            /* if (event.key.keysym.sym == SDLK_d) */
            /*     m_isDebugging = !m_isDebugging; */

            m_eventBus->EmitEvent<KeyPressEvent>(event.key.keysym.sym);

            break;

        case SDL_KEYUP:
            m_eventBus->EmitEvent<KeyReleaseEvent>(event.key.keysym.sym);
            break;
        }
    }
}

void Game::loadLevel(uint8_t level)
{
    m_registry->addSystem<MovementSystem>();
    m_registry->addSystem<RenderSystem>();
    m_registry->addSystem<DebugSystem>();
    m_registry->addSystem<AnimationSystem>();
    m_registry->addSystem<CollisionSystem>();
    m_registry->addSystem<DamageSystem>();
    m_registry->addSystem<KeyboardMovementSystem>();
    m_registry->addSystem<CameraFollowSystem>();

    // Subscribe to events, see comments on update fn below
    m_registry->getSystem<DamageSystem>().subscribeToEvents(m_eventBus);
    m_registry->getSystem<KeyboardMovementSystem>().subscribeToEvents(m_eventBus);

    // Add some assets
    m_assetStore->addTexture(m_renderer, "radar", "./assets/images/radar.png");
    m_assetStore->addTexture(m_renderer, "chopper-spritesheet", "./assets/images/chopper-spritesheet.png");
    m_assetStore->addTexture(m_renderer, "tank-image-right", "./assets/images/tank-panther-right.png");
    m_assetStore->addTexture(m_renderer, "truck-image-left", "./assets/images/truck-ford-left.png");
    m_assetStore->addTexture(m_renderer, "jungle-tilemap", "./assets/tilemaps/jungle.png");

    Map map = Map(m_registry, "jungle-tilemap", 32, 2.0);
    map.loadMap("./assets/tilemaps/jungle.map", 25, 20);

    // Create a few entities and components to them
    Entity radar = m_registry->createEntity();
    m_registry->addComponent<TransformComponent>(radar, glm::vec2(m_windowWidth - 74, 10.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->addComponent<RigidBodyComponent>(radar, glm::vec2(0.0, 0.0));
    m_registry->addComponent<SpriteComponent>(radar, "radar", 64, 64, 4);
    m_registry->addComponent<AnimationComponent>(radar, 8, 5, true);

    Entity chopper = m_registry->createEntity();
    m_registry->addComponent<TransformComponent>(chopper, glm::vec2(70.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->addComponent<RigidBodyComponent>(chopper, glm::vec2(40.0, 0.0));
    m_registry->addComponent<SpriteComponent>(chopper, "chopper-spritesheet", 32, 32, 3);
    m_registry->addComponent<AnimationComponent>(chopper, 2, 16, true);
    m_registry->addComponent<BoxColliderComponent>(chopper, 32, 32);
    m_registry->addComponent<KeyboardControlledComponent>(chopper, glm::vec2(0, -200), glm::vec2(200, 0),
                                                          glm::vec2(0, 200), glm::vec2(-200, 0));
    m_registry->addComponent<CameraFollowComponent>(chopper);

    Entity tank = m_registry->createEntity();
    m_registry->addComponent<TransformComponent>(tank, glm::vec2(400.0, 40.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->addComponent<RigidBodyComponent>(tank, glm::vec2(40.0, 0.0));
    m_registry->addComponent<SpriteComponent>(tank, "tank-image-right", 32, 32, 2);
    m_registry->addComponent<BoxColliderComponent>(tank, 32, 32);

    Entity truck = m_registry->createEntity();
    m_registry->addComponent<TransformComponent>(truck, glm::vec2(600.0, 80.0), glm::vec2(1.0, 1.0), 0.0);
    m_registry->addComponent<RigidBodyComponent>(truck, glm::vec2(-40.0, 0.0));
    m_registry->addComponent<SpriteComponent>(truck, "truck-image-left", 32, 32, 2);
    m_registry->addComponent<BoxColliderComponent>(truck, 32, 32);

    m_registry->destroyEntity(radar);
}

void Game::setup()
{
    loadLevel(1);
}

void Game::update()
{
    // number of milliseconds since the SDL library initialized
    int32_t currentFrameTicks = SDL_GetTicks();

    // Check if an artifical delay is required to paint at desired frame rate.
    int32_t timeToWait = TARGET_FRAME_TIME - (currentFrameTicks - m_ticksLastFrame);

    if (timeToWait > 0 && timeToWait < TARGET_FRAME_TIME)
        SDL_Delay(timeToWait);

    // Difference in ticks since last frame, in seconds
    float deltaTime = static_cast<float>((currentFrameTicks - m_ticksLastFrame)) / 1000.0F;

    // Contrain delta_time to a max value, and save variable
    /* delta_time = (delta_time > 0.05f) ? 0.05f : delta_time; */

    m_ticksLastFrame = currentFrameTicks;

    ///////////
    // Subscribe on every frame???

    // Reset all event handlers for every frame
    /* m_eventBus->clear(); */

    // Subscribe to events for all systems
    /* m_registry->getSystem<DamageSystem>().subscribeToEvents(m_eventBus); */

    ///////////

    m_registry->update();

    // Call systems that need update
    m_registry->getSystem<CameraFollowSystem>().update(m_camera);
    m_registry->getSystem<MovementSystem>().update(deltaTime);
    m_registry->getSystem<AnimationSystem>().update(deltaTime);
    m_registry->getSystem<CollisionSystem>().update(m_eventBus);
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // Draw PNG texture
    /* SDL_Surface *surface = IMG_Load("assets/images/tank-tiger-right.png"); */
    /* SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface); */
    /* SDL_FreeSurface(surface); */

    /* SDL_DestroyTexture(texture); */

    // Update all systems that need rendering
    m_registry->getSystem<RenderSystem>().update(m_renderer, m_assetStore, &m_camera);
    if (m_isDebugging)
        m_registry->getSystem<DebugSystem>().update(m_renderer);

    SDL_RenderPresent(m_renderer);
}
