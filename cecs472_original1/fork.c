#include <stdio.h>
#include <stdlib.h> /* fork */
int sum;
main () {
  int i;
  sum = 0;
  fork();  /* create a new process */
  for (i=1; i<=10000 ; i++) {
    sum += i;
    printf("sum is %d\n", sum);
    fflush(stdout);
  }
  exit(0);
};
