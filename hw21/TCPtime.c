//Yohei Takayama
//cecs472 homework6 9/17/2012

/* TCPdaytime.c - TCPdaytime, main */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h> //for time.c

int     TCPdaytime(const char *host, const char *service);
#include "connectTCP.c"
/* handled by the include
 * int     errexit(const char *format, ...);
 * int     connectTCP(const char *host, const char *service);
 */
#define UNIXEPOCH 	2208988800UL	/* UNIX epoch, in UCT secs	*/
#define LINELEN         128

/*------------------------------------------------------------------------
 * main - TCP client for DAYTIME service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
        char    *host = "panther";    /* host to use if none supplied */
        char    *service = "5001";   /* default service port         */

        switch (argc) {
        case 1:
                break;
        case 3:
                service = argv[2];
                /* FALL THROUGH */
        case 2:
                host = argv[1];
                break;
        default:
                fprintf(stderr, "usage: TCPdaytime [host [port]]\n");
                exit(1);
        }
        TCPdaytime(host, service);
        exit(0);
}

/*------------------------------------------------------------------------
 * TCPdaytime - invoke Daytime on specified host and print results
 *------------------------------------------------------------------------
 */
int
TCPdaytime(const char *host, const char *service)
{
        char    buf[LINELEN+1];         /* buffer for one line of text  */
        int     s, n;                   /* socket, read count           */
	int	inchars;
	time_t	now;
	
        s = connectTCP(host, service);
	for(inchars = 0; inchars < 4; inchars += n)
	{
		n = read(s, &buf[inchars], 4 - inchars);
		if (n <= 0)
			errexit("read failed: %s\n", strerror(errno));
	}
	memcpy(&now, buf, 4);

	now = ntohl((u_long)now);	/* put in host byte order	*/
	now -= UNIXEPOCH;		/*convert UCT to UNIC epoch	*/
	printf("%s", ctime(&now));
	exit(0);
}
