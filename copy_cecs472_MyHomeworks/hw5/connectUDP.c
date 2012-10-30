//Yohei Takayama
////cecs472 Homework5 9/12/2012
//connectUDP.c

/* connectUDP.c - connectUDP */
#ifndef _CONNECTUDP
#define _CONNECTUDP

#include "connectsock.c"
/* handled by include
 * int     connectsock(const char *host, const char *service,
 *                const char *transport);
 */

/*------------------------------------------------------------------------
 * connectUDP - connect to a specified UDP service on a specified host
 *------------------------------------------------------------------------
 */
int
connectUDP(const char *host, const char *service )
/*
 * Arguments:
 *      host    - name of host to which connection is desired
 *      service - service associated with the desired port
 */
{
        return connectsock(host, service, "udp");
}
#endif
