#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void logSDLError(char *message)
{
  fprintf(stderr, "%s: %s\n", message, SDL_GetError());
}

void logTTFError(char *message)
{
  fprintf(stderr, "%s: %s\n", message, TTF_GetError());
}