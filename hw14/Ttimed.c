//Yohei Takayama
//cecs472 Homework8 9/24/2012
//Ttimed.c


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "get_port.c"

#include "passiveTCP.c"
#define QLEN	5 // max clients number that can wait in que for connection
/* handled by the include
 * int     passiveUDP(const char *service);
 * int     errexit(const char *format, ...);
 */

//#define UNIXEPOCH       2208988800UL      /* UNIX epoch, in UCT secs      */

/*------------------------------------------------------------------------
 * main - Iterative TCP server for TIME service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
    struct sockaddr_in fsin;        /* the from address of a client */
    char    *service = get_port();      /* service name or port number  */
    char    buf[8];                 /* "input" buffer; any size > 0 */
    int     msock, ssock;                   /* server socket                */
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
            errexit("usage: TCPtimed [port]\n");
    }

    // msock us the master socket. QLEN is the que length.
    // the server waits for a connect request from client, using the master socket.
    msock = passiveTCP(service, QLEN); 

    while (1)
    {
        alen = sizeof(fsin);
	// after a connection request arrives; accepts a connection and creates a slave
	// socket (sscok) for the connection. A slave socket provides communication to
	// one client. 
	ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
	if(ssock < 0)
//          if (recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&fsin, &alen) < 0)
            errexit("recvfrom: %s\n", strerror(errno)); // handles error; mostly OS proble.
        (void) gettimeofday(&tv, NULL);
	// Prints tv_sec and tv_usec in hexdecimal
	printf("tv_sec: %x\n", tv.tv_sec);
	printf("tv_usec: %x\n", tv.tv_usec);
       // htonl nad put back into the structure 
	tv.tv_sec = htonl(tv.tv_sec);
	tv.tv_usec = htonl(tv.tv_usec);
	// copy the sec into the array starting at position 0
	memcpy(&buf[0], &tv.tv_sec, 4);
	// copy usec into the array starting at positioin 4
	memcpy(&buf[4], &tv.tv_usec, 4);
	// Send the array (8 bytes)
        (void) write(ssock, (char *)&buf, sizeof(buf));
	close(ssock);
    }
}
