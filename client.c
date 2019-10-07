/* Christopher Kane, jwi705
   Sarah Marynak, oos266
*/

#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SERVER_IP "69.61.103.44"
#define SERVER_PORT 7891
#define DATA_SIZE 99


int main(int argc, char *argv[]) {
  char outMessage[DATA_SIZE]; //the outgoing message, to be sent to the server
  char inMessage[DATA_SIZE]; //the incoming message, received from the server
  int sd, nBytes; //socket descriptor, number bytes received from the server
  struct sockaddr_in server; //the server address
  int returnCode; //the return value of sendto()
  int addrSize;
  
  //create the socket
  sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sd < 0) {
    printf("Failed to create socket: %s\n", strerror(errno));
    return -1;
  }
  
  //fill out server address structure
  server.sin_family = AF_INET;
  server.sin_port = htons(SERVER_PORT); // http uses port 80
  server.sin_addr.s_addr = inet_addr(SERVER_IP);
  memset(server.sin_zero, '\0', sizeof server.sin_zero); 
  
  addrSize = sizeof(server);
  
  //start loop to get message from user, send to server, and wait for response
  while(1) {
    //get the outgoing message
    printf("Message: ");
    fgets(outMessage, DATA_SIZE, stdin);
    outMessage[sizeof(outMessage)-1] = '\0'; //make it null-terminated
    printf("Outgoing message: %s\n", outMessage);
    
    //send the message using sendto(), and check the error return value
    returnCode = sendto(sd, (char *)outMessage, strlen(outMessage), MSG_CONFIRM, (struct sockaddr *)&server, addrSize);
    if(returnCode < 0) {
      printf("Failed to send message: %s\n", strerror(errno));
      return -1;
    }
    
    //receive and process the message from the server
    nBytes = recvfrom(sd, (char *) inMessage, DATA_SIZE, MSG_WAITALL, (struct sockaddr*) &server, &addrSize);
    
    if(nBytes > 0) {
      inMessage[nBytes] = '\0';
      printf("Server says: %s\n", inMessage);
      break;
    }
    else {
      printf("There was no reply from the server, please try again.\n"); 
    }
  }
  
  close(sd);

  return 0;
}
