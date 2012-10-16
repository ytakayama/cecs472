//Yohei Takayama
//cecs472 Homework2 8/29/2012

#include <stdio.h>
#include <stdlib.h> /* fork */
int sum;
main ()
{
  int i;
  sum = 0;
  if(fork()) // parent process  /* create a new process */
  {
    for (i=1; i<=10; i++)
    {
      sum += i;
      printf("P sum is %d\n", sum);
      fflush(stdout);
      sleep(1);
    }
  }
  else // child process
  {
    for (i=1; i<=10; i++)
    {
      sum += i;
      printf("C sum is %d\n", sum);
      fflush(stdout);
      sleep(2);
    }
  }
    exit(0);
};
