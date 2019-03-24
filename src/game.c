#include <stdlib.h>

#include "game.h"
#include "log.h"

void initGame(struct game *game)
{
  SDL_Event event;

  game->width = DEFAULT_WIDTH;
  game->height = DEFAULT_HEIGHT;
  game->event = event;
  game->state = MAIN_MENU;
  game->inMenuKeyPressed = SDL_FALSE;

  if ((game->window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game->width, game->height, SDL_WINDOW_SHOWN)) == NULL)
  {
    logSDLError("Cannot create window");
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  if ((game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
  {
    logSDLError("Cannot create renderer");
    destroyGame(game);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
  SDL_RenderClear(game->renderer);

  SDL_RenderPresent(game->renderer);

  game->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 25);
}

void destroyGame(struct game *game)
{
  if (game->font != NULL)
  {
    TTF_CloseFont(game->font);
  }

  if (game->window != NULL)
  {
    SDL_DestroyWindow(game->window);
  }
}

char *gameStateToString(enum states state)
{
  switch (state)
  {
  case MAIN_MENU:
    return "main menu";
  case HOST_GAME:
    return "host game";
  case JOIN_GAME:
    return "join game";
  case IN_GAME:
    return "in game";
  case OVER:
    return "over";
  case CONFIRM_EXIT:
    return "confirm exit";
  case EXIT:
    return "exit";
  }
}