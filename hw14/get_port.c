/* This function returns a string that contains the number of your personal
 * well known port. Notice that it has real storage that it puts this
 * string into (port[10]). Since port is declared as static it will be 
 * allocated once and remain allocated for the life-time of the program (it
 * does not get re-created each time call the function. Thus port will be 
 * around when the main program wants to use the pointer to it. You may
 * include (#include) this procedure in you program.
*/

/* For the getuid */
#include <unistd.h>
#include <sys/types.h>

/* For the  sprintf */
#include <stdio.h>
char *get_port() {
  static char port[10];
  /* Get your personal well known port number */
  int well_known_port = getuid();
  if (well_known_port < 500) well_known_port += 5000;
  /* Put it into a string so it can be passed to the comer procedures */
  sprintf(port,"%d",well_known_port);
  /* Return a pointer to where we put the answer. */
  return port;
}
