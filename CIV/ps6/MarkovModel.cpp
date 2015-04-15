/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "MarkovModel.hpp"
#include <algorithm>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>
#include <utility>

/* Creates a Markov model of order k from the given text.
 * Assume that the text has a length of at least k.               */
MarkovModel::MarkovModel(std::string text, int k) {
  // Set the order.
  _order = k;

  // Seed the random number generator for later.
  srand((int)time(NULL)); //NOLINT

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
      // Also ignore upper case,
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

  // Use std::map::find to see if we can find the kgram.
  std::map<std::string, int>::iterator it;
  it = _kgrams.find(kgram);

  // If it equals map::end, we didn't find it, so return 0.
  if (it == _kgrams.end()) {
    return 0;
  }

  // Other wise return the given kgram since we found it.
  return it->second;
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

  // use std::map::find to see if we can find the kgram + c.
  std::map<std::string, int>::iterator it;
  kgram.push_back(c);
  it = _kgrams.find(kgram);

  // If it equals map::end, we didn't find it, so return 0.
  if (it == _kgrams.end()) {
    return 0;
  }

  // Other wise return the given kgram since we found it.
  return it->second;
}


/* Returns a random character following the given kgram
 * -> Throw an exception if kgram is not of length k.
 * -> Throw an exception if no such kgram.                        */
char MarkovModel::randk(std::string kgram) {
  // Throw an exception if kgram is not of length k.
  if (kgram.length() != (unsigned)_order) {
    throw std::runtime_error("Error - kgram not of length k (randk)");
  }

  // Need an iterator for going through the kgrams map.
  std::map<std::string, int>::iterator it;

  // Search through and see if we find the given kgram.
  it = _kgrams.find(kgram);

  // We didn't find it. Throw an exception.
  if (it == _kgrams.end()) {
    throw std::runtime_error("Error - Could not find the given kgram! (randk)");
  }

  // DEBUGGING
//   std::cout << "\n\n\n";

  // Get the freq of the given kgram. (we will rand by this number!)
  int kgram_freq = freq(kgram);

  // MORE DEBUG STATEMENTS.
//   std::cout << "Freq of kgram is: " << kgram_freq << "\n";

  // Picking a random int from the possible characters.
  // This should be an int from 1 to the total number of possible letters.
  int random_value = rand() % kgram_freq; //NOLINT

  // Debugging
//   std::cout << "Random number value is: " << random_value << "\n";

  double test_freq = 0;
  double random_num = static_cast<double>(random_value) / kgram_freq;
  double last_values = 0;

  // Non Bugz
//  std::cout << "Random num as a double / kgram_freq = " << random_num << "\n";

  // Go through all the letters.
  for (unsigned int a = 0; a < _alphabet.length(); a++) {
    // This line basically calculates the probability as a double.
    test_freq =  static_cast<double>(freq(kgram, _alphabet[a])) / kgram_freq;

    // Some debug couts
//     std::cout << "Letter: " << _alphabet[a] << " -> Freq for that letter: ";
//     std::cout << test_freq << "\n";

    // NOTE: I'm comparing our random number, which we got from rand()ing
    // the kgram_freq against the test freq, and making that test_freq is
    // NOT 0. My logic is if a letter has "0" appearences in the kgram,
    // then its probability of showing up is exactly 0 / kgram_freq, which
    // is 0. I add the sum of all the last values as well as that is how
    // you do this sort of math.
    // Credit to the amazing stackoverflow post which gave me this idea,
    // but I actually turned it into a more "dynamic" implemenation by adding
    // the sum of all the last frequencies.
    if (random_num < test_freq + last_values && test_freq != 0) {
      // Return this letter since it matches.
      return _alphabet[a];
    }

    // I think the above comment details this nicely. Its basically a sum
    // counter for all of the last few frequencies. I add them up here to
    // avoid missing the second frequency by mistake. I think it would also
    // possibly cause the below "return '-'" statement too, since if you sum
    // something before you expect to its going to cause an error.
    last_values += test_freq;
  }

  // This is here for error checking. We should never reach this point unless
  // something in the above code is wrong.
  return '-';
}


/* Generate a string of length T characters by simulating a trajectory
 * through the corresponding Markov chain.
 * The first k characters of the newly generated string should be
 * the argument kgram. ** Assume that T is at least k. **
 * -> Throw an exception if kgram is not of length k.             */
std::string MarkovModel::gen(std::string kgram, int T) {
  // Throw an exception if kgram is not of length k.
  if (kgram.length() != (unsigned)_order) {
    throw std::runtime_error("Error - kgram not of length k. (gen)");
  }

  // We need to take the given kgram, and add "T" characters to it, based
  // on the given kgram's frequencies and whatever we add to its frequencies.
  // This confused me at first and I think I now understand how to deal with
  // this function.

  // We first call randk on the original kgram, then we append add it to
  // a new string with both the original kgram and the new character.
  // We note that "T" is the final length of the string, so if we have a
  // order 2 kgram, and T equals 4, we gotta add just two characters.
  // So we keep running until we've hit string length of T.

  // The final string we will return. We'll build it up over time.
  std::string final_string = "";

  // Temp char for using to collect the return value from randk()
  char return_char;

  // Add the kgram to it.
  final_string += "" + kgram;

  // Now the magic loop - loop until final_string's length equals T.
  // Which, T - the length of the kgram can get us there!
  for (unsigned int a = 0; a < (T - (unsigned)_order); a++) {
    // Call randk on the substring we're looking at.
    // Note we want just _order long kgram to compare against.
    return_char = randk(final_string.substr(a, _order));

    // Add the return_char to final_string
    final_string.push_back(return_char);

    // Keep looping til it stops.
  }

  // When we get here, we're done. YAY.
  return final_string;
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
