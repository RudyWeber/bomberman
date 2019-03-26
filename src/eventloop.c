#include <pthread.h>

#include "game.h"
#include "menu.h"
#include "eventloop.h"
#include "server.h"

void run(struct game *game)
{
  pthread_t serverThread;
  SDL_bool serverStarted = SDL_FALSE;

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
    case HOST_GAME:
      if (!serverStarted)
      {
        printf("Creating server thread\n");
        pthread_create(&serverThread, NULL, runServer, game);
        serverStarted = SDL_TRUE;
      }
      break;
    default:
      break;
    }

    if (game->event.type == SDL_QUIT)
    {
      if (serverStarted)
      {
        pthread_cancel(serverThread);
        printf("Canceling server thread\n");
      }
      game->state = EXIT;
    }

    SDL_RenderPresent(game->renderer);
  }
}