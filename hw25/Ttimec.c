//Yohei Takayama
//cecs472 Homework8 9/24/2012
//Ttimec.c

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

#include "connectTCP.c"
/*  handled by the include
 * int     connectUDP(const char *host, const char *service);
 * int     errexit(const char *format, ...);
 */

/*------------------------------------------------------------------------
 * main - TCP client for TIME service that prints the resulting time
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{//Yohei Takayama
//cecs472 Homework7 9/19/2012
    char    *host = "localhost";    /* host to use if none supplied */
    char    *service = get_port();      /* default service name         */
//    time_t  now;                    /* 32-bit integer to hold time  */
    char    now[8];
    int     socket, n;                   /* socket descriptor, read count*/

    int	   inchars;
    struct timeval tv;

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

    socket = connectTCP(host, service);

//    (void) write(socket, MSG, strlen(MSG));

    for(inchars = 0; inchars < 8; inchars += n)
    {
   	 /* Read the time */
    	n = read(socket, (char *)&now, sizeof(now));
   	 if (n < 0)
        	errexit("read failed: %s\n", strerror(errno));
    }
    memcpy(&tv.tv_sec, &now[0], 4);
    memcpy(&tv.tv_usec, &now[4], 4);

    tv.tv_sec = ntohl(tv.tv_sec);
    tv.tv_usec = ntohl(tv.tv_usec);

    printf("tv_sec: %x\n", tv.tv_sec);
    printf("tv_usec: %x\n", tv.tv_usec);
//    now = ntohl((u_long)now);       /* put in host byte order       */
//    now -= UNIXEPOCH;               /* convert UCT to UNIX epoch    */
    printf("%s\n", ctime(&tv.tv_sec));
    exit(0);
}
