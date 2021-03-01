
# include "client_server.h"



int main(int argc, char **argv){

  int count = 0;

  if(argc != 2){
    puts("Usage : ./server.o port");
    puts("example : ./server.o 400");
    exit(1);
  }

  // set the buffers and sockets
  int sockfd, received_bytes, sended_bytes;
  char buffer[1024], buffer_to_send[1024];

  // get the port  and set it in our structur
  struct configuration conf={atoi(argv[1])};
  struct configuration *confptr;
  confptr = &conf;

  // set the sockets
  struct sockaddr_in local_addr;
  struct sockaddr_in remote_addr;

  // init the socket fd
  sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  // check error 
  if(sockfd == -1){
    perror("Socket error ");
    return 1;
  }

  char tr = '1';

  if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&tr,sizeof(int)) == -1) {
    perror("Setsockopt ");
    exit(1);
  }

  // config
  local_addr.sin_family = AF_INET;
  local_addr.sin_port = htons(confptr->port);
  local_addr.sin_addr.s_addr = INADDR_ANY;
  memset(local_addr.sin_zero, '\0', sizeof(local_addr.sin_zero));

  // bind the socket fd created
  int local_bind = bind(sockfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr));
  if(local_bind == -1){
    perror("Bind error ");
    return 1;
  }


  printf("serveur starts... \n");
  int slen = sizeof(remote_addr);
  int mode_chat = 0;

  while(1){
    if (count == 0){
      greating(sended_bytes, received_bytes, sockfd, &buffer, &buffer_to_send, remote_addr, slen);
      count = 1;
    }
    else if (count == 1){
      printf("waiting for response... \n");
      if((received_bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&remote_addr, &slen)) == -1){
        perror("Recv ");
        exit(1);
      }
      buffer[received_bytes] = '\0';
      int choice = atoi(buffer);
      printf("Received choice : %s\n", buffer);
      if (choice == 1){

        strcpy(buffer_to_send, " OKey, let's chat then,: \
        \n if you want to quit, write : QUIT \n");

        if((sended_bytes = sendto(sockfd, buffer_to_send, strlen(buffer_to_send), 0, (struct sockaddr*) &remote_addr, slen)) == -1){
          perror("Send error ");
          exit(1);
        }
        buffer_to_send[sended_bytes] = '\0';
        while (mode_chat == 0){
          mode_chat = chat_op(sended_bytes, received_bytes, sockfd, &buffer, &buffer_to_send, remote_addr, slen);
        }
        mode_chat = 0;
        count = 0;
      }
      else if (choice == 2){

        strcpy(buffer_to_send, " OKey, give an Integer please : \n");

        if((sended_bytes = sendto(sockfd, buffer_to_send, strlen(buffer_to_send), 0, (struct sockaddr*) &remote_addr, slen)) == -1){
          perror("Send error ");
          exit(1);
        }
        buffer_to_send[sended_bytes] = '\0';
        prime_number(sended_bytes, received_bytes, sockfd, &buffer, &buffer_to_send, remote_addr, slen);
        count = 0;
      }
      else if (choice == 3){

        strcpy(buffer_to_send, " OKey, give an Integer please : \n");

        if((sended_bytes = sendto(sockfd, buffer_to_send, strlen(buffer_to_send), 0, (struct sockaddr*) &remote_addr, slen)) == -1){
          perror("Send error ");
          exit(1);
        }
        buffer_to_send[sended_bytes] = '\0';
        fact_number(sended_bytes, received_bytes, sockfd, &buffer, &buffer_to_send, remote_addr, slen);
        count = 0;
      }
      else{
        count = 5;
      }
    }

  }

  return 0;

}