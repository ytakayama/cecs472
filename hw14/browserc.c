/* This program implements the browser client. 
 * It is for use with your browser server.
 * All commands are send with a \0 delimiter included on the end
 * You will need to look for this when re-assembling the
 * command in the server.
 * Notice the sleep in the middle of sending the chdir
 * command to check that your reassemble is correct.
 */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include "connectTCP.c"
#include "get_port.c"

#define LINELEN         128

/*------------------------------------------------------------------------
 * main - TCP client for ECHO service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
        char    *host = "localhost";    /* host to use if none supplied */
        char    *service = get_port();      /* default service name         */

        switch (argc) {
        case 1:
                host = "localhost";
                break;
        case 3:
                service = argv[2];
                /* FALL THROUGH */
        case 2:
                host = argv[1];
                break;
        default:
                fprintf(stderr, "usage: TCPecho [host [port]]\n");
                exit(1);
        }
        signal (SIGPIPE,SIG_IGN);
        browser(host, service);
        exit(0);
}

/*------------------------------------------------------------------------
 * TCPecho - send input to ECHO service on specified host and print reply
 *------------------------------------------------------------------------
 */
int
browser(const char *host, const char *service)
{
  char buf[LINELEN+1];   /* input buffer */
  char command[80];      /* buffer for sending the command */
  int  s, n;                   /* socket descriptor, read count*/
  int  cmdSize, inchars;       /* characters sent and received */
  int sendSize;
  unsigned long fileSize;
  int dest_fd;

  s = connectTCP(host, service);

  while (1) {
    /* get the user's command */
    printf(">");
    fgets(command,80,stdin);
    /* replace the '\n' that fgets puts at the end of the line with a '\0' */
    command[strlen(command)-1]='\0';
    /* Send the command to the server. Really all that needs
     * to be done here is
     * write(s,command,strlen(command)+1);
     * However, to test your reassembly loop there
     * are two writes with a sleep in between.
     * Of course, the switch does ensure that the command is l,c,g;
     * but that's just a side effect.
     */
    sendSize = strlen(command)+1;
    switch (command[0]) {
      case 'l': 
        /* send the entire command*/
        write(s, command, sendSize);
        /* A \0 delimited directory should be comming back. Read
         * and print that directory */
        while (1)
        {
          n = read(s,buf,sizeof(buf)-1);
          /* error checks, hopefully these don't happen */
          if (n < 0)
            errexit("socket read failed: %s\n", strerror(errno));
          if (n == 0)
            errexit("unexpected end of input\n");
          /* put a string delimiter on */
          buf[n]='\0';
          /* print this part of the listing.*/
          printf("%s",buf);
          /* check for the terminator, exit the loop if we find it */
          if (buf[n-1]=='\0') break;
        }
        break;
      case 'c':
        /* this is a c command, c-space-dirName-\0; the sendSize should be at
         * least 4. If it isn't we don't bother to send.*/
        if (sendSize < 4) break;
        /* send the first 3 */
        write(s, command, 3);
        sleep(1);
        /* send the rest */
        write(s,&command[3],sendSize-3);
        /* we expect nothing to return so we go back around the loop */
        break;
      case 'g':
        /* this is a g command, g-space-dirName-\0; the sendSize should be at
         * least 4. If it isn't we don't bother to send. The code here
         * is exactly like the c command
         */
        if (sendSize < 4) break;
        /* send the first 3 */
        write(s, command, 3);
        sleep(1);
        /* send the rest */
        write(s,&command[3],sendSize-3);
        /* The first thing we expect is the file size. We use the
         * loop from the TCP time client. We use buf to build
         * the 4 bytes of the integer
         */
        for (inchars=0; inchars<4;inchars+=n)
	{
          n = read(s,&buf[inchars],4-inchars);
          /* error checks, hopefully these don't happen */
          if (n < 0)
            errexit("socket read failed: %s\n", strerror(errno));
          if (n == 0)
            errexit("unexpected end of input\n");
	}
	/* We have the 4 bytes, convert it into an integer.
	 * This integer is the size of the file that we
	 * are being sent
	 */
        memcpy(&fileSize,&buf[0],4);
        /* it should be in network order, convert it to host order */
        fileSize = ntohl(fileSize);
        /* This is a sanity check on the student server. On a real
         * server this would prevent the sending of a large file, but
         * on our tests this sort of file size probably means the
         * server didn't correctly pack up the size at the front of
         * the send.
         */
        if (fileSize > 200000)
        {
          errexit("File of size %d (%x), assuming it's an error\n",
            fileSize,fileSize);
        }
        /* Create the destination file. */
        dest_fd = open("xfer.tmp",O_CREAT|O_WRONLY|O_TRUNC,0644);
        if (dest_fd < 0)
        {
          /* This could happen if the student tries to run
           * the client program in the instructor's directory;
           * the program wouldn't have permission to open the
           * output file.
           */
          errexit("Couldn't open file: %s\n",strerror(errno));
        }
        inchars = 0;
        while (inchars < fileSize)
        {
          n = read(s, buf, sizeof(buf));
          /* error checks, hopefully these don't happen */
          if (n < 0)
            errexit("socket read failed: %s\n", strerror(errno));
          if (n == 0)
            errexit("unexpected end of input\n");
          write(dest_fd, buf, n);
          inchars += n;
        }
        close(dest_fd);
        break;
      case 'q':
        exit(0);
      default:
        printf("bad command\n");
        
    }
  }
}
