//Yohei Takayama
//cecs472 Homework4 9/10/2012

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

int main(int argc, char*argv[])
{
  // if number of argument is not equal to 5, print error message and exit.
  if(argc != 5)
  {
    printf("%s\n", "ERROR1: This program expects 5 arguments. The program terminates...");
    return 0;
  }

//===================================================================  
  struct hostent *hp, *hp2;
  struct in_addr addr;

  hp = gethostbyname(argv[1]);
  if(!hp)
    printf("%s\n", "ERROR2: The machine name is NULL...");
  else
  {
    printf("%s\n",hp->h_name); // should match with argv[1]
    printf("%d\n",hp->h_length); // should be 4
    memcpy(&addr, hp->h_addr, hp->h_length); // copyh_addr to addr
    printf("%x\n",ntohl(addr.s_addr)); // network to host-long ??
    printf("%s\n",inet_ntoa(addr)); // conver addr  to ascii ??
  }
//===================================================================
//  hp2 = gethostbyaddr(&addr, 4, AF_INET); 

{ // { doesn't do anything...just here.
  struct servent *sp, *sp2;

  sp = getservbyname(argv[2], "tcp");
  if(!sp)
    printf("%s\n", "ERROR2: The service name is NULL...");
  else
  {
    printf("%s\n",sp->s_name); /* telnet */
    printf("%d\n",ntohs(sp->s_port)); /* 23 */
    printf("%s\n",sp->s_proto); /* tcp */
  }

  sp2 = getservbyport(htons(atoi(argv[3])), "tcp");
  if(!sp2)
    printf("%s\n", "ERROR3: The port number of service is NULL...");
  else 
    printf("%s\n", sp2->s_name); //if argv[3] is 80 then should print http
} // } doesn't do anything...just here.
//==================================================================

  addr.s_addr = inet_addr(argv[4]);
  if(addr.s_addr == INADDR_NONE)
    printf("%s\n", "ERROR4: The internet number is bad format...");
  else
    hp2 = gethostbyaddr(&addr, 4, AF_INET);
    if(!hp2)
      printf("%s\n", "ERROR5: The internet number is NULL...");
    else
      printf("%s\n", hp2->h_name);
  return 0;
};

