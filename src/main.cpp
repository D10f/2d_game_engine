#include "./constants.h"
#include "./game.h"

int main(int argc, char *args[]) {
  Game *game = new Game();

  game->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

  while (game->is_running()) {
    game->process_input();
    game->update();
    game->render();
  }

  game->destroy();

  return 0;
}
