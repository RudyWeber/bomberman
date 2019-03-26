#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 1337
#define MAX_CONNECTION 4

struct server
{
  int listenFd;
  int numberOfClients;
  int clientsFd[MAX_CONNECTION];
};

void *runServer(void *);

#endif