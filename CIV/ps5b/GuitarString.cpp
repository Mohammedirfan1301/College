/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "GuitarString.hpp"
#include <vector>


// Create a guitar string of the given freq using a rate of 44,100
GuitarString::GuitarString(double frequency) {
  std::cout << "GuitarString(double)\n";

  // Round up the frequency
  int freq = ceil(frequency);

  // Ringbuffer will be this large.
  int N = SAMPLING_RATE / freq;

  // Create a new RingBuffer, of size N
  _buff = new RingBuffer(N);

  // Enqueue N (44,100 / freq) 0's.
  for(int i = 0; i < N; i++) {
    _buff->enqueue((int16_t)0);
  }
}


// Create a guitar string with size and initial values of the vector init
GuitarString::GuitarString(std::vector<sf::Int16> init) {
  std::cout << "GuitarString(vector<sf::Int16>()\n";

  // RingBuffer will be as large as the array.
  int N = init.size();

  // Create a new RingBuffer, of size N
  _buff = new RingBuffer(N);

  // Iterator to keep track of the vector.
  std::vector<sf::Int16>::iterator it;

  // Enqueue all the items in the vector.
  for(it = init.begin(); it < init.end(); it++) {
    _buff->enqueue((int16_t)*it);
  }
}


// GuitarString Destructor
GuitarString::~GuitarString() {
  delete _buff;
}


// pluck the guitar string by replacing the buffer with random valuess
void GuitarString::pluck() {
  std::cout << "pluck()\n";

  return;
}


// advance the simulation one time step
void GuitarString::tic() {
  std::cout << "tic()\n";

  return;
}


// return the current sample
sf::Int16 GuitarString::sample() {
  sf::Int16 test = 5.0;

  std::cout << "sample()\n";

  return test;
}


// return number of times tic was called so far
int GuitarString::time() {
  std::cout << "Time()\n";

  return 1;
}
