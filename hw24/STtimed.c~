//Yohei Takayama
//cecs472 Homework24 11/28/2012
//STtimed.c
//upgraded hw8 Ttime.c

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <openssl/ssl.h> //upgrade hw24
#include "get_port.c"

#include "passiveTCP.c"
#define QLEN	5 // max clients number that can wait in que for connection
#define pass "password"

// upgrade hw24
int passwd_cb(char *buf, int num, int rwflag,void *userdata)
{
  if (num < strlen(pass)+1)
    return 0;
  strcpy(buf, pass);
  return strlen(pass);
};

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
   
    //upgrade hw24
   // int master, client, len; char message[80];
    int wn, rn, rslt;
   // struct sockaddr_in my_addr, his_addr;
    SSL_METHOD* meth;
    SSL_CTX *ctx;
    SSL *ssl;


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

  /* The SSL stuff */ //upgrade hw24 -------------
  // setting up the context
  SSL_library_init();
  meth = SSLv23_method();
  ctx = SSL_CTX_new(meth);
  SSL_CTX_use_certificate_chain_file(ctx, "server.pem");
  SSL_CTX_set_default_passwd_cb(ctx, passwd_cb);
  SSL_CTX_use_PrivateKey_file(ctx, "server.pem", SSL_FILETYPE_PEM);
  //-----------------------------------------------
    while (1)
    {
	// updrage hw24 -----------------------
	ssock = accept(msock, (struct sockaddr *)&fsin, &alen);

	ssl = SSL_new(ctx);
	SSL_set_fd(ssl, ssock);
	rslt = SSL_accept(ssl);
        alen = sizeof(fsin);
        // -------------------------------------
	if(rslt < 0)
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
        SSL_write(ssl, &buf, sizeof(buf)); //update hw24
	SSL_free(ssl);
	close(ssock);
    }
}


