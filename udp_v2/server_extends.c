#include "client_server.h"

char	*ft_strjoin(char const *dst, char const *src)
{
	char			*new;
	size_t			len_dst;
	size_t			len_src;
	register size_t	i;

	if (!src)
		return (NULL);
	len_dst = (dst ? strlen(dst) : 0);
	len_src = strlen(src);
	if (!(new = (char *)malloc((len_dst + len_src + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len_dst)
	{
		new[i] = dst[i];
		++i;
	}
	while (i < len_dst + len_src)
	{
		new[i] = src[i - len_dst];
		++i;
	}
	new[i] = '\0';
	return (new);
}

void greating(int sended_bytes, int received_bytes, int sockfd, char *buffer, char *buffer_to_send,struct sockaddr_in remote_addr, int slen)
{

    printf("waiting for response... \n");
    if((received_bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&remote_addr, &slen)) == -1){
      perror("Recv ");
      exit(1);
    }
    buffer[received_bytes] = '\0';
    printf("Received : %s\n", buffer);
    printf ("msg sent :)\n");

    strcpy(buffer_to_send, "Oh God, hello from mars to earth !! \
    \n please choose one of these options \
    \n 1 : chat simulation with the server \
    \n 2 : check if number is prime or not \
    \n 3 : factoriel of a number \n");

    if((sended_bytes = sendto(sockfd, buffer_to_send, strlen(buffer_to_send), 0, (struct sockaddr*) &remote_addr, slen)) == -1){
      perror("Send error ");
      exit(1);
    }
    buffer_to_send[sended_bytes] = '\0';
}


int chat_op(int sended_bytes, int received_bytes, int sockfd, char *buffer, char *buffer_to_send,struct sockaddr_in remote_addr, int slen){

  printf("waiting for response... \n");
    if((received_bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&remote_addr, &slen)) == -1){
      perror("Recv ");
      exit(1);
    }
    buffer[received_bytes] = '\0';
    printf("Received : %s\n", buffer);

    if (strcmp(buffer, "QUIT\n") == 0){
      printf("chat closed \n");
      strcpy(buffer_to_send, "0");

      if((sended_bytes = sendto(sockfd, buffer_to_send, strlen(buffer_to_send), 0, (struct sockaddr*) &remote_addr, slen)) == -1){
        perror("Send error ");
        exit(1);
      }
      buffer_to_send[sended_bytes] = '\0';
      return (1);
    }
    else{
      printf("Message : ");
      fgets(buffer_to_send, sizeof(buffer), stdin);

      if((sended_bytes = sendto(sockfd, buffer_to_send, strlen(buffer_to_send), 0, (struct sockaddr*) &remote_addr, slen)) == -1){
        perror("Send error ");
        exit(1);
      }
      buffer_to_send[sended_bytes] = '\0';
      return (0);
    }
}


void greating_2(int sended_bytes, int received_bytes, int sockfd, char *buffer, char *buffer_to_send,struct sockaddr_in remote_addr, int slen)
{

    strcpy(buffer_to_send, "Oh God, hello from mars to earth !! \
    \n please choose one of these options : \
    \n 1 : chat simulation with the server \
    \n 2 : check if number is prime or not : \
    \n 3 : factoriel of a number \n");

    if((sended_bytes = sendto(sockfd, buffer_to_send, strlen(buffer_to_send), 0, (struct sockaddr*) &remote_addr, slen)) == -1){
      perror("Send error ");
      exit(1);
    }
    buffer_to_send[sended_bytes] = '\0';
}


int isPrime(int num){
	int i,counter=0;
	for(i=2;i<num;i++)
    {
       if(num%i==0)
       {
           counter++;
       }    
    }     
    
    if(counter==0)
    {
        return (1);                  
    }
    else
    {
        return (0);
    }
}

int fact_recursive(int n)
{
	//Base Case
	if(n == 0)
	return 1;
	
	return (n *fact_recursive(n-1));
}

void prime_number(int sended_bytes, int received_bytes, int sockfd, char *buffer, char *buffer_to_send,struct sockaddr_in remote_addr, int slen)
{

  printf("waiting for response... \n");
    if((received_bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&remote_addr, &slen)) == -1){
      perror("Recv ");
      exit(1);
    }
    buffer[received_bytes] = '\0';
    printf("Received : %s\n", buffer);
    int number = atoi(buffer);
    printf ("number :%d: \n", number);
    if (isPrime(number) == 1){
        strcpy(buffer_to_send, "your number is a prime number \n ===== please press ENTER for a blank message ===== \n");
    }
    else{
        strcpy(buffer_to_send, "your number is not a prime number \n ===== please press ENTER for a blank message ===== \n");
    }

    if((sended_bytes = sendto(sockfd, buffer_to_send, strlen(buffer_to_send), 0, (struct sockaddr*) &remote_addr, slen)) == -1){
      perror("Send error ");
      exit(1);
    }
    buffer_to_send[sended_bytes] = '\0';

}


void fact_number(int sended_bytes, int received_bytes, int sockfd, char *buffer, char *buffer_to_send,struct sockaddr_in remote_addr, int slen)
{

  printf("waiting for response... \n");
    if((received_bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&remote_addr, &slen)) == -1){
      perror("Recv ");
      exit(1);
    }
    buffer[received_bytes] = '\0';
    printf("Received : %s\n", buffer);
    int number = atoi(buffer);
    int result = fact_recursive(number);
    char str[12];
    sprintf(str, "%d", result);
    char *dest = ft_strjoin("factoriel = ", str);
    dest = ft_strjoin(dest, "\n===== please press ENTER for a blank message =====\n");
    strcpy(buffer_to_send, dest);

    if((sended_bytes = sendto(sockfd, buffer_to_send, strlen(buffer_to_send), 0, (struct sockaddr*) &remote_addr, slen)) == -1){
      perror("Send error ");
      exit(1);
    }
    buffer_to_send[sended_bytes] = '\0';

}

