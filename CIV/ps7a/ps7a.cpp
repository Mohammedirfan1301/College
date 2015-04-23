/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include <boost/regex.hpp>
#include <iostream>
#include <fstream>
#include <string>


int main(int argc, const char* argv[]) {
  // Make sure the user knows how to use our amazing log parser.
  if (argc != 2) {
    std::cout << "./ps7a device1_intouch.log\n";
    return 0;
  }

  int lines_scan = 0;
  std::string file_name(argv[1]);
  std::string output_name = file_name + ".rpt";
  std::string report = "";
  std::string success = "oejs.AbstractConnector:Started SelectChannelConnector";

  // Need to match against something like this:
  std::string test = "2014-01-26 09:58:04.362:INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080"
  std::string start_regex = "";
  std::string end_regex = "([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2}).([0-9]{3}):INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080";

  std::cout << "Device boot report.\n\n";
  std::cout << "InTouch log file: " << file_name << "\n";

  // Read the file here and do stuff.
  // Save stuff to a string with formatting to output later on.
  std::string line;
  std::ifstream file (file_name.c_str());

  bool found_start = false;
  bool found_end = false;

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
