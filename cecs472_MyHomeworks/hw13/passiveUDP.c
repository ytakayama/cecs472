#ifndef _PASSIVEUDP
#define _PASSIVEUDP
/* passiveUDP.c - passiveUDP */

#include "passivesock.c"
/* handled by include
 * int     passivesock(const char *service, const char *transport,
 *              int qlen);
 */

/*------------------------------------------------------------------------
 * passiveUDP - create a passive socket for use in a UDP server
 *------------------------------------------------------------------------
 */
int
passiveUDP(const char *service)
/*
 * Arguments:
 *      service - service associated with the desired port
 */
{
        return passivesock(service, "udp", 0);
}
#endif
