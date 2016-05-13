#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define NUM 3

int doprocessing (int sock);

void *operation(void *port) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n, pid;

   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = *((int *) port);

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   unlink(INADDR_ANY);

   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }


   /* Now start listening for the clients, here
      * process will go in sleep mode and will wait
      * for the incoming connection
   */

   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
   printf("server is spawn for port %d\n", portno);

   struct sockaddr *id = 0;
   while (1) {
         int stop = doprocessing(newsockfd);
		 if (stop) break;
   } /* end of while */
   close(sockfd);
}

int main(int argc, char *argv[]) {
	if(argc < 4) {
		printf("You forget port No.\n");
		exit(0);
	}
	pthread_t thread[NUM];
	int port[NUM];
	int i;
	for(i = 0; i < NUM; i++) {
		port[i] = atoi(argv[i+1]);
		pthread_create(&thread[i], NULL, operation, (void*) &port[i]);
	}
	for(i = 0; i < NUM; i++) {
		pthread_join(thread[i], NULL);
	}
	return 0;
}

int doprocessing (int sock) {
   int n;
   char buffer[256];
   bzero(buffer,256);
   n = read(sock,buffer,255);

   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }

   printf("recieve %s",buffer);
   n = write(sock,"",18);
   if (!strcmp(buffer, "end\n")) {
	   printf("exiting\n");
	   return 1;
   }

   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   return 0;

}