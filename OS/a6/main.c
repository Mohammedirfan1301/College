/**
 *     Jason Downing
 *     Assignment 6 main c file
 */
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

// Print function, displays all the stats about the files
void print_details(struct stat statBuffer);

// Command line program
int main(int argc, char *argv[]) {

  struct stat statBuffer;
  struct dirent* entry;
  DIR* directory;
  int x, y;

  // Two ways to run this program: no arguments, or multiple arguments

  // Multiple arguments
  if (argc > 1) {

    // Let's run through all the arguments
    for(x = 1; x < argc; x++) {
      //printf("WE GOT AN ARGUMENT #%d\n", x);

      // Should print details. argv[] has the file names, so let's check them.
      // First see if we can access the current file
      if (lstat(argv[x], &statBuffer ) == -1) {
        printf("Error: failed to access file %s!\n", argv[x]);
        exit(1);
      }

      // Now we can print the details for this file.
      // First print the file name, then print the stats about it.
      printf("File name: %s\n", argv[x]);
      print_details(statBuffer);
    }
  }
  // Since we got no arguments, that means we should check this directory
  // and display stats the files in it.
  else {

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
      printf("File name: %s\n", entry -> d_name);
      print_details(statBuffer);
    }
  }

  // Le end
  return 0;
}

// Print function, displays all the stats about the files
// Some of this is from Prof. Moloney's lecture capture:
// URL: *put url here since he went over this on 12/1/2016*
void print_details(struct stat statBuffer) {

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


  // print the permissions, in the format: rw- r-- r--

  // print the owner name

  // print the group name

  // print the date of last modification in format: MONTH | DAY | TIME | YEAR

  // print the link count

  // print the size in bytes

  // print the inode number

  // Print a blank link between each entry.
  printf("\n");
}
