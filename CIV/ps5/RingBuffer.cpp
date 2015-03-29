/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "RingBuffer.hpp"


// Empty ring buffer, with given max capacity.
RingBuffer::RingBuffer(int capacity) {
  std::cout << "Hello world.\n";

  return;
}


// return # of items in the buffer.
int RingBuffer::size() {
  std::cout << "Size is blah blah\n";

  return 1;
}


// is size == 0?
bool RingBuffer::isEmpty() {
  std::cout << "NOT IMPLEMENTED YET.\n";

  return false;
}


// is size == capacity?
bool RingBuffer::isFull() {
  std::cout << "NOT IMPLEMENTED YET.\n";

  return false;
}


// add item x to the end.
void RingBuffer::enqueue(int16_t x) {
  std::cout << "NOT IMPLEMENTED YET.\n";

  return;
}


// delete and return item from the front
int16_t dequeue() {
  std::cout << "NOT IMPLEMENTED YET.\n";

  return 1;
}


// return (don't delete) item from the front.
int16_t peek() {
  std::cout << "NOT IMPLEMENTED YET.\n";

  return 1;
}

