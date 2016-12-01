/**
 *     Jason Downing
 *     Assignment 6 main c file
 */
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

// Print function, displays all the stats about the files
void print_details(struct dirent *entry, struct stat statBuffer);

// Command line program
int main(int argc, char *argv[]) {

  struct stat statBuffer;
  struct dirent* entry;
  DIR* directory;
  int x;

  // Two ways to run this program: no arguments, or multiple arguments

  // Multiple arguments if argc isn't equal to 1
  if (argc > 1) {

    // Let's run through all the arguments
    for(x = 1; x < argc; x++) {

      // Should print details. argv[] has the file names, so let's check them.
      // First see if we can access the current file
      if (lstat(argv[x], &statBuffer ) == -1) {
        printf("Error: failed to access file %s!\n", argv[x]);
        exit(1);
      }

      // Now we can print the details for this file.
      // First print the file name, then print the stats about it.
      printf("File name: %s\n", argv[x]);
      print_details(entry, statBuffer);
    }

    return 0;     // Le end of multiple arguments
  }

  // Since we got no arguments, that means we should check this directory
  // and display stats the files in it.
  // Let's see if we can open the current directory (. = current directory)
  if ( (directory = opendir(".")) == NULL) {

    printf("Error: failed to open the current directory!\n");
    exit(1);
  }

  // Okay so we opened it. Let's print the details for all the files here!
  while( (entry = readdir(directory)) != NULL) {

    // Check and see if we can even open the current directory
    if (lstat(entry -> d_name, &statBuffer) == -1) {

      // It failed for some reason
      printf("Error: lstat failed on the current directory!\n");
      exit(2);
    }

    // Now we can print the details for this file.
    // Print the file name, and then the stats about it.
    printf("FILE NAME: %s\n", entry -> d_name);
    print_details(entry, statBuffer);
  }

  return 0;     // Le end
}

// Print function, displays all the stats about the files
// Some of this is from Prof. Moloney's lecture capture:
// URL: *put url here since he went over this on 12/1/2016*
// Also, I found a man page that had examples so I referenced that:
// URL: http://pubs.opengroup.org/onlinepubs/009604499/functions/stat.html
void print_details(struct dirent *entry, struct stat statBuffer) {
  struct passwd  *owner;
  struct group   *group;

  /*
      Output should look like the following:

      FILENAME
      FILE_TYPE
      PERMISSIONS
      OWNER_NAME
      GROUP_NAME
      DATE_OF_LAST_MODIFICATION
      LINK_COUNT
      SIZE_IN_BYTES OR DEV INFO
      INODE_NUMBER

      Prof. Moloney provided an example in the assignment 6 PDF:

      FILENAME: alpha
      FILE_TYPE: ordinary
      PERMISSIONS: rw- r-- r--
      OWNER_NAME: jedwards
      GROUP_NAM: grad
      DATE_OF_LAST_MODIFICATION: Mar 30 08:11 2003
      LINK_COUNT: 2
      SIZE_IN_BYTES: 1345 (or 12, 6 dev info)
      INODE_NUMBER: 347
       *******< a blank line between entries >*******
  */

  // We've already print the file name in main, so let's print the file type
  // URL: http://www.cs.odu.edu/~cs476/unix/codelectures/lstat.c
  printf("FILE_TYPE: ");

  // Get the mode of the file
  switch (statBuffer.st_mode & S_IFMT) {
    // Ordinary regular file
    case S_IFREG:
      printf("ordinary\n");
      break;

    // Directory
    case S_IFDIR:
      printf("directory\n");
      break;

    // Symbolic Link
    case S_IFLNK:
      printf("symbolic link\n");
      break;

    // Character Device
    case S_IFCHR:
        printf("character device\n");
        break;

    // Block device
    case S_IFBLK:
        printf("block device\n");
        break;

    // In case the user tries a type that we don't support, print an error.
    default:
        printf("Error: unknown file type\n");
        break;
  }

  // Print the permissions, in the format: rw- r-- r--
  // URL: https://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c
  printf("PERMISSIONS: ");
  printf( (S_ISDIR(statBuffer.st_mode))  ? "d" : "-");
  printf( (statBuffer.st_mode & S_IRUSR) ? "r" : "-");
  printf( (statBuffer.st_mode & S_IWUSR) ? "w" : "-");
  printf( (statBuffer.st_mode & S_IXUSR) ? "x" : "-");
  printf( (statBuffer.st_mode & S_IRGRP) ? "r" : "-");
  printf( (statBuffer.st_mode & S_IWGRP) ? "w" : "-");
  printf( (statBuffer.st_mode & S_IXGRP) ? "x" : "-");
  printf( (statBuffer.st_mode & S_IROTH) ? "r" : "-");
  printf( (statBuffer.st_mode & S_IWOTH) ? "w" : "-");
  printf( (statBuffer.st_mode & S_IXOTH) ? "x" : "-");
  printf("\n");

  // Print the owner name if found using getpwuid()
  if ( (owner = getpwuid(statBuffer.st_uid) ) != NULL) {
    printf("OWNER_NAME: %-8.8s\n", owner -> pw_name);
  }
  // Otherwise just print the UID
  else {
    printf("OWNER_NAME: %-8d\n", statBuffer.st_uid);
  }

  // Print the group name if found using getgrgid()
  if ( (group = getgrgid(statBuffer.st_gid) ) != NULL) {
    printf("GROUP_NAME: %-8.8s\n", group -> gr_name);
  }
  // Otherwise just print the GID
  else {
    printf("GROUP_NAME: %-8d\n", statBuffer.st_gid);
  }
  // Print the date of last modification in local time format
  // On my Ubuntu 16.04 LTS laptop it looks like: Thu Dec  1 13:29:46 2016
  // But on Mercury / cs.uml.edu it may look different!
  // URL: http://man7.org/linux/man-pages/man3/ctime.3.html
  printf("DATE_OF_LAST_MODIFICATION: %s", ctime(&(statBuffer.st_mtime)));

  // Print the link count
  printf("LINK_COUNT: %jd\n", (long) statBuffer.st_nlink);

  // Print the size in bytes
  printf("SIZE_IN_BYTES: %jd\n", (long) statBuffer.st_size);

  // Print the inode number
  printf("INODE_NUMBER: %jd\n", (long) statBuffer.st_ino);

  // Print a blank link between each entry.
  printf("\n");
}
