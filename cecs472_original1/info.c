/*
  Start file for homework. This is just clips from the lectures.
  I added the correct includes and a set of {}s so it would
  compile. You need to do the rest of the work.
*/
#include <sys/types.h> /* u_long */
#include <netdb.h> /* getXbyY */
#include <netinet/in.h> /*htons*/
#include <stdio.h> /*printf*/
#include <string.h> /*memcpy*/
#include <arpa/inet.h> /*inet_ntoa*/
int main()
{
  struct hostent *hp, *hp2;
  struct in_addr addr;
  hp = gethostbyname("cheetah.cecs.csulb.edu");
  printf("%s\n",hp->h_name);
  printf("%d\n",hp->h_length);
  memcpy(&addr, hp->h_addr, hp->h_length);
  printf("%x\n",ntohl(addr.s_addr));
  printf("%s\n",inet_ntoa(addr));
  hp2 = gethostbyaddr(&addr, 4, AF_INET);

  {
  struct servent *sp, *sp2;
  sp = getservbyname("telnet", "tcp");
  printf("%s\n",sp->s_name); /* telnet */
  printf("%d\n",ntohs(sp->s_port)); /* 23 */
  printf("%s\n",sp->s_proto); /* tcp */
  sp2 = getservbyport(htons(23), "tcp");
  }
  return 0;
};

