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
      drawMenu(MainMenu, game);
      break;
    case CONFIRM_EXIT:
      handleMenuEvents(&ConfirmExitMenu, game);
      drawMenu(ConfirmExitMenu, game);
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