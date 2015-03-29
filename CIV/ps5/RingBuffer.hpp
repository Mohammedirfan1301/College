/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <stdint.h>
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>

class RingBuffer {
 public:
  RingBuffer(int capacity);   // Empty ring buffer, with given max capacity.
  int size();                 // return # of items in the buffer.
  bool isEmpty();             // is size == 0?
  bool isFull();              // is size == capacity?
  void enqueue(int16_t x);    // add item x to the end.
  int16_t dequeue();          // delete and return item from the front
  int16_t peek();             // return (don't delete) item from the front.

 private:

};

#endif