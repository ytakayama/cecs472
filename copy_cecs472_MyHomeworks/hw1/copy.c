//Yohei Takayama
//cecs472 Homework1 8/27/2012

#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
int main (int argc, char* argv[])
{
  int src_fd dest_fd;
  char filebuf[256]; /* a small buffer used to copy the file */
  int readSize; // Could also say   size_t readSize

  src_fd = open(argv[1], O_RDONLY);
  dest_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);

  while (( readSize = read(src_fd, filebuf, sizeof(filebuf)-1)) > 0)
  {
    // I turn it into a string only because I'm using printf;
    // making a copy using "write" would not need this.
    filebuf[readSize] = '\0';
    printf("%s",filebuf);

    write(destination, filebuf, readSize);
  }
  close(src_fd);
  close(destination);
  return 0;
}

