//Yohei Takayama
//cecs472 Homework5 9/12/2012
//UDPdaytime.c

/* UDPdaytime.c - main, UDPdaytime */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int     UDPdaytime(const char *host, const char *service);
#include "connectUDP.c"
/* handled by the include
 * int     errexit(const char *format, ...);
 * int     connectUDP(const char *host, const char *service);
 */

#define LINELEN         128

#define MSG	"what time is it?\n"

/*------------------------------------------------------------------------
 * main - UDP client for daytime service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
        char    *host = "localhost";
        char    *service = "daytime";

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
                fprintf(stderr, "usage: UDPdaytime [host [port]]\n");
                exit(1);
        }
        UDPdaytime(host, service);
        exit(0);
}

/*------------------------------------------------------------------------
 * UDPdaytime - send input to daytime service on specified host and print reply
 *------------------------------------------------------------------------
 */
int
UDPdaytime(const char *host, const char *service)
{
        char    buf[LINELEN+1];         /* buffer for one line of text  */
        int     s, nchars;              /* socket descriptor, read count*/

        s = connectUDP(host, service);

	(void) write(s, MSG, strlen(MSG)); //sends message to server
	
	if (read(s, buf, sizeof(buf)) < 0) //receives reply from server
		errexit("socket read failed: %s\n", strerror(errno));
	printf("%s", buf); //print reply message
}
