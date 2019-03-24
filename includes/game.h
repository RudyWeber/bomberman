#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

enum states
{
  MAIN_MENU,
  JOIN_GAME,
  HOST_GAME,
  IN_GAME,
  OVER,
  CONFIRM_EXIT,
  EXIT
};

struct game
{
  unsigned int width;
  unsigned int height;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  enum states state;
  TTF_Font *font;
  SDL_bool inMenuKeyPressed;
};

void initGame(struct game *);
void destroyGame(struct game *);
char *gameStateToString(enum states);

#endif