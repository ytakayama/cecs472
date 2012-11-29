//Yohei Takayama
//cecs472 Homework15 10/24/2012
//btimec.c

/* UDPtime.c - main */
#include <sys/types.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include "get_port.c"

#define BUFSIZE 64

//#define UNIXEPOCH       2208988800UL      /* UNIX epoch, in UCT secs      */
#define MSG             "what time is it?\n"

#include "connectUDP.c"
/*  handled by the include
 * int     connectUDP(const char *host, const char *service);
 * int     errexit(const char *format, ...);
 */

/*------------------------------------------------------------------------
 * main - UDP client for TIME service that prints the resulting time
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
    char    *host = "localhost";    /* host to use if none supplied */
    char    *service = get_port();      /* default service name         */
//    time_t  now;                    /* 32-bit integer to hold time  */
    char    now[8];
    int     s, n, m;                   /* socket descriptor, read count*/

    struct timeval tv;
    int One = 1;
    struct sockaddr_in fsin, fsin_him;
    int alen;
    char out_buf[8];
    alen = sizeof(fsin_him);
    //from homework 12
    int nfds;
    fd_set afds, rfds;    

    switch (argc)
    {
        case 1:
            break;
        case 3:
            service = argv[2];
            /* FALL THROUGH */
        case 2:
            host = argv[1];
            break;
        default:
            fprintf(stderr, "usage: UDPtime [host [port]]\n");
            exit(1);
    }

    /* get socket */
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    /* eanable broadcat */
    setsockopt(s, SOL_SOCKET, SO_BROADCAST, &One, sizeof(One));
    FD_ZERO(&afds);
    FD_SET(s, &afds);
    FD_SET(0, &afds);
    nfds = s+1;

    fsin.sin_family = AF_INET;
    fsin.sin_port = htons(atoi(service));
    fsin.sin_addr.s_addr = INADDR_BROADCAST;

    while(1)
    {
       memcpy(&rfds, &afds, sizeof(rfds));
       m = select(nfds, &rfds, NULL, NULL, NULL);
       if(m < 0)
	       errexit("select: %s\n", strerror(errno));
       if(FD_ISSET(0,&rfds))
       {
	  fgets(out_buf, 8, stdin);
	  if(out_buf[0] == 'q')
	      exit(0);
	  if(out_buf[0] == 'b')
	  {
   	      /* send broadcast */
   	      sendto(s, " ", 1, 0, (struct sockaddr *)&fsin, sizeof(fsin));
	   }
       }

       if(FD_ISSET(s, &rfds))
       {
           /* get first reply */
            recvfrom(s, &now, sizeof(now), 0, (struct sockaddr * )&fsin_him, &alen);

            memcpy(&tv.tv_sec, &now[0], 4);
            memcpy(&tv.tv_usec, &now[4], 4);

            tv.tv_sec = ntohl(tv.tv_sec);
            tv.tv_usec = ntohl(tv.tv_usec);

            printf("addr: %s\n", inet_ntoa(fsin_him.sin_addr)); 
            printf("tv_sec: %x\n", tv.tv_sec);
            printf("tv_usec: %x\n", tv.tv_usec);
            //    now = ntohl((u_long)now);       /* put in host byte order       */
            //    now -= UNIXEPOCH;               /* convert UCT to UNIX epoch    */
            printf("%s\n", ctime(&tv.tv_sec));
       }
    }// end of while loop


    exit(0);

}
