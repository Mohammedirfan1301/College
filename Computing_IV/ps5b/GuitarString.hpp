/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#ifndef GUITARSTRING_HPP
#define GUITARSTRING_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "RingBuffer.hpp"

const int SAMPLING_RATE = 44100;
const double ENERGY_DECAY_FACTOR = 0.996;

class GuitarString {
 public:
  // create a guitar string of the given freq using a rate of 44,100
  explicit GuitarString(double frequency);

  // create a guitar string with size and initial values of the vector init
  explicit GuitarString(std::vector<sf::Int16> init);

  // pluck the guitar string by replacing the buffer with random valuess
  void pluck();
  void tic();              // advance the simulation one time step
  sf::Int16 sample();      // return the current sample
  int time();              // return number of times tic was called so far
 private:
  RingBuffer _buff;
  int _N;
  int _tic;
};
#endif
