/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "MarkovModel.hpp"
#include <algorithm>
#include <utility>
#include <map>
#include <string>

/* Creates a Markov model of order k from the given text.
 * Assume that the text has a length of at least k.               */
MarkovModel::MarkovModel(std::string text, int k) {
  _order = k;                    // Set the order.

  // Need to treat the text as circular! So wrap around the first k characters.
  // Add the wrap around portion.
  std::string text_circular = text;   // Make a copy.

  for (int a = 0; a < _order; a++) {
    text_circular.push_back(text[a]);
  }

  int text_len = text.length();  // Find the text's length, easier later on.

  // Now we need to set the alphabet.
  char tmp;
  bool inAlpha = false;

  // Go through the entire text and pick out all the individual letters,
  for (int i = 0; i < text_len; i++) {
    tmp = text.at(i);
    inAlpha = false;

    // See if this letter has been added to the alphabet.
    for (unsigned int y = 0; y < _alphabet.length(); y++) {
      // tmp is already in the alphabet!
      if (_alphabet.at(y) == tmp) {
        inAlpha = true;   // Match it as being in the alphabet.
      }
    }

    // If tmp isn't in the alphabet, isAlpha should be FALSE.
    // So push it back to the alphabet.
    if (!inAlpha) {
      _alphabet.push_back(tmp);
    }
  }

  // Now that we've got the alphabet, why not sort it alphabetically?
  std::sort(_alphabet.begin(), _alphabet.end());

  std::string tmp_str;
  int x, y;

  // Do up to text.length() substring comparisons.
  // This first part just "finds" kgrams and puts a "0" next to them.
  for (x = _order; x <= _order + 1; x++) {
    // Go through the entire text.
    for (y = 0; y < text_len; y++) {
      // This collects all given kgrams, and adds a "0" that we can use
      // later on to increment. We basically find ALL the kgrams, then
      // find their occurrences after.

      // current kgram we want.
      tmp_str.clear();
      tmp_str = text_circular.substr(y, x);

      // Insert the 0.
      _kgrams.insert(std::pair<std::string, int>(tmp_str, 0));
    }
  }

  // Need an iterator for going through the kgrams map.
  std::map<std::string, int>::iterator it;
  int count_tmp = 0;

  // Now let's count the kgrams!
  // Uses same loop as above.
  for (x = _order; x <= _order + 1; x++) {
    // Go through the entire text.
    for (y = 0; y < text_len; y++) {
      // Let's get the current kgram we're comparing against.

      tmp_str.clear();
      tmp_str = text_circular.substr(y, x);

      // Now let's get the kgram's current count.
      it = _kgrams.find(tmp_str);
      count_tmp = it->second;

      // Increment the count by 1.
      count_tmp++;

      // Reinsert the count into the map.
      _kgrams[tmp_str] = count_tmp;
    }
  }

}


// Order k of Markov model
int MarkovModel::order() {
  return _order;
}


/* Number of occurrences of kgram in text.
 * -> Throw an exception if kgram is not of length k              */
int MarkovModel::freq(std::string kgram) {
  // Throw an exception if kgram is not of length k
  if (kgram.length() != (unsigned)_order) {
    throw
      std::runtime_error("Error - kgram not of length k.");
  }

  std::map<std::string, int>::iterator it;

  // Return the number of times that kgram occurs in the text.
  for (it = _kgrams.begin(); it != _kgrams.end(); it++) {
    // See if we found a match.
    if (kgram == it->first) {
      // Got one! So return it->second, which is the # of occurrences.
      return it->second;
    }
  }

  // If we get here, return 0 - we didn't find the given kgram. :'(
  return 0;
}


/* Number of times that character c follows kgram
 * If order = 0, return number of times char c appears
 * -> Throw an exception if kgram is not of length k              */
int MarkovModel::freq(std::string kgram, char c) {
  // Throw an exception if kgram is not of length k
  if (kgram.length() != (unsigned)_order) {
    throw
      std::runtime_error("Error - kgram not of length k.");
  }

  std::map<std::string, int>::iterator it;

  // If kgram is NULL, return number of occurrences of the given character
  // in map.
  std::string tmp(1, c);

  if (kgram.length() == 0) {
    for (it = _kgrams.begin(); it != _kgrams.end(); it++) {
      // See if we found a match.
      if (tmp == it->first) {
        // Got one! So return it->second, which is the # of occurrences.
        return it->second;
      }
    }
  }

  // Adding char c to the kgram, since that's basically what this
  // function is doing - finding the number of times the given kgram
  // is followed by a char c.
  kgram.push_back(c);

  // Otherwise, return the given kgram if we can find it.
  for (it = _kgrams.begin(); it != _kgrams.end(); it++) {
    // See if we found a match.
    if (kgram == it->first) {
      // Got one! So return it->second, which is the # of occurrences.
      return it->second;
    }
  }

  // If we get here, return 0 - we didn't find the given kgram. :'(
  return 0;
}


/* Returns a random character following the given kgram
 * -> Throw an exception if kgram is not of length k.
 * -> Throw an exception if no such kgram.                        */
char MarkovModel::randk(std::string kgram) {
  // Throw an exception if kgram is not of length k.
  if (kgram.length() != (unsigned)_order) {
    throw
    std::runtime_error("Error - kgram not of length k.");
  }

  // Need an iterator for going through the kgrams map.
  std::map<std::string, int>::iterator it;
  it = _kgrams.find(kgram);

  // Throw an exception if no such kgram.
  // So search through and see if we find the kgram.
  if (it == _kgrams.end() ) {
    // We didn't find it. Throw an exception.
    throw
      std::runtime_error("Error - Could not find the given kgram!");
  } else {
    // Found it, let's return a random character
    // that follows the original kgram!
    std::vector<int> probabilities;

    // First find the frequencies of getting a given letter in
    // the alphabet for this kgram.
    for (unsigned int x = 0; x < _alphabet.length(); x++) {
      int prob = freq(kgram, _alphabet[x]);
      probabilities.push_back(prob);

      std::cout << "Prob for " << _alphabet[x] << " is: " << prob << "\n";
    }
  }


  return 'a';
}


/* Generate a string of length T characters by simulating a trajectory
 * through the corresponding Markov chain.
 * The first k characters of the newly generated string should be
 * the argument kgram. ** Assume that T is at least k. **
 * -> Throw an exception if kgram is not of length k.             */
std::string MarkovModel::gen(std::string kgram, int T) {
  std::cout << "gen(string, int)\n";
  return "Hello";
}


/* Overload the stream insertion operator and display the internal
 * state of the Markov Model. Print out the order, the alphabet,
 * and the frequencies of the k-grams and k+1-grams.              */
std::ostream& operator<< (std::ostream &out, MarkovModel &mm) {
  out << "\n_Order: " << mm._order << "\n";
  out << "Alphabet: "<< mm._alphabet << "\n";

  out << "Kgrams map: \n\n";

  std::map<std::string, int>::iterator it;

  for (it = mm._kgrams.begin(); it != mm._kgrams.end(); it++) {
    out << it->first << "\t" << it->second << "\n";
  }

  return out;
}
