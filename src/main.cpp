#include <Game/Game.hpp>
#include <Logger/Logger.hpp>
#include <SDL2/SDL.h>

int main(int /*argc*/, char ** /*argv*/)
{
    Game game;

    game.run();

    return 0;
}
