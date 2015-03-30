/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "RingBuffer.hpp"

// Create an empty ring buffer, with given max capacity.
RingBuffer::RingBuffer(int capacity) {
  if (capacity < 1) {
    throw
    std::invalid_argument("RB constructor: capacity must be greater than zero");
  }

  _last = 0;
  _first = 0;
  _size = 0;
  _capacity = capacity;
  _buffer.resize(capacity);

  return;
}


// Return # of items in the buffer.
int RingBuffer::size() {
  return _size;
}


// Is size == 0?
bool RingBuffer::isEmpty() {
  // Determine if the RingBuffer is empty.
  if (_size == 0) {
    return true;
  } else {
    return false;
  }
}


// Is size == capacity?
bool RingBuffer::isFull() {
  // Determine if size equals capacity.
  if (_size == _capacity) {
    return true;
  } else {
    return false;
  }
}


// Add item x to the end.
void RingBuffer::enqueue(int16_t x) {
  // See if the buffer is full
  if (isFull()) {
    throw
      std::runtime_error("enqueue: can't enqueue to a full ring");
  }

  // Check to see if we need to loop last back around to 0.
  if (_last >= _capacity) {
    _last = 0;
  }

  // If we don't throw any exceptions, then continue on!
  _buffer.at(_last) = x;

  // Increase counter variables.
  _last++;
  _size++;
}


// Delete and return item from the front
int16_t RingBuffer::dequeue() {
  if (isEmpty()) {
    throw
      std::runtime_error("dequeue: can't dequeue to an empty ring");
  }

  // Remove from the front.
  int16_t first = _buffer.at(_first);
  _buffer.at(_first) = 0;

  // Decrease counter variables.
  _first++;
  _size--;

  // Check to see if we need to loop first back around to 0.
  if (_first >= _capacity) {
    _first = 0;
  }

  return first;
}


// Return (don't delete) item from the front.
int16_t RingBuffer::peek() {
  // This is an easy function - return the first buffer position.
  if (isEmpty()) {
    throw
      std::runtime_error("peek: can't peek an empty ring");
  }

  return _buffer.at(_first);
}


// Dumps the variables to stdout
void RingBuffer::output() {
  std::cout << "   First: " << _first << "\n";
  std::cout << "    Last: " << _last << "\n";
  std::cout << "Capacity: " << _capacity << "\n";
  std::cout << "    Size: " << _size << "\n";
  std::cout << "Vector size: " << _buffer.size() << "\n";
  std::cout << "Vector capacity: " << _buffer.capacity() << "\n";
  std::cout << "Buffer (no blanks): \n";

  int x = 0;
  int y = _first;

  while (x < _size) {
    // Make the loop go back to 0 to continue printing.
    if (y >= _capacity) {
      y = 0;
    }

    std::cout << _buffer[y] << " ";
    y++;
    x++;
  }

  std::cout << "\nDump the entire buffer (including blanks): \n";

  for (int x = 0; x < _capacity; x++) {
    std::cout << _buffer[x] << " ";
  }

  std::cout << "\n\n";
}


