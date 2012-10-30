//Yohei Takayama
//cecs472 Homework10 10/8/2012
//csa472q1

///* tbrowerd.c - main, TCPtbrowser.c */
// used hw9 browserd.c and changed fork() to threading...

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
#include <pthread.h> // this is for thread

#define QLEN        5 // maximum connection queue length
#define BUFSIZE     4096

void    reaper(int);
int     TCPtbrowser(int fd);

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
    static char port[10];
    sprintf(port,"%d", 5001);
    char    *service = port;  /* service name or port number  */
    //char    *service = get_port();  /* service name or port number  */
    struct  sockaddr_in fsin;       /* the address of a client      */
    int     alen;                   /* length of client's address   */
    int     msock;                  /* master server socket         */
    int     ssock;                  /* slave server socket          */

	//*** for thread ***
	pthread_t th; // th is the thread.
	pthread_attr_t ta; // ta is the thread attributes.

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

    //*** for thread ***
    // int pthread_attr_init(pthread_attr_t *attr);
    // The thread attribute variable is initialized to have defaults values.
	(void) pthread_attr_init(&ta);
    // int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
    // The detach state is set to "detached" as opposed to "joinable".
    // which means, the main program can't do thread joins. The main program doesn't need 
    // to do thread joins to recover thread resources...
	(void) pthread_attr_setdetachstate(&ta, PTHREAD_CREATE_DETACHED);

    // reaper
    (void) signal(SIGCHLD, reaper);

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

        // int ptherad_create(pthread_t *thread,
        // pthread_attr_t *attr,
        // void*(*start_routine)(void *),
        // void *arg);
        // Return value: zero = OK, non-zero = error.
        // th: is filled with info about the thread. This info is never used...
        // ta: says to do a "detached" create.
        // TCPtbrowser: is the procedure that is to be the thread.
        //(void * (*)(void *)): TCPtbrowser is int (*) int, it takes an integer and returns an integer.
        // warning... this cast is drstically disabling type checking... will give a warning when compile.. 
        if(pthread_create(&th, &ta, (void * (*)(void *))TCPtbrowser, (void *)ssock) < 0)
            errexit("pthread_create: %s\n", strerror(errno));
    } // end while loop
} // end main

/*------------------------------------------------------------------------
 * TCPtbrowser 
 *------------------------------------------------------------------------
 */
int
TCPtbrowser(int fd)
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
        inchars = 0;
        while(1)
        {
            n = read(fd, &command[inchars], sizeof(command)-1);
            if(n < 0)
                errexit("command read: %n\n", strerror(errno));
            if(n == 0)
            {
                close(fd); // close the soket
                return 0;
            }
            inchars += n;
            command[inchars] = '\0';
            if(command[inchars-1] == '\0')
                break;
        } // end inner while loop

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
                close(dest_fd);
                break;
            case 'q':
                return 0;
            default:
                printf("bad command\n");
        } //end switch
    }// end outer while loop
}// end TCPtbrowser

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
