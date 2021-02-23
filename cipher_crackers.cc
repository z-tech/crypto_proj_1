#include <future>
#include <iostream>
#include <limits.h>
#include <string>
#include <thread>
#include <vector>

#include "cipher_algorithms.hh"
#include "dictionaries.hh"
#include "distance_measures.hh"
#include "frequency_analyzers.hh"
#include "key_length_finders.hh"

std::pair<int, int> get_fitness(std::string guess, std::vector<std::string> dict) {
  if (dict.size() == 0) {
    throw std::invalid_argument("expected dictionary to have length greater than zero");
  }
  int dictIndex, localDist, minDist = INT_MAX;
  for (int i = 0; i < dict.size(); i++) {
    localDist = levenshtein_distance(dict[i], guess);
    if (localDist < minDist) {
      minDist = localDist;
      dictIndex = i;
    }
  }
  if (minDist == INT_MAX) {
    throw std::runtime_error("expected to compute fitness better than INT_MAX");
  }
  return std::pair<int, int> (minDist, dictIndex);
}

std::vector<std::vector<int>> get_list_of_probable_shifts(std::string c, int period) {
  std::vector<std::vector<int>> res = {};
  for (int j = 0; j < period; j++) {
    std::vector<std::pair<int, float>> tmp = basic_analysis(c, j, period);
    std::vector<int> s = {};
    for (int i = 0; i < 5; i++) {
      s.push_back(tmp[i].first);
    }
    res.push_back(s);
  }
  return res;
}

std::vector<int> key_of_len_l_guess(std::string c, std::vector<std::pair<int, float>> lenGuesses, std::vector<std::string> dict, int keyLen) {
  // 1) for every index in this key length, frequency analyze for most probable shift values
  std::vector<std::vector<int>> probableShifts = get_list_of_probable_shifts(c, keyLen);
  // 2) then using the most probable at each index create a "base" guess of this key
  std::vector<int> keyGuess = {};
  for (int j = 0; j < keyLen; j++) {
    keyGuess.push_back(probableShifts[j][0]);
  }
  // 3) finally, "hill climb" by swapping probable shift values at each index, comparing fitness
  for (int j = 0; j < keyLen; j++) {
    int minIndex = 0;
    int minDist = INT_MAX;
    for (int k = 0; k < 4; k++) {
      keyGuess[j] = probableShifts[j][k];
      std::pair<int, int> tmp = get_fitness(basic_deciph(c, keyGuess), dict);
      if (tmp.first < minDist) {
        minDist = tmp.first;
        minIndex = k;
      }
    }
    keyGuess[j] = probableShifts[j][minIndex];
  }
  // 4) unlikely to be exact, but better than many other guesses
  return keyGuess;
}

std::vector<int> generate_initial_key_guess(std::string c, std::vector<std::pair<int, float>> lenGuesses, std::vector<std::string> dict) {
  // 1) for each of the top 2 *shrug emoji* potential key lengths based on index of coincidence
  auto future1 = std::async(key_of_len_l_guess, c, lenGuesses, dict, lenGuesses[0].first);
  auto future2 = std::async(key_of_len_l_guess, c, lenGuesses, dict, lenGuesses[1].first);
  // auto future3 = std::async(key_of_len_l_guess, c, lenGuesses, dict, lenGuesses[2].first);
  // auto future4 = std::async(key_of_len_l_guess, c, lenGuesses, dict, lenGuesses[3].first);
  std::vector<std::vector<int>> guesses = {};
  guesses.push_back(future1.get());
  guesses.push_back(future2.get());
  // guesses.push_back(future3.get());
  // guesses.push_back(future4.get());
  int globMinDist = INT_MAX;
  std::vector<int> bestKeyGuess;
  for (int i = 0; i < guesses.size(); i++) {
    std::vector<int> keyGuess = guesses[i];
    std::pair<int, int> chk = get_fitness(basic_deciph(c, keyGuess), dict);
    // // DEBUG
    // std::cout << "\ndist: " << chk.first << std::endl;
    if (chk.first < globMinDist) {
      globMinDist = chk.first;
      bestKeyGuess = keyGuess;
    }
  }
  return bestKeyGuess;
}

std::string basic_crack(std::string c) {
  std::vector<std::pair<int, float>> keyLenGuesses = basic_find(c);
  std::vector<int> keyGuess = generate_initial_key_guess(c, keyLenGuesses, dict1);
  std::pair<int, int> tmp = get_fitness(basic_deciph(c, keyGuess), dict1);
  return dict1[tmp.second];
}
