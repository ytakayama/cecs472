/* This program prints the contents of the current directory to the screen 
 * It prints one directory entry per iteration of the loop. Each entry is
 * printed on a separate line. The trick here is that the ctime call puts
 * a newline (\n) at the end of the string it returns. If you want the
 * information about a directory entry to go to into a string you may
 * use sprintf. See get_port.c for a hint about how to do this. 
 * Your program should print the directory in that same format as this
 * program does (i.e., name date). */
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
main () {
  DIR *dirp;
  struct dirent *dp;
  struct stat buf;
  dirp = opendir(".");
  for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {
    stat(dp->d_name, &buf);
    printf("%s\t%s",dp->d_name, ctime(&(buf.st_mtime)));
  }
  closedir(dirp);
}
