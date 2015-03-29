/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "RingBuffer.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

// Tests various aspects of the contructor.
BOOST_AUTO_TEST_CASE(Constructor)
{
  // Create a size 3 RingBuffer
  RingBuffer test(3);

  BOOST_REQUIRE(true);
}
