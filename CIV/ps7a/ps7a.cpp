/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>


int main(int argc, const char* argv[]) {
  // Make sure the user knows how to use our amazing log parser.
  if (argc != 2) {
    std::cout << "./ps7a device1_intouch.log\n";
    return 0;
  }

  int lines_scan = 0;
  std::string file_name(argv[1]);
  std::string report = "";
  std::string success = "oejs.AbstractConnector:Started SelectChannelConnector";

  std::cout << "Device boot report.\n";
  std::cout << "InTouch log file: " << file_name << "\n";

  // Read the file here and do stuff.
  // Save stuff to a string with formatting to output later on.
  std::string line;
  std::ifstream file (file_name);

  if (file.is_open()) {
    while (getline(file, line)) {
      // We've got the current string here and can do stuff with it.

      lines_scan++;
    }
    file.close();
  }

  // ...
  report += "\nDevice boot count: initiated = xx, completed: xx\n";

  // This would be the first thing we print out - the total lines we scanned.
  std::cout << "Lines scanned: " << lines_scan << "\n";

  // Now let's print out our report string. It has already been formatted
  // correctly so it should be fairly simple to just dump it to stdio.
  std::cout << report;

  return 0;
}
