#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "game.h"
#include "server.h"

int makeServer(struct server *server)
{
  struct sockaddr_in serverAddress = {.sin_family = AF_INET, .sin_addr = {.s_addr = htonl(INADDR_ANY)}, .sin_port = htons(PORT)};

  if ((server->listenFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket");
    return -1;
  }

  if (bind(server->listenFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
  {
    perror("bind");
    return -1;
  }

  return 0;
}

int serverAccept(struct server *server)
{
  int connectionFd = 0;
  struct sockaddr_in clientAddress;
  socklen_t clientLength = sizeof(clientAddress);

  if ((connectionFd = accept(server->listenFd, (struct sockaddr *)&clientAddress, &clientLength)) == -1)
  {
    perror("accept");
    return -1;
  }

  printf("Client connected\n");

  return connectionFd;
}

void *runServer(void *voidGame)
{
  struct game *game = (struct game *)voidGame; // we will need the game later on
  struct server server = {0};
  int newConnectionFd = 0;

  makeServer(&server);

  if (listen(server.listenFd, MAX_CONNECTION) == -1)
  {
    perror("listen");
    return (void *)-1;
  }

  printf("Server listening...\n");

  for (;;)
  {
    if ((newConnectionFd = serverAccept(&server)) == -1)
    {
      fprintf(stderr, "shit\n");
      return (void *)-1;
    }

    if (server.numberOfClients < MAX_CONNECTION)
    {
      server.numberOfClients++;
      server.clientsFd[server.numberOfClients - 1] = newConnectionFd;
      printf("We should run a new thread handling client %d interactions\n", server.numberOfClients);
      fflush(stdout);
    }
    else
    {
      printf("No more connections allowed\nClosing all connections because why not...\n");
      fflush(stdout);
      if (close(newConnectionFd) == -1)
      {
        perror("close");
        return (void *)-1;
      }

      for (int i = 0; i < server.numberOfClients; i++)
      {
        printf("Closing client %d...\n", i + 1);
        if (close(server.clientsFd[i]) == -1)
        {
          perror("close");
          return (void *)-1;
        }
      }

      fflush(stdout);
      break;
    }
  }

  close(server.listenFd);
  game->isServer = SDL_FALSE;

  return (void *)0;
}