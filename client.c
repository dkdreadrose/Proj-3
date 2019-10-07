#include <sys/types.h>
#include <arps/inet.h>
#include <sys/socket.h>

#include "client.h"

#define SERVER_IP "000"
#define SERVER_PORT 00
#define DATA_SIZE 00


int main(int argc, char *argv[]) {
  char outMessage[99]; //the outgoing message, to be sent to the server
  char inMessage[255]; //the incoming message, received from the server
  
  //create the socket
  
  //fill out server address structure
  
  //get the outgoing message
  printf("Message: ");
  fgets(outMessage, 99, stdin);
  outMessage[sizeof(outMessage)-1] = '\0'; //make it null-terminated
  printf('Outgoing message: "%s"', outMessage);
  
  //send the message using sendto(), and check the eror return value
  
  //receive and process the message from the server
  
  return 0;
}
