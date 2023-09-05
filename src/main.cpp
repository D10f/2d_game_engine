#include <Game.hpp>
#include <Logger.hpp>
#include <SDL2/SDL.h>

int main(int /*argc*/, char ** /*argv*/)
{
    Game game;

    game.run();

    /* Logger::log("This is a log message."); */
    /* Logger::error("This is an error message."); */
    /* Logger::warn("This is a warning."); */

    return 0;
}
