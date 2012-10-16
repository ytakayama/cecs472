#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
int main (int argc, char* argv[]) {
  int src_fd;
  char filebuf[256]; /* a small buffer used to copy the file */
  int readSize; // Could also say   size_t readSize

  src_fd = open(argv[1],O_RDONLY);

  while (( readSize = read(src_fd, filebuf, sizeof(filebuf)-1)) > 0)
  {
    // I turn it into a string only because I'm using printf;
    // making a copy using "write" would not need this.
    filebuf[readSize] = '\0';
    printf("%s",filebuf);
  }
  close(src_fd);
  return 0;
}
