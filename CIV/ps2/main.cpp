#include <iostream>
#include <string>
#include <sstream>
#include "LFSR.hpp"

// Testing the LFSR class

int main()
{
  LFSR test("01101000010", 8);

  std::cout << test << std::endl;

  std::string test_string("01101000010");

  // Hope this works. Step once.
  test.step();

  std::cout << test << std::endl;

// //   for(int x = 0; (unsigned)x < test_string.size(); x++)
// //   {
// //     std::cout << "Position " << x << " is: " << test_string[x] << std::endl;
// //   }
//
//   // figure out the position of the tap using the magic formula:
//   // position = size() - tap - 1
//   int tap_pos = test_string.size() - 8 - 1;
//
// //   std::cout << test_string[0] << test_string[tap_pos] << std::endl;
//
//   int res = test_string[0] ^ test_string[tap_pos];
//
//   std::cout << "res: " << res << std::endl;
//
//   std::string::size_type i;
//
//   std::ostringstream ostring;
//
//   // Now shift everything left.
//   for(i = 0; (unsigned)i < test_string.length() - 1; i++)
//   {
//     ostring << test_string[i + 1];
//   }
//
//   ostring << res;
//
//   std::ostringstream oss;
//   oss << test_string << res;
//   std::cout << "final string should be: " << ostring.str() << std::endl;
//
//   test_string[i] = 1;
//   std::cout << test_string[i] << "i = " << i << std::endl;
//
//   std::cout << "test size is: " << test_string.length() << std::endl;
//   std::cout << test_string << " " << res << "\n";

//   test.step();
//
//   test.generate(10);
//
//   std::cout << test << std::endl;
//
//   std::cout << "Main is done!\n";

  return 0;
}