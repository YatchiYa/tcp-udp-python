#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#define ADRESS "127.0.0.1"

void recieveFile(int sockfd);

int main(int argc, char *argv[])
{
    system("clear");
    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[4096];
    struct sockaddr_in serv_addr;


    if(argc != 2){
        puts("Usage : ./client.o hostname");
        puts("example : ./client.o 127.0.0.1 \n");
        exit(1);
    }
    memset(recvBuff, '0', sizeof(recvBuff));

    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    char ip[100];

    /* Hostname to ip Starts here */
    // we try to select a list  of hostnames 
    struct hostent *he;
    struct in_addr **addr_list;

    // if we can't get the hostname like localhost or ip x.x.x.x
    if ((he = gethostbyname(argv[1])) == NULL)
    {
        herror("gethostbyname error :");
        return 1;
    }
    //# set the adress host list
    addr_list = (struct in_addr **) he->h_addr_list;

    // get the ip of each one
    for(int i = 0; addr_list[i] != NULL; i++)
    {
        strcpy(ip , inet_ntoa(*addr_list[i]) );
    }
    /* Initialize sockaddr_in data structure */
    //memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    serv_addr.sin_addr.s_addr = inet_addr(ip); 


    //serv_addr.sin_addr.s_addr = inet_addr(ip);

    /* Attempt a connection */
    if(connect(sockfd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    printf("Connected to ip: %s : %d\n",inet_ntoa(serv_addr.sin_addr),ntohs(serv_addr.sin_port));
    recieveFile(sockfd);
    close (sockfd);
    return 0;
}

void recieveFile(int sockfd)
{
    ssize_t total=0;
   	 /* Create file where data will be stored */
    FILE *fp;

    char filename[4096] = {0}; 
    if (recv(sockfd, filename, 4096, 0) == -1) 
    {
        perror("Can't receive filename");
        exit(-1);
    }

	//strcat(fname,"AK");
	printf("File Name: %s\n",filename);
	printf("Receiving file...");
   	fp = fopen(filename, "w"); 
    if(NULL == fp)
    {
        printf("Error opening file");
        exit(-1);
    }
    
    ssize_t n;
    char buff[4096] = {0};
    while ((n = recv(sockfd, buff, 4096, 0)) > 0) 
    {
	    total+=n;
        if (n == -1)
        {
            perror("Receive File Error");
            exit(1);
        }
        
        if (fwrite(buff, sizeof(char), n, fp) != n)
        {
            perror("Write File Error");
            exit(1);
        }
        memset(buff, 0, 4096);
    }
    
    if(total <= 0)
    {
        printf("\n Read Error \n");
    }
    else
        printf("\nFile OK....Completed\n");
}
