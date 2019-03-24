#include "game.h"
#include "menu.h"
#include "eventloop.h"

void run(struct game *game)
{
  while (game->state != EXIT)
  {
    SDL_PollEvent(&(game->event));

    SDL_RenderClear(game->renderer);

    switch (game->state)
    {
    case MAIN_MENU:
      handleMenuEvents(&MainMenu, game);
      drawMenu(game, MainMenu);
      break;
    case CONFIRM_EXIT:
      handleMenuEvents(&ConfirmExitMenu, game);
      drawMenu(game, ConfirmExitMenu);
      break;
    default:
      break;
    }

    if (game->event.type == SDL_QUIT)
    {
      game->state = EXIT;
    }

    SDL_RenderPresent(game->renderer);
  }
}