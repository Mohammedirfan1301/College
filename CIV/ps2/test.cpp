#include <iostream>
#include <string>
#include <sstream>
#include "LFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

// The initial test that was in this file.
BOOST_AUTO_TEST_CASE(fiveBitsTapAtTwo)
{
  LFSR l("00111", 2);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 0);

  LFSR l2("00111", 2);
  BOOST_REQUIRE(l2.generate(8) == 198);
}


// My first test. I just tested what Princeton's
// website gave as examples.
// In this case, they use 11 bit seeds with a tap of 8.
BOOST_AUTO_TEST_CASE(PrincetonExamples)
{
  // The simulate step test
  LFSR test("01101000010", 8);

  BOOST_REQUIRE(test.step() == 1);
  BOOST_REQUIRE(test.step() == 1);
  BOOST_REQUIRE(test.step() == 0);
  BOOST_REQUIRE(test.step() == 0);
  BOOST_REQUIRE(test.step() == 1);
  BOOST_REQUIRE(test.step() == 0);
  BOOST_REQUIRE(test.step() == 0);
  BOOST_REQUIRE(test.step() == 1);
  BOOST_REQUIRE(test.step() == 0);
  BOOST_REQUIRE(test.step() == 0);

  // The generate test from Princeton
  LFSR test2("01101000010", 8);
  BOOST_REQUIRE(test2.generate(5) == 25);
  BOOST_REQUIRE(test2.generate(5) == 4);
  BOOST_REQUIRE(test2.generate(5) == 30);
  BOOST_REQUIRE(test2.generate(5) == 27);
  BOOST_REQUIRE(test2.generate(5) == 18);
  BOOST_REQUIRE(test2.generate(5) == 26);
  BOOST_REQUIRE(test2.generate(5) == 28);
  BOOST_REQUIRE(test2.generate(5) == 24);
  BOOST_REQUIRE(test2.generate(5) == 23);
  BOOST_REQUIRE(test2.generate(5) == 29);
}


// A couple of tests making sure the constructor functions
// as intended. This also tests the << operator as well.
BOOST_AUTO_TEST_CASE(Constructor_Tests)
{
  LFSR test("001100", 5);
  std::stringstream buffer;
  buffer << test;

  // Make sure the constructor saves the seed correctly.
  BOOST_REQUIRE(buffer.str().compare("001100") == 0);

  // Try a much larger seed - 30 bits for example.
  LFSR test2("0000000111111111001010101011", 10);
  buffer.str("");   // Clear the stringstream object
  buffer.clear();
  buffer << test2;

  // Make sure the constructor saves the seed correctly.
  BOOST_REQUIRE(buffer.str().compare("0000000111111111001010101011") == 0);

  // Now try a very small seed - 1 bit for example.
  LFSR test3("1", 1);
  buffer.str("");   // Clear the stringstream object
  buffer.clear();
  buffer << test3;

  // Make sure the constructor saves the seed correctly.
  BOOST_REQUIRE(buffer.str().compare("1") == 0);
}



