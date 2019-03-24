#include <stdio.h>
#include <stdlib.h>

#include "eventloop.h"
#include "log.h"
#include "setup.h"
#include "game.h"

int main(int argc, char *argv[])
{
  struct game game;

  initLibraries();
  initGame(&game);

  run(&game);

  destroyGame(&game);

  quitLibraries();

  return EXIT_SUCCESS;
}