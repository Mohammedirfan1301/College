/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#ifndef MARKOVMODEL_HPP
#define MARKOVMODEL_HPP
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <stdexcept>


class MarkovModel {
 public:
  /* Creates a Markov model of order k from the given text.
   * Assume that the text has a length of at least k.               */
  MarkovModel(std::string text, int k);

  // Order k of Markov model
  int order();

  /* Number of occurrences of kgram in text.
   * -> throw an exception if kgram is not of length k              */
  int freq(std::string kgram);

  /* Number of times that character c follows kgram
   * If order = 0, return number of times char c appears
   * -> throw an exception if kgram is not of length k              */
  int freq(std::string kgram, char c);

  /* Random character following given kgram
   * -> Throw an exception if kgram is not of length k.
   * -> Throw an exception if no such kgram.                        */
  char randk(std::string kgram);

  /* Generate a string of length T characters by simulating a
   * trajectory through the corresponding Markov chain.
   * The first k characters of the newly generated string should be
   * the argument kgram. ** Assume that T is at least k. **
   * -> Throw an exception if kgram is not of length k.             */
  std::string gen(std::string kgram, int T);

  /* overload the stream insertion operator and display the internal
   * state of the Markov Model. Print out the order, the alphabet,
   * and the frequencies of the k-grams and k+1-grams.              */
  friend std::ostream& operator<< (std::ostream &out, MarkovModel &mm);

 private:
  int _order;
  std::map <std::string, int> _kgrams;
  std::string _alphabet;
};
#endif
