/* Christopher Kane, jwi705
   Sarah Marynak, oos266
*/

#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define SERVER_IP "129.115.27.202"
#define SERVER_PORT 8080
#define DATA_SIZE 99


int main(int argc, char *argv[]) {
  char outMessage[DATA_SIZE]; //the outgoing message, to be sent to the server
  char inMessage[DATA_SIZE]; //the incoming message, received from the server
  int sd, nBytes, rc; //socket descriptor, number bytes received from the server, return code
  int commSd; //communication socket descriptor
  struct sockaddr_in local; //this server address
  struct sockaddr_in client; //the client address
  int returnCode; //the return value of sendto()
  int clientAddrSize;
  
  //create the socket
  sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sd < 0) {
    printf("Failed to create socket: %s\n", strerror(errno));
    return -1;
  }
  
  //fill out local address structure
  local.sin_family = AF_INET;
  local.sin_port = htons(SERVER_PORT); // http uses port 80
  local.sin_addr.s_addr = inet_addr(SERVER_IP);
  memset(local.sin_zero, '\0', sizeof local.sin_zero); 

  rc = bind(sd, (struct sockaddr *) &local, 
  			sizeof(local));
  if(rc < 0) {
	  printf("Failed to bind socket: %s\n", strerror(errno));
	  return -1;
  }

  printf("Socket bound.\n");
  printf("IP: %s, Port: %d\n", SERVER_IP, SERVER_PORT);
  
  //start loop to get message from user, send to server, and wait for response
  while(1) {
    //get the incoming message
    clientAddrSize = sizeof(struct sockaddr_in);
	
    //read message from client
	nBytes = recvfrom(sd, inMessage, DATA_SIZE, MSG_WAITALL, (struct sockaddr *) &client, &clientAddrSize);
    
    if(nBytes > 0) {
      inMessage[nBytes] = '\0';
      printf("Client says: %s\n", inMessage);
    }
    else if(nBytes == 0) {
      printf("There was no message from the client.\n"); 
    }
	else {
		printf("recvfrom failure: %s\n", strerror(errno));
		return -1;
	}

	strcpy(outMessage, inMessage);

	//send the message using sendto(), and check the error return value
    returnCode = sendto(sd, (char *)outMessage, DATA_SIZE, MSG_CONFIRM, (struct sockaddr *)&client, sizeof(client));
    if(returnCode < 0) {
      printf("Failed to send message: %s\n", strerror(errno));
      return -1;
    }
  }
  
  close(sd);

  return 0;
}

