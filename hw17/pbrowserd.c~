//Yohei Takayama // csa472q1
//cecs472 Homework17 10/31/2012
//pbrowserd.c - preallocated server

///* pbrowerd.c - main, TCPbrowser */
// used some code from browserd.c for concurrent server - fork(); //homework9
// and used browser.c for handing "list", "change", and "get" cases...

#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define QLEN        5 // maximum connection queue length
#define BUFSIZE     4096

void    reaper(int);
int     TCPbrowser(int fd);

#include "get_port.c"
#include "passiveTCP.c"
/* handled by the include
 * int     errexit(const char *format, ...);
 * int     passiveTCP(const char *service, int qlen);
 */

/*------------------------------------------------------------------------
 * main - Concurrent TCP server for browse_file_system service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
    char    *service = get_port();  /* service name or port number  */
    struct  sockaddr_in fsin;       /* the address of a client      */
    int     alen;                   /* length of client's address   */
    int     msock;                  /* master server socket         */
    int     ssock;                  /* slave server socket          */

    switch (argc)
    {
        case 1:
            break;
        case 2:
            service = argv[1];
            break;
        default:
            errexit("too many arguments...\n");
    }

    msock = passiveTCP(service, QLEN);

    // reaper
    (void) signal(SIGCHLD, reaper);


    // fork() creates a new process by duplicating the calling process.
    // The new process, referred to as the child, is an exact duplicate of 
    // the calling process, referred to as the parent...
    // On success, the PID of the child process is returned in the parent, 
    // and 0 is returned in the child. On failure, -1 is returned in the parent,
    switch (fork())
    {
        case 0:    /* child */
            fork();
        default:   /* parent */
            break;
         case -1:
             errexit("fork: %s\n", strerror(errno));
    } // end switch

    while (1) // handle one client request per iteration.
    {
        alen = sizeof(fsin);
        // accept a client, get slave socket connected to that client.
        ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
        if (ssock < 0)
        {
            if (errno == EINTR)
                continue;
            errexit("accept: %s\n", strerror(errno));
        }
	else
	{
	    TCPbrowser(ssock);
	    close(ssock);
	    printf("im dead\n");
	}
    } // end while loop
} // end main

/*------------------------------------------------------------------------
 * TCPbrowser - browse_file_system service
 *------------------------------------------------------------------------
 */
int
TCPbrowser(int fd) // fd means forked server = child process = slave server socket ??
{
    DIR *dirp; // directory path
    struct dirent *dp;
    struct stat buf;
    char command[80];
    int src_fd, dest_fd;
    char dirbuf[256]; /* a small buffer used to send back directory */
    int fileSize;
    char filebuf[256]; /* a small buffer used to copy the file */
    int readSize;
    int transferCount;

    int inchars, n;

    while (1)
    {
        /* why i can't do thin????
        n = read(fd, command, sizeof(command));
        if(n < 0)
            errexit("command read: %n\n", strerror(errno));
        if(n == 0) // On end of file, read returns a 0.
            exit (0);
        */
        inchars = 0;
        while(1)
        {
            // read returns the number of bytes read.
            n = read(fd, &command[inchars], sizeof(command-1));
            if(n < 0)
                errexit("command read: %n\n", strerror(errno));
            if(n == 0) // On end of file, read returns a 0.
                return(0);
            inchars += n;
         //   command[inchars] = '\0';
            if(command[inchars-1] == '\0')
                break;
        } // end innner while loop

        /* get the user's command */
        printf("command: %s\n", command);

        switch (command[0])
        {
            case 'l': 
                dirp = opendir(".");
                for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp))
                {
                    stat(dp->d_name, &buf);
                    printf("%s\t%s", dp->d_name, ctime(&(buf.st_mtime)));
                    sprintf(dirbuf, "%s\t%s", dp->d_name, ctime(&(buf.st_mtime)));
                    write(fd, &dirbuf, strlen(dirbuf));
                }
                write(fd, "\0", 1);
                closedir(dirp);
                break;
            case 'c':
                chdir(&command[2]);
                break;
            case 'g':
                /* Get the file size */
                stat(&command[2], &buf);
                fileSize = buf.st_size;
                /* open the input file */
                src_fd = open(&command[2], 0);
                if(src_fd == -1)
                    fileSize = 0;
                n = htonl(fileSize);
                write(fd, &n, sizeof(fileSize)); // sends size of the file to the client
                /* open the destination file */
                // dest_fd = open("xfer.tmp",O_CREAT|O_WRONLY|O_TRUNC,0644);
                /* copy the file using the fileSize */
                transferCount = 0;
                while (transferCount < fileSize)
                {
                    readSize = read(src_fd, filebuf, sizeof(filebuf));
                    // write(dest_fd, filebuf, readSize);
                    write(fd, &filebuf, readSize);
                    transferCount += readSize;
                }
                close(src_fd);
                break;
            case 'q':
		printf("quit\n");
               return(0);
            default:
                printf("bad command\n");
        } //end switch
    }// end outer while loop
}// end TCPbrowser

/*------------------------------------------------------------------------
 * reaper - clean up zombie children
 *------------------------------------------------------------------------
 */
/*ARGSUSED*/
void
reaper(int sig)
{
    int status;

    while (wait3(&status, WNOHANG, (struct rusage *)0) > 0)
        /* empty */;
        /* changed from >= to > because it was hanging until
        all children had exited -- 11 Sept 96 djv */
    (void) signal(SIGCHLD, reaper);
    /* this signal was added because linux deletes the signal entry
    whenever a signal is used, so we re-add it -- 10 Mar 99 djv */
}
