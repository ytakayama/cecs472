//Yohei Takayama
//cecs472 Homework11 10/10/2012
//csa472q1
//Chapter 13

///* chatd.c - main */
// used TCPmechod.c as reference...

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#define QLEN               5    /* maximum connection queue length */
#define BUFSIZE         4096

#include "passiveTCP.c"
#include "get_port.c"
/* handled by the include
 * int    errexit(const char *format, ...);
 * int    passiveTCP(const char *service, int qlen);
 *
 * /
 
/*------------------------------------------------------------------------
 * main - Concurrent TCP server for chat service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
    char    *service = get_port();      /* service name or port number  */
    struct  sockaddr_in fsin;        /* the from address of a client */
    int     msock;                  /* master server socket         */
    // fd_set is set of integers. Implimented by a bit vector (array of Booleans).
    fd_set  rfds;                   /* read file descriptor set     */
    fd_set  afds;                   /* active file descriptor set   */
    int     alen;                   /* from-address length          */
    int     fd, nfds;

    char buf[BUFSIZE];
    int fd2, cc;

    switch (argc)
	{
        case 1:
            break;
        case 2:
            service = argv[1];
            break;
        default:
            errexit("usage: TCPmechod [port]\n");
    }

	signal(SIGPIPE, SIG_IGN);

    msock = passiveTCP(service, QLEN);

    nfds = getdtablesize(); //scan them all
    // FD_ZERO: the set of file descriptors(afds) is set to the empty set.
    FD_ZERO(&afds);
    // FD_SET: add a file descriptor(msock) to the set of file descriptors(afds).
    FD_SET(msock, &afds);


    while (1)
	{
        memcpy(&rfds, &afds, sizeof(rfds)); // makes copy from afds to rfds

        if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0) < 0)
            // 0 in select() are NULL. not used..
            errexit("select: %s\n", strerror(errno));
        // FD_ISSET: returns TRUE if file descriptor(msock) is in the set of file descriptors(rfds).
        if (FD_ISSET(msock, &rfds))// check if master socket is set...if so, do accept
		{
            int ssock;

            alen = sizeof(fsin);
            ssock = accept(msock, (struct sockaddr *)&fsin,  &alen);
            if (ssock < 0)
                    errexit("accept: %s\n", strerror(errno));
            // FD_SET: add a file descriptor(ssock) to the set of file descriptors(afds).
            FD_SET(ssock, &afds);
        }

        for (fd = 0; fd < nfds; ++fd) // checks all other sockes (other than master socket)
		{
            // FD_ISSET: returns TRUE if file descriptor(fd) is in the set of file descriptors(rfds).
            if (fd != msock && FD_ISSET(fd, &rfds)) // checks if master socket is set
			{
				cc = recv(fd, buf, sizeof(buf), 0);
				if (cc <= 0)
				{
					(void) close(fd);
                    // FD_CLR: remove file descriptor(fd) from the set of file descriptors(afds).
					FD_CLR(fd, &afds);
					continue; // go back to top of the for-loop 
	        	}
				for(fd2 = 0; fd2 < nfds; ++fd2)
				{
                    // following if statement skips the master socket (msock),
                    // skips the fd, and allows only clients found in the afds.
                    // FD_ISSET: returns TRUE if file descriptor(fd2) is in the set of file descriptors(afds).
					if(fd2 != msock && FD_ISSET(fd2, &afds) && fd2 != fd)
					{
                        // send message to fd2 socket.
						if (cc && send(fd2, buf, cc, 0) <= 0)
						{
							(void) close(fd2);
                            // FD_CLR: remove file descriptor(fd2) from the set of file descriptors(afds).
							FD_CLR(fd2, &afds); // clear the send socket (fd2) from afds
						}
					}
				}
			}
		}
    }
}

