#include <stdlib.h>

#include "game.h"
#include "log.h"

void initLibraries()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    logSDLError("Cannot initialize SDL");
    exit(EXIT_FAILURE);
  }

  if (TTF_Init() == -1)
  {
    logTTFError("Cannot initialize TTF\n");
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
};

void quitLibraries()
{
  SDL_Quit();
  TTF_Quit();
}