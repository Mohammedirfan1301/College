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
  _order = k;   // Set the order.

  // Now we need to set the alphabet.We should dave it in alphabetical order.
  char tmp;
  bool inAlpha = false;

  // Go through the entire text and pick out all the individual letters,
  for (unsigned int i = 0; i < text.length(); i++) {
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

//   // Need to add "", which is just the # of letters in the text string.
//   _kgrams.insert(std::pair<std::string, int>("", text.length()));
//
//   // Okay, so we've got the alphabet.
//   // Now we gotta figure out the kgrams.
//   // Let's first just try doing A B C D etc.
//   // Basically order 1.
//   int count = 0;
//   std::string kgram;
//
//   // Go through the entire alphabet.
//   for (unsigned int x = 0; x < _alphabet.length(); x++) {
//     count = 0;
//     kgram.clear();
//     kgram = _alphabet[x];
//
//     // Check the given letter in the alphabet.
//     for (unsigned int y = 0; y < text.length(); y++) {
//       // Found a match character!
//       if (_alphabet[x] == text[y]) {
//         count++;
//       }
//     }
//
//     // Save the given kgram and count to the map.
//     _kgrams.insert(std::pair<std::string, int>(kgram, count));
//   }
//
//   // We also need to generate some kgrams.
//   // Order 1 is covered above, so do order 2 and on now.
//   // Can use .compare to compare substrings and what not.
//
  // Do up to _order substring comparisons.
  // This first part just "finds" kgrams and puts a "0" next to them.
  // We do the same loop again to count the kgrams.
  for (int x = 0; x <= _order; x++) {
    // Go through the entire text.
    for (unsigned int y = 0; y < text.length(); y++) {
      // This collects all given kgrams, and adds a "0" that we can use
      // later on to increment. We basically find ALL the kgrams, then
      // find their occurrences after.
      _kgrams.insert(std::pair<std::string, int>(text.substr(y,x), 0));
    }
  }

  // Need an iterator for going through the kgrams map.
  std::map<std::string, int>::iterator it;
  int count_tmp = 0;
  std::string tmp_str;

  // Now let's count the kgrams!
  for (int x = 0; x <= _order; x++) {
    // Go through the entire text.
    for (unsigned int y = 0; y < text.length(); y++) {
      // Let's get the current kgram we're comparing against.
      tmp_str.clear();
      tmp_str = text.substr(y,x);

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
  // Error checking

  // Throw an exception if kgram is not of length k.
  if (kgram.length() != (unsigned)_order) {
    throw
    std::runtime_error("Error - kgram not of length k.");
  }

  // Throw an exception if no such kgram.

  return 'c';
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
