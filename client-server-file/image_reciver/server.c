#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>


char fname[100];

// définir le prototype de la fonction
void* SendFileToClient(int *arg);



int main(int argc, char *argv[])
{
    system("clear");
    // Initialisation des variables
    int connfd = 0,err;
    
    // Initialisation et déclaration d'un thread dont l'identifiant est "tid"
    pthread_t tid;
    
    
    struct sockaddr_in serv_addr;
    struct sockaddr_in c_addr;
    int listenfd = 0,ret;
    char sendBuff[1024];
    
    int numrv;
    
    size_t clen=0;
	
	// Création d'une socket "listenfd"
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(listenfd == -1)
	{
	  printf("Error in socket creation\n");
	  exit(1);
	}

    printf("Socket created successfully \n");

    //memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;// adresse du server 
    //serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(5000);
    memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));
   

    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));


    listen(listenfd, 5);
	printf("[+]Sever Listening...\n");
	
    // récupération du fichier à envoyer (forcément il est dans le répertoire e server.c)
    // dans notre cas, on considère que le fichier existe
    if (argc < 2) 
    {	
            printf("Enter file name to send: ");
            gets(fname);
    }
    else
        strcpy(fname,argv[1]);

    while(1)
    {
    	// tant que je reçois une connexion de la part du client
        clen=sizeof(c_addr);
        printf("Waiting...\n");
        connfd = accept(listenfd, (struct sockaddr*)&c_addr,&clen);

        
        /*        if(connfd<0)
                {
            printf("Error in accept\n");
            continue;	
            }*/
        // Utilisation de thread , avec comme argument la nouvelle socket
        err = pthread_create(&tid, NULL, &SendFileToClient, &connfd);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
    }
    close(connfd);
    return 0;
}



void* SendFileToClient(int *arg)
{
    ssize_t total=0;
    int connfd=(int)*arg;
    
    // envoi du contenu "fname" dans socket connfd
    //write(connfd, fname,1024);

    char *filename = basename(fname); 
    char buff[1024] = {0};
    strncpy(buff, filename, strlen(filename));
    if (send(connfd, buff, 1024, 0) == -1)
    {
        perror("Can't send filename");
        exit(1);
    }

    FILE *fp = fopen(fname,"rb");
    if(fp==NULL)
    {
        printf("File opern error");
        //return 1;   
    }   

    /* Read data from file and send it */
    
    int n; 
    char sendline[4096] = {0}; 
    while ((n = fread(sendline, sizeof(char), 4096, fp)) > 0) 
    {
        total+=n;
        if (n != 4096 && ferror(fp))
        {
            perror("Read File Error");
            exit(1);
        }
        
        if (send(connfd, sendline, n, 0) == -1)
        {
            perror("Can't send file");
            exit(1);
        }
        memset(sendline, 0, 4096);
    }
        
    printf("Closing Connection for id: %d\n",connfd);
    close (fp);
    close(connfd);
}