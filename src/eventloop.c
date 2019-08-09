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

    if (game->event.type == SDL_KEYDOWN && game->event.key.keysym.sym == SDLK_ESCAPE) {
      game->state = MAIN_MENU;
    }

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
        game->isServer = SDL_TRUE;

        if (pthread_create(&serverThread, NULL, runServer, game) != 0)
        {
          fprintf(stderr, "Cannot create server thread\n");
          exit(EXIT_FAILURE);
        }

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