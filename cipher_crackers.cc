#include <iostream>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"
#include "dictionaries.hh"
#include "distance_measures.hh"
#include "frequency_analyzers.hh"
#include "key_length_finders.hh"

// std::vector<std::string> make_guesses(std::string c, std::vector<std::vector<std::pair<int, float>>> keyGuesses) {
//   std::vector<int> mask(keyGuesses.size(), 0);
//   std::vector<int> keyGuess(keyGuesses.size(), 0);
//   std::string pGuess;
//   int ptr = 0;
//   while (std::count(mask.begin(), mask.end(), 5) < keyGuesses.size()) {
//     for (int i = 0; i < keyGuesses.size(); i++) {
//       keyGuess[i] = keyGuesses[i][mask[i]].first;
//     }
//     pGuess = basic_deciph(c, keyGuess);
//     if (dict1Map[pGuess] == true) {
//       std::cout << "found: " << pGuess << std::endl;
//     }
//     mask[ptr] += 1;
//     ptr = (ptr + 1) % keyGuesses.size();
//   }
//   return { "" };
// }

std::pair<int, int> get_closest_dist(std::string c, std::vector<int> k) {
  std::string g = basic_deciph(c, k);
  // std::cout << "guess is: " << g << std::endl;
  int dist, lowestDist = 10000000, index;
  for (int i = 0; i < dict1.size(); i++) {
    dist = levenshtein_distance(dict1[i], g);
    if (dist < lowestDist) {
      lowestDist = dist;
      index = i;
    }
  }
  return std::pair<int, int> (lowestDist, index);
}

std::vector<int> generate_initial_key_guess(std::string c, int len) {
  std::vector<int> keyGuess(len);
  for (int j = 0; j < len; j++) {
    std::vector<std::pair<int, float>> shiftGuesses = basic_analysis(c, j, len);
    keyGuess[j] = shiftGuesses[0].first;
  }
  return keyGuess;
}

std::string basic_crack(std::string c) {
  std::vector<std::pair<int, float>> keyLens = basic_find(c);
  std::vector<int> initialKeyGuess;
  int lowestDist = 10000000, index;
  for (int i = 0; i < keyLens.size(); i++) {
    initialKeyGuess = generate_initial_key_guess(c, keyLens[i].first);
    std::pair<int, int> h = get_closest_dist(c, initialKeyGuess);
    if (h.first < lowestDist) {
      lowestDist = h.first;
      index = h.second;
      if (lowestDist < dict1[index].length() - 300) {
        // for random strings levenshtein distance is roughly avg of length of
        // both strings, improvement to 40% of that pretty much guarantees match
        break;
      }
    }
  }
  // std::cout << "TAKING A GUESS! lowest dist is: " << lowestDist << std::endl;
  return dict1[index];
}
