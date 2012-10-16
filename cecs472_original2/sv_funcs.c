/* sv_funcs.c - TCPechod, TCPchargend, TCPdaytimed, TCPtimed */

#include <sys/types.h>

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

#define	BUFFERSIZE	4096		/* max read buffer size	*/

int	TCPechod(int), TCPchargend(int), TCPdaytimed(int), TCPtimed(int);
int	errexit(const char *format, ...);

/*------------------------------------------------------------------------
 * TCPecho - do TCP ECHO on the given socket
 *------------------------------------------------------------------------
 */
int
TCPechod(int fd)
{
	char	buf[BUFFERSIZE];
	int	cc;

	while (cc = read(fd, buf, sizeof buf)) {
		if (cc < 0)
			errexit("echo read: %s\n", strerror(errno));
		if (write(fd, buf, cc) < 0)
			errexit("echo write: %s\n", strerror(errno));
	}
	return 0;
}

#define	LINELEN		72

/*------------------------------------------------------------------------
 * TCPchargend - do TCP CHARGEN on the given socket
 *------------------------------------------------------------------------
 */
int
TCPchargend(int fd)
{
	char	c, buf[LINELEN+2];	/* print LINELEN chars + \r\n */

	c = ' ';
	buf[LINELEN] = '\r';
	buf[LINELEN+1] = '\n';
	while (1) {
		int	i;

		for (i=0; i<LINELEN; ++i) {
			buf[i] = c++;
			if (c > '~')
				c = ' ';
		}
		if (write(fd, buf, LINELEN+2) < 0)
			break;
	}
	return 0;
}

/*------------------------------------------------------------------------
 * TCPdaytimed - do TCP DAYTIME protocol
 *------------------------------------------------------------------------
 */
int
TCPdaytimed(int fd)
{
	char	buf[LINELEN], *ctime();
	time_t	now;

	(void) time(&now);
	sprintf(buf, "%s", ctime(&now));
	(void) write(fd, buf, strlen(buf));
	return 0;
}

#define	UNIXEPOCH	2208988800UL	/* UNIX epoch, in UCT secs	*/

/*------------------------------------------------------------------------
 * TCPtimed - do TCP TIME protocol
 *------------------------------------------------------------------------
 */
int
TCPtimed(int fd)
{
	time_t	now;

	(void) time(&now);
	now = htonl((u_long)(now + UNIXEPOCH));
	(void) write(fd, (char *)&now, sizeof(now));
	return 0;
}
