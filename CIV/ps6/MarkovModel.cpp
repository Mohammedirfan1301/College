/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "MarkovModel.hpp"
#include <utility>
#include <map>
#include <string>

/* Creates a Markov model of order k from the given text.
 * Assume that the text has a length of at least k.               */
MarkovModel::MarkovModel(std::string text, int k) {
  // Not really sure how to do this, so let's just set some
  // default values for testing.

  _order = k;
  _alphabet = "abcdef";
  _kgrams.insert(std::pair<std::string, int>("hello", 5));
}


// Order k of Markov model
int MarkovModel::order() {
  return _order;
}


/* Number of occurrences of kgram in text.
 * -> throw an exception if kgram is not of length k              */
int MarkovModel::freq(std::string kgram) {
  // Error checking
  if (kgram.length() != (unsigned)_order) {
    throw
      std::runtime_error("Error - kgram not of length k.");
  }

  return 1;
}


/* Number of times that character c follows kgram
 * If order = 0, return number of times char c appears
 * -> throw an exception if kgram is not of length k              */
int MarkovModel::freq(std::string kgram, char c) {
  // Error checking
  if (kgram.length() != (unsigned)_order) {
    throw
      std::runtime_error("Error - kgram not of length k.");
  }

  return 1;
}


/* Random character following given kgram
 * -> Throw an exception if kgram is not of length k.
 * -> Throw an exception if no such kgram.                        */
char MarkovModel::randk(std::string kgram) {
  std::cout << "randk(string)\n";
  return 'c';
}


/* Generate a string of length T characters by simulating a
 * trajectory through the corresponding Markov chain.
 * The first k characters of the newly generated string should be
 * the argument kgram. ** Assume that T is at least k. **
 * -> Throw an exception if kgram is not of length k.             */
std::string MarkovModel::gen(std::string kgram, int T) {
  std::cout << "gen(string, int)\n";
  return "Hello";
}


/* overload the stream insertion operator and display the internal
 * state of the Markov Model. Print out the order, the alphabet,
 * and the frequencies of the k-grams and k+1-grams.              */
std::ostream& operator<< (std::ostream &out, MarkovModel &mm) {
  out << "\nHello World.\n";
  out << "Outputting the object: \n\n";
  out << "_Order: " << mm._order << "\n";
  out << "Alphabet: "<< mm._alphabet << "\n";

  out << "Kgrams map: \n\n";

  std::map<std::string, int>::iterator it;

  for (it = mm._kgrams.begin(); it != mm._kgrams.end(); it++) {
    out << it->first << "\t" << it->second << "\n";
  }

  return out;
}
