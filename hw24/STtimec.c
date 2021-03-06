//Yohei Takayama
//cecs472 Homework24 11/28/2012
//STtimec.c
//upgrade hw8 Ttime.c

#include <sys/types.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <openssl/ssl.h> //upgrade hw24
#include <signal.h> //upgrade hw24
#include "get_port.c"

#define BUFSIZE 64

//#define UNIXEPOCH       2208988800UL      /* UNIX epoch, in UCT secs      */
#define MSG             "what time is it?\n"

#define pass "password"

#include "connectTCP.c"

int passwd_cb(char *buf, int num, int rwflag,void *userdata)
{
  if (num < strlen(pass)+1)
    return 0;
  strcpy(buf, pass);
  return strlen(pass);
};

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
{
    char    *host = "localhost";    /* host to use if none supplied */
    char    *service = get_port();      /* default service name         */
//    time_t  now;                    /* 32-bit integer to hold time  */
    char    now[8];
    int     socket, n;                   /* socket descriptor, read count*/

    int	   inchars;
    struct timeval tv;

//upgrade hw24
  int rn, wn, rslt;
  struct sockaddr_in      srv_addr;
  SSL_METHOD *meth;
  SSL_CTX *ctx;
  SSL *ssl;
  signal(SIGPIPE, SIG_IGN);
 //----------------------------------
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

  /* Here comes the SSL stuff */ //upgrade hw24 -------
  SSL_library_init();
  meth = SSLv23_method();

  ctx = SSL_CTX_new(meth);
  SSL_CTX_use_certificate_chain_file(ctx, "client.pem");
  SSL_CTX_set_default_passwd_cb(ctx, passwd_cb);
  SSL_CTX_use_PrivateKey_file(ctx, "client.pem", SSL_FILETYPE_PEM);
  ssl = SSL_new(ctx);
  SSL_set_fd(ssl, socket);
  rslt = SSL_connect(ssl);
  //---------------------------------------------------
    for(inchars = 0; inchars < 8; inchars += n)
    {
   	 /* Read the time */ 
	n = SSL_read(ssl, &now, sizeof(now)); // upgrade hw24
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

