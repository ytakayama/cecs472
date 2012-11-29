/* passiveTCP.c - passiveTCP */
#ifndef _PASSIVETCP
#define _PASSIVETCP

#include "passivesock.c"
/* handled by include
 * int     passivesock(const char *service, const char *transport,
 *              int qlen);
 */

/*------------------------------------------------------------------------
 * passiveTCP - create a passive socket for use in a TCP server
 *------------------------------------------------------------------------
 */
int
passiveTCP(const char *service, int qlen)
/*
 * Arguments:
 *      service - service associated with the desired port
 *      qlen    - maximum server request queue length
 */
{
        return passivesock(service, "tcp", qlen);
}
#endif
