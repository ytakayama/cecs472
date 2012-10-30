//Yohei Takayama
//cecs472 Homework12 10/15/2012
//csa472q1
//Chapter 13b
/* chatc.c - main */
// used TCPtecho.c as reference...

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#include "connectTCP.c"
#include "get_port.c"
/* handled by the include
 * int     errexit(const char *format, ...);
 * int     connectTCP(const char *host, const char *service);
 */

#define BUFSIZE		4096            /* write buffer size            */
//#define CCOUNT          64*1024         /* default character count      */
#define QLEN		5    /* maximum connection queue length      */

/*------------------------------------------------------------------------
 * main - concurrent TCP client for chat service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
    char    *host = "localhost";    /* host to use if none supplied */
    char    *service = get_port();  /* default service name         */

	int 	fd;	// fd  is an index into the desctiotor table.
	int     nfds;	// nfds is the number of file descriptors
	// fd_set is a set of integers. implemented by a bit vector
	fd_set afds;    /*  a active file descriptor set     */
	fd_set  rfds;   /*  a receive file descriptor set   */
	int     sock;   /* socket */
	char 	out_buf[BUFSIZE];	/* buffer for sending message */
	char 	in_buf[BUFSIZE];	/* buffer for receving message */
	int      m;
	// for Timed Wait
	struct timeval waitTime;
	int 	n; //
// create connection with the server ------------------------------------
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
    sock = connectTCP(host, service);
// -----------------------------------------------------------------------
    FD_ZERO(&afds); // the set of file descriptors is set to the empty set. // set/clean the file discriptor afds zero

    FD_SET(sock, &afds); // add a file descriptor (sock) to the set of file descriptors (sfds).
    FD_SET(0, &afds); // add a keyboard(0) descriptor to the set of file descriptors (sfds).i
    
    // getdablesize: this Unix system call returns the maximum number of descriptors in the descriptor table.
    nfds = sock+1; //set nfds to be the number of the socket descriptor +1

    while (1)
	{
		
		memcpy(&rfds, &afds, sizeof(rfds)); // makes copy from afds to rfds
		waitTime.tv_sec = 5;
		waitTime.tv_usec = 0;
		// select() example...
		// iret = select(nfds, rfds, wfds, efds, time);
		// nfds: number of file descriptor.
		// rfds: check this set for input.
		// wfds: check this set to see if output is allowed
		// efds: check this set for errors.
		// the program waits here until there is imput on at least one descriptor in the rfds set.
		// waitTime is 5 sec and it is modified as time passes
		//  0 in select() are NULL. not used 
		m = select(nfds, &rfds, (fd_set *)0, (fd_set *)0, (struct timeval *) &waitTime); 
		if(m < 0)
			errexit("select: %s\n", strerror(errno));
		else if(m == 0)
		{
			printf("Anybody there?\n");
			continue;
		}

		// check if keyboard is set...if so, read from keyboard and sends it to server
		if(FD_ISSET(0, &rfds)) // the keyboard is descroptor 0.
		{
		//	printf("send: ");
			n = fgets(out_buf, BUFSIZE, stdin);
			if (n ==  NULL)
			{
				close(0);
				FD_CLR(0, &afds);
				shutdown(sock, SHUT_WR);
				continue;
			}
			if(send(sock, out_buf, strlen(out_buf), 0) <= 0)
			{
				printf("Bye!\n");
				errexit("send failed: %s\n", strerror(errno));
			}

		}
		// check if the socket is set... if so, do read
		if (FD_ISSET(sock, &rfds))
		{
			n = recv(sock, in_buf, sizeof(in_buf), 0);
			if(n <= 0)
			{

				close(0);
				exit(0);
			}
			in_buf[n] = '\0';
			printf("recv: %s", in_buf);
		}
	} // end while loop
    exit(0);
}

