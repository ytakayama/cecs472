/* This program implements the user interface for the browser client. It also
 * has pieces of the browser server. The change directory and list directory
 * code should be carefully examined.
 * The trick is this client implements the commands directly, while you must
 * build a client that passes (most of) the commands to the server and gets
 * the answer back; and you must build the server.
 *
 * The list command prints the contents of the current directory to the screen 
 * It prints one directory entry per iteration of the loop. Each entry is
 * printed on a separate line. The trick here is that the ctime call puts
 * a newline (\n) at the end of the string it returns. If you want the
 * information about a directory entry to go to into a string you may
 * use sprintf. See get_port.c for a hint about how to do this. 
 * Your program should print the directory in that same format as this
 * program does (i.e., name date). 
 * Remember to read the homework assignment carefully !
 */
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
main () {
  DIR *dirp;
  struct dirent *dp;
  struct stat buf;
  char command[80];
  int fileSize;
  int src_fd,dest_fd;
  char filebuf[256]; /* a small buffer used to copy the file */
  int readSize;
  int transferCount;

  while (1) {
    /* get the user's command */
    printf(">");
    fgets(command,80,stdin);
    /* replace the '\n' that fgets puts at the end of the line with a '\0' */
    command[strlen(command)-1]='\0';
    switch (command[0]) {
      case 'l': 
        dirp = opendir(".");
        for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {
          stat(dp->d_name, &buf);
          printf("%s\t%s",dp->d_name, ctime(&(buf.st_mtime)));
        } 
        closedir(dirp);
        break;
      case 'c':
        chdir(&command[2]);
        break;
      case 'g':
        /* Get the file size */
        stat(&command[2], &buf);
        fileSize = buf.st_size;
        /* open the input file */
        src_fd = open(&command[2],0);
        /* open the destination file */
        dest_fd = open("xfer.tmp",O_CREAT|O_WRONLY|O_TRUNC,0644);
        /* copy the file using the fileSize */
        transferCount = 0;
        while (transferCount < fileSize)
        {
          readSize = read(src_fd, filebuf, sizeof(filebuf));
          write(dest_fd, filebuf, readSize);
          transferCount += readSize;
        }
        close(src_fd);
        close(dest_fd);
        break;
      case 'q':
        exit(0);
      default:
        printf("bad command\n");
        
    }
  }
}
