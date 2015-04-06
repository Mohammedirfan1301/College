/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "GuitarString.hpp"
#include <vector>


// Create a guitar string of the given freq using a rate of 44,100
GuitarString::GuitarString(double frequency):
                                      _buff(ceil(SAMPLING_RATE / frequency)) {
  // Ringbuffer will be this large.
  _N = ceil(SAMPLING_RATE / frequency);

  // Enqueue N (44,100 / freq) 0's.
  for (int i = 0; i < _N; i++) {
    _buff.enqueue((int16_t)0);
  }

  // Set _tic to 0 for the tic / time methods.
  _tic = 0;
}


// Create a guitar string with size and initial values of the vector init
GuitarString::GuitarString(std::vector<sf::Int16> init):
                                                        _buff(init.size()) {
  // RingBuffer will be as large as the array.
  _N = init.size();

  // Iterator to keep track of the vector.
  std::vector<sf::Int16>::iterator it;

  // Enqueue all the items in the vector.
  for (it = init.begin(); it < init.end(); it++) {
    _buff.enqueue((int16_t)*it);
  }

  // Set _tic to 0 for the tic / time methods.
  _tic = 0;
}


// pluck the guitar string by replacing the buffer with random valuess
void GuitarString::pluck() {
  // Remove N items
  for (int i = 0; i < _N; i++) {
    _buff.dequeue();
  }

  // Add N random items between -32768 to 32767
  for (int i = 0; i < _N; i++) {
    _buff.enqueue((sf::Int16)(rand() & 0xffff)); //NOLINT
  }

  return;
}


// advance the simulation one time step
void GuitarString::tic() {
  // First get the first value, and dequeue it at the same time.
  int16_t first = _buff.dequeue();

  // Get the second value (DON'T dequeue it)
  int16_t second = _buff.peek();

  // Now we can apply the Karplus-Strong update:
  // Take the first two values, average them and multiply by the
  // ENERGY_DECAY_FACTOR
  int16_t avg = (first + second) / 2;
  int16_t karplus = avg * ENERGY_DECAY_FACTOR;

  // Debugging code.
//   std::cout << "Karplus is: " << karplus << "\n";

  // Now enqueue the Karplus-Strong update.
  _buff.enqueue((sf::Int16)karplus);

  _tic++;

  return;
}


// return the current sample
sf::Int16 GuitarString::sample() {
  // Get the value of the item at the front of the RingBuffer
  sf::Int16 sample = (sf::Int16)_buff.peek();

  return sample;
}


// return number of times tic was called so far
int GuitarString::time() {
  return _tic;
}
