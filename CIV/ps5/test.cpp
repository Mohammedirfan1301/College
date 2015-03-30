/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include "RingBuffer.hpp"

// Tests various aspects of the contructor.
BOOST_AUTO_TEST_CASE(Constructor) {
  // Normal constructor - shouldn't fail.
  BOOST_REQUIRE_NO_THROW(RingBuffer(100));

  // These should fail.
  BOOST_REQUIRE_THROW(RingBuffer(0), std::exception);
  BOOST_REQUIRE_THROW(RingBuffer(0), std::invalid_argument);
  BOOST_REQUIRE_THROW(RingBuffer(-1), std::invalid_argument);
}


// Checks the size() method
BOOST_AUTO_TEST_CASE(Size) {
  RingBuffer test(1);

  // This should be size 0.
  BOOST_REQUIRE(test.size() == 0);

  test.enqueue(5);

  // This should be size 1.
  BOOST_REQUIRE(test.size() == 1);

  test.dequeue();
  BOOST_REQUIRE(test.size() == 0);
}


// Checks the isEmpty() method
BOOST_AUTO_TEST_CASE(isEmpty) {
  // This should be true
  RingBuffer test(5);
  BOOST_REQUIRE(test.isEmpty() == true);

  // This should be false
  RingBuffer test2(5);
  test2.enqueue(5);
  BOOST_REQUIRE(test2.isEmpty() == false);
}


// Checks the isFull() method
BOOST_AUTO_TEST_CASE(isFull) {
  RingBuffer test(5);
  BOOST_REQUIRE(test.isFull() == false);

  RingBuffer test2(1);
  test2.enqueue(5);
  BOOST_REQUIRE(test2.isFull() == true);
}


// Test enqueue
BOOST_AUTO_TEST_CASE(Enqueue) {
  // These test basic enqueuing
  RingBuffer test(5);

  BOOST_REQUIRE_NO_THROW(test.enqueue(1));
  BOOST_REQUIRE_NO_THROW(test.enqueue(2));
  BOOST_REQUIRE_NO_THROW(test.enqueue(3));
  BOOST_REQUIRE_NO_THROW(test.enqueue(4));
  BOOST_REQUIRE_NO_THROW(test.enqueue(5));
  BOOST_REQUIRE_THROW(test.enqueue(6), std::runtime_error);
}


// Test dequeue
BOOST_AUTO_TEST_CASE(Dequeue) {
  RingBuffer test(5);

  test.enqueue(0);
  test.enqueue(1);
  test.enqueue(2);

  BOOST_REQUIRE(test.dequeue() == 0);
  BOOST_REQUIRE(test.dequeue() == 1);
  BOOST_REQUIRE(test.dequeue() == 2);
  BOOST_REQUIRE_THROW(test.dequeue(), std::runtime_error);
}
