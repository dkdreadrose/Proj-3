#include <sys/types.h>
#include <arps/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "client.h"

#define SERVER_IP "000"
#define SERVER_PORT 00
#define DATA_SIZE 00


int main(int argc, char *argv[]) {
  char outMessage[99]; //the outgoing message, to be sent to the server
  char inMessage[255]; //the incoming message, received from the server
  int sd; //socket descriptor
  struct sockaddr_in server; //the server address
  int rc; //return code (error if < 0)
  
  //create the socket
  sd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sd == -1) 
    errExit("Failed to create socket: %s", strerror(errno));
  
  //fill out server address structure
  server.sin_family = AF_INET;
  server.sin_port = htons(SERVER_PORT); // http uses port 80
  inet_pton(AF_INET, SERVER_IP, &(server.sin_addr.s_addr));
  
  //get the outgoing message
  printf("Message: ");
  fgets(outMessage, 99, stdin);
  outMessage[sizeof(outMessage)-1] = '\0'; //make it null-terminated
  printf('Outgoing message: "%s"', outMessage);
  
  //TODO send the message using sendto(), and check the eror return value
  
  //TODO receive and process the message from the server
  
  return 0;
}
