/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
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

#define CONCERT_A 440.0
#define SAMPLES_PER_SEC 44100
const int keyboard_size = 37;

std::vector<sf::Int16> makeSamplesFromString(GuitarString gs) {
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
  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Guitar Hero");
  sf::Event event;

  // sample vector / freq - all reused.
  double freq;
  std::vector<sf::Int16> sample;

  // Samples vector of a vector
  std::vector<std::vector<sf::Int16>> samples(keyboard_size);
  std::vector<sf::SoundBuffer> buffers(keyboard_size);
  std::vector<sf::Sound> sounds(keyboard_size);

  // From Princeton.
  std::string keyboard = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";

  // For loop to go through the entire keyboard.
  for (int i = 0; i < (signed)keyboard.size(); i++) {
    // Set the frequency and make a GuitarString.
    freq = CONCERT_A * pow(2, ( (i - 24)/12.0));
    GuitarString tmp = GuitarString(freq);

    // Make a vector of sf::Int16, will act as a sample.
    sample = makeSamplesFromString(tmp);
    samples[i] = sample;

    // Load the above same into the buffer vector.
    if (!buffers[i].loadFromSamples(&samples[i][0],
        samples[i].size(), 2, SAMPLES_PER_SEC)) {
      throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
    }

    // Now load the buffer into a sf::sound.
    sounds[i].setBuffer(buffers[i]);
  }

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::TextEntered) {
          // This detects unicode characters
          if (event.text.unicode < 128) {
            // Convert the key from unicode to ASCII
            char key = static_cast<char>(event.text.unicode);

            // Now go through the keyboard string and if we find a match,
            // then access that sound and play it.
            for (int i = 0; i < (signed)keyboard.size(); i++) {
              if (keyboard[i] == key) {
                std::cout << "Keyboard key is: " << keyboard[i] << "\n";
                std::cout << "Attempting to play sound...\n";
                sounds[i].play();
                break;
              }
            }
          }
        }
      }

    window.clear();
    window.display();
  }
  return 0;
}

