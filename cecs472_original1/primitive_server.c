#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
int main(){
  int master, client, len; char message[80];
  struct sockaddr_in my_addr, his_addr;
  /* get a socket allocated */
  master = socket(PF_INET, SOCK_STREAM, 0);
  /* bind to the well-known port on our machine */
  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = INADDR_ANY;
  my_addr.sin_port = htons(7654);
  bind(master, (struct sockaddr *) &my_addr, sizeof(my_addr));
  listen(master, 5);
  len=sizeof(his_addr);
  /* get the connection to the client */
  client = accept(master, (struct sockaddr *) &his_addr, &len);
    /* get the message from the client */
  read(client,message,80);
  strcpy(message,"Server replies");
  write(client, message, 80); /* send reply */
  close(client);
  close(master);
  return 1;
}
