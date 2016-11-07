/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include <stdint.h>
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <vector>

class RingBuffer {
 public:
  // API functions

  // Empty ring buffer, with given max capacity.
  explicit RingBuffer(int capacity);
  int size();                 // return # of items in the buffer.
  bool isEmpty();             // is size == 0?
  bool isFull();              // is size == capacity?
  void enqueue(int16_t x);    // add item x to the end.
  int16_t dequeue();          // delete and return item from the front
  int16_t peek();             // return (don't delete) item from the front.

  // Other functions
  void output();

 private:
  std::vector<int16_t> _buffer;
  int _first;
  int _last;
  int _capacity;
  int _size;
};
