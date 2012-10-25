//Yohei Takayama
//cecs472 Homework15 10/24/2012
//btimed.c

/* UDPtimed.c - main */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "get_port.c"

#include "passiveUDP.c"
/* handled by the include
 * int     passiveUDP(const char *service);
 * int     errexit(const char *format, ...);
 */

//#define UNIXEPOCH       2208988800UL      /* UNIX epoch, in UCT secs      */

/*------------------------------------------------------------------------
 * main - Iterative UDP server for TIME service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
    struct sockaddr_in fsin;        /* the from address of a client */
    char    *service = get_port();      /* service name or port number  */
    char    buf[8];                 /* "input" buffer; any size > 0 */
    int     sock;                   /* server socket                */
//    time_t  now;                    /* current time                 */
    int     alen;                   /* from-address length          */

    struct timeval tv;

    switch (argc)
    {
        case 1:
            break;
        case 2:
            service = argv[1];
            break;
        default:
            errexit("usage: UDPtimed [port]\n");
    }

    sock = passiveUDP(service);
    int One = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &One, sizeof(One)); 

    while (1)
    {
        alen = sizeof(fsin);
        if (recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&fsin, &alen) < 0)
            errexit("recvfrom: %s\n", strerror(errno));
        (void) gettimeofday(&tv, NULL );
	printf("tv_sec: %x\n", tv.tv_sec);
	printf("tv_usec: %x\n", tv.tv_usec);
       
	tv.tv_sec = htonl(tv.tv_sec);
	tv.tv_usec = htonl(tv.tv_usec);
	memcpy(&buf[0], &tv.tv_sec, 4);
	memcpy(&buf[4], &tv.tv_usec, 4);

//        now = htonl((u_long)(now + UNIXEPOCH));u}
        (void) sendto(sock, (char *)&buf, sizeof(buf), 0, (struct sockaddr *)&fsin, sizeof(fsin));
    }
}
