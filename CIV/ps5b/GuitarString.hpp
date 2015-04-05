/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "RingBuffer.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

const int SAMPLING_RATE = 44100;

class GuitarString {
 public:
  // create a guitar string of the given freq using a rate of 44,100
  GuitarString(double frequency);

  // create a guitar string with size and initial values of the vector init
  GuitarString(std::vector<sf::Int16> init);

  // Guitar string destructor
  ~GuitarString();

  // pluck the guitar string by replacing the buffer with random valuess
  void pluck();
  void tic();              // advance the simulation one time step
  sf::Int16 sample();      // return the current sample
  int time();              // return number of times tic was called so far
 private:
  RingBuffer *_buff;
};
