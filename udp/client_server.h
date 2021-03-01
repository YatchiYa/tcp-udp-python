
#ifndef CLIENT_SERVER_H
# define CLIENT_SERVER_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

struct configuration {
  int     port;
  char**  list_adress_hist; // for a later try for multiple hosts
};

# endif