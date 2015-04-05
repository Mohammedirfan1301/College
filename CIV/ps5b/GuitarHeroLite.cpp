/*
  Copyright 2015 Fred Martin, fredm@cs.uml.edu
  Mon Mar 30 08:58:49 2015

  based on Princeton's GuitarHeroLite.java
  www.cs.princeton.edu/courses/archive/fall13/cos126/assignments/guitar.html

  build with
  g++ -Wall -c GuitarHeroLite.cpp -lsfml-system \
     -lsfml-audio -lsfml-graphics -lsfml-window
  g++ -Wall GuitarHeroLite.o RingBuffer.o GuitarString.o \
   -o GuitarHeroLite -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <math.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "RingBuffer.hpp"
#include "GuitarString.hpp"

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100

vector<sf::Int16> makeSamplesFromString(GuitarString gs) {
  std::vector<sf::Int16> samples;

  gs.pluck();
  int duration = 8;  // seconds
  int i;
  for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
    gs.tic();
    samples.push_back(gs.sample());
  }

  return samples;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(300, 200), "SFML Guitar Hero Lite");
  sf::Event event;
  double freq;
  vector<sf::Int16> samples;

  // we're reusing the freq and samples vars, but
  // there are separate copies of GuitarString, SoundBuffer, and Sound
  //   for each note
  //
  // GuitarString is based on freq
  // samples are generated from GuitarString
  // SoundBuffer is loaded from samples
  // Sound is set to SoundBuffer

  freq = CONCERT_A;
  GuitarString gs1 = GuitarString(freq);
  sf::Sound sound1;
  sf::SoundBuffer buf1;
  samples = makeSamplesFromString(gs1);
  if (!buf1.loadFromSamples(&samples[0], samples.size(), 2, SAMPLES_PER_SEC))
    throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
  sound1.setBuffer(buf1);

  freq = CONCERT_A * pow(2, 3.0/12.0);
  GuitarString gs2 = GuitarString(freq);
  sf::Sound sound2;
  sf::SoundBuffer buf2;
  samples = makeSamplesFromString(gs2);
  if (!buf2.loadFromSamples(&samples[0], samples.size(), 2, SAMPLES_PER_SEC))
    throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
  sound2.setBuffer(buf2);

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        switch (event.key.code) {
        case sf::Keyboard::A:
          sound1.play();
          break;
        case sf::Keyboard::C:
          sound2.play();
          break;
        default:
          break;
        }

      default:
        break;
      }

      window.clear();
      window.display();
    }
  }
  return 0;
}

