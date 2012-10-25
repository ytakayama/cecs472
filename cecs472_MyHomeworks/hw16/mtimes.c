//Yohei Takayama
//cecs472 homework16 10/29/2012
//mtimes.c
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "get_port.c"

int main(int argc, char* argv[])
{
  int s;
  struct sockaddr_in multiAddr;
  char msg[8] ;

  char *service = get_port();
  struct timeval tv;

  if ((s = socket(AF_INET, SOCK_DGRAM, 0))<0)
  {
    printf("couldn't get socket: %s\n", strerror(errno));
    return -1;
  };
  // Multicast to send to.
  multiAddr.sin_family = AF_INET;
  multiAddr.sin_port = htons(atoi(service));
  multiAddr.sin_addr.s_addr = inet_addr("224.0.1.2");


  while(1)
  {
  (void)gettimeofday(&tv, NULL);
  printf("tv_sec: %x\n", tv.tv_sec);
  printf("tv_usec: %x\n", tv.tv_usec);

  tv.tv_sec = htonl(tv.tv_sec);
  tv.tv_usec = htonl(tv.tv_usec);
  memcpy(&msg[0], &tv.tv_sec, 4);
  memcpy(&msg[4], &tv.tv_usec, 4);
  // Send
  if ( sendto(s, msg, sizeof(msg), 0, (struct sockaddr *)&multiAddr, sizeof(multiAddr)) < 0)
  {
    printf("sendto error: %s\n", strerror(errno));
    return -1;
  };
  printf("sent multicast\n");
  sleep(1);
  }// end of while

  return 0;
}
