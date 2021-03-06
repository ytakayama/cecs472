//Yohei Takayama
//cecs472 homework25 12/03/2012
// this is new connectsock.c for IPv6

///* connectsock.c - connectsock */
#ifndef _CONNECTSOCK
#define _CONNECTSOCK

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifndef INADDR_NONE
#define INADDR_NONE     0xffffffff
#endif  /* INADDR_NONE */

#include "errexit.c"
/* int     errexit(const char *format, ...); handled by include */

/*------------------------------------------------------------------------
 * connectsock - allocate & connect a socket using TCP or UDP
 *------------------------------------------------------------------------
 */
int
connectsock(const char *host, const char *service, const char *transport )
/*
 * Arguments:
 *      host      - name of host to which connection is desired
 *      service   - service associated with the desired port
 *      transport - name of transport protocol to use ("tcp" or "udp")
 */
{
        struct hostent  *phe;   /* pointer to host information entry    */
        struct servent  *pse;   /* pointer to service information entry */
        struct protoent *ppe;   /* pointer to protocol information entry*/
        struct sockaddr_in6 sin6; /* an Internet endpoint address         */
        int     s, type;        /* socket descriptor and socket type    */

	struct addrinfo hint, *infoptr; // upgrade for hw25 (for IPv6)
	int result;

	hint.ai_family = AF_INET6;
	hint.ai_socktype = SOCK_STREAM; // UDP/TCP, 0 means retrive all.
	hint.ai_protocol = 0; /* any protool */
	// AI_CANONNAME return the cannonicanical name
	// AI_ADDRCONFIG used with unspec, return only addresses
	hint.ai_flags = AI_CANONNAME | AI_ADDRCONFIG;
	
        memset(&sin6, 0, sizeof(sin6));
	inet_pton(AF_INET6, host, &sin6.sin6_addr); // upgrage for hw25
	
	result = getaddrinfo(host, service, &hint, &infoptr);

        memcpy(&sin6, infoptr->ai_addr, infoptr->ai_addrlen);

        // memset(&sin6, 0, sizeof(sin6));
	// inet_pton(AF_INET6, host, &sin6.sin6_addr); // upgrage for hw25
        // sin6.sin6_family = AF_INET6; // upgrade for hw25
	// sin6.sin6_flowinfo =0;
/*
       // Map service name to port number
        if ( pse = getservbyname(service, transport) )
                sin6.sin6_port = pse->s_port;
        else if ( (sin6.sin6_port = htons((u_short)atoi(service))) == 0 )
                errexit("can't get \"%s\" service entry\n", service);

       // Map host name to IP address, allowing for dotted decimal
        if ( phe = gethostbyname(host) )
		//sin6.sin6_addr = in6addr_loopback;
                memcpy(&sin6.sin6_addr, phe->h_addr, phe->h_length);
        else if ( (sin6.sin6_addr.s6_addr[16] = inet_addr(host)) == INADDR_NONE )
                errexit("can't get \"%s\" host entry\n", host);

       // Map transport protocol name to protocol number
        if ( (ppe = getprotobyname(transport)) == 0)
                errexit("can't get \"%s\" protocol entry\n", transport);
*/
    /* Use protocol to choose a socket type */
        if (strcmp(transport, "udp") == 0)
                type = SOCK_DGRAM;
        else
                type = SOCK_STREAM;

    /* Allocate a socket */
    //API calls takes version 6 parameters
    //  s = socket(AF_INET6, SOCK_STREAM, IPPROTO_IPV6);
        s = socket(PF_INET6, type, ppe->p_proto);
        if (s < 0)
                errexit("can't create socket: %s\n", strerror(errno));
    /* Connect the socket */
        if (connect(s, (struct sockaddr *)&sin6, sizeof(sin6)) < 0)
                errexit("can't connect to %s.%s: %s\n", host, service,
                        strerror(errno));
        return s;
}
#endif
