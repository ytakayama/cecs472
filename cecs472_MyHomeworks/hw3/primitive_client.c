//Yohei Takayama
//cecs472 Homework3 9/5/2012
//primitive_client.c

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

int main()
{
  int s;
  char message[80];
  struct sockaddr_in      srv_addr;
  /* Get a socket. */
  s = socket(PF_INET, SOCK_STREAM, 0);
  printf("socket: %i\n", s);
  /* Put server's address into a socket structure */
  memset(&srv_addr, 0, sizeof(srv_addr));
  srv_addr.sin_addr.s_addr = htonl(0x868bf831); 
  // gethostbyname "134.139.248.49"
  /*134.139.248.17*/
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(7654);
  /* Request the connection to the server */
  printf("connect: %i\n", connect(s, (struct sockaddr *) &srv_addr, sizeof(srv_addr)));
  
  strcpy(message,"Client speaks");
  /* Send a message to server*/
  printf("write1: %i\n", write(s, message, 80));
  /* Get server's reply*/
  printf("read1: %i\n", read(s, message, 80));
  printf("msg1: %s\n", message);

  strcpy(message,"Message 2");
  /* Send a message2 to server*/
  printf("write2: %i\n", write(s, message, 80));
  /* Get server's reply2*/
  printf("read2: %i\n", read(s, message, 80));
  printf("msg2: %s\n", message);

  close(s);
  return 1;
}
