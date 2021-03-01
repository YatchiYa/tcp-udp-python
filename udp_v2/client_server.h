
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

void greating(int sended_bytes, int received_bytes, int sockfd, char *buffer, char *buffer_to_send,struct sockaddr_in remote_addr, int slen);
int chat_op(int sended_bytes, int received_bytes, int sockfd, char *buffer, char *buffer_to_send,struct sockaddr_in remote_addr, int slen);
void greating_2(int sended_bytes, int received_bytes, int sockfd, char *buffer, char *buffer_to_send,struct sockaddr_in remote_addr, int slen);
void prime_number(int sended_bytes, int received_bytes, int sockfd, char *buffer, char *buffer_to_send,struct sockaddr_in remote_addr, int slen);
void fact_number(int sended_bytes, int received_bytes, int sockfd, char *buffer, char *buffer_to_send,struct sockaddr_in remote_addr, int slen);
# endif