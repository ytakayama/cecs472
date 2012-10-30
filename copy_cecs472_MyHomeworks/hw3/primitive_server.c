//Yohei Takayama
//cecs472 Homework3 9/5/2012
//primitive_server.c

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

int main()
{
  int master, client, len; char message[80];
  struct sockaddr_in my_addr, his_addr;
  /* get a socket allocated */
  master = socket(PF_INET, SOCK_STREAM, 0);
  printf("master: %i\n",master);
  /* bind to the well-known port on our machine */
  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = INADDR_ANY;
  my_addr.sin_port = htons(7654);
  printf("bind: %i\n", bind(master, (struct sockaddr *) &my_addr, sizeof(my_addr)));
  printf("listen: %i\n", listen(master, 5));
  len = sizeof(his_addr);
  /* get the connection to the client */
  client = accept(master, (struct sockaddr *) &his_addr, &len);
  printf("client: %i\n", client);

  /* get the message from the client */
  printf("read1: %i\n", read(client, message, 80));
  printf("msg1: %s\n", message);
  strcpy(message,"Server replies");
  printf("write1: %i\n", write(client, message, 80));
  /* send reply */

  /* get the message from the client */
  printf("read2: %i\n", read(client,message,80));
  printf("msg2: %s\n", message);
  strcpy(message,"Reply 2");
  printf("write2: %i\n", write(client, message, 80));
  /* send reply2 */

  close(client);
  close(master);
  return 1;
}
