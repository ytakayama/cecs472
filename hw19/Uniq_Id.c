#include <stdio.h>
int main(){
  printf("0x%x\n",0x20000000 + getuid());
  return 0;
}
