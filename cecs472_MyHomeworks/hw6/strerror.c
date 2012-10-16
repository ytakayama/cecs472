#ifndef _STRERROR
#define _STRERROR
extern char *sys_errlist[];
char * strerror(int error){
  return sys_errlist[error];
}
#endif
