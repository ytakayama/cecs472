#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
int main() {
  int s;
  char message[80];
  struct sockaddr_in      srv_addr;
  /* Get a socket. */
  s = socket(PF_INET, SOCK_STREAM, 0);
  /* Put server's address into a socket structure */
  memset(&srv_addr, 0, sizeof(srv_addr));
  srv_addr.sin_addr.s_addr = htonl(0x868bf811);
    /*134.139.248.17*/
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(7654);
  /* Request the connection to the server */
  connect(s, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
  strcpy(message,"Client speaks");
    /*Send a message to server*/
  write(s, message, 80);
    /*Get server's reply*/
  read(s, message, 80);
  close(s);
  return 1;
}
