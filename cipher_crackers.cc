#include <future>
#include <iostream>
#include <limits.h>
#include <string>
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
  std::vector<std::future<int>> futures = {};
  for (unsigned int i = 0; i < dict.size(); i++) {
    futures.push_back(std::async(levenshtein_distance, dict[i], guess));
  }
  int dictIndex, localDist, minDist = INT_MAX, compScore = 0;
  for (unsigned int i = 0; i < dict.size(); i++) {
    localDist = futures[i].get();
    std::cout << "dist of: " << dict[i] << " is: " << localDist << std::endl;
    if (localDist == 0) {
      compScore -= 1;
    }
    if (localDist < minDist) {
      minDist = localDist;
      dictIndex = i;
    }
  }
  if (minDist == INT_MAX) {
    throw std::runtime_error("expected to compute fitness better than INT_MAX");
  }
  if (compScore < 0) {
    return std::pair<int, int> (compScore, dictIndex);
  } else {
    return std::pair<int, int> (minDist, dictIndex);
  }
}

std::vector<std::vector<int>> get_list_of_probable_shifts(std::string c, int period) {
  std::vector<std::future<std::vector<std::pair<int, float>>>> futures = {};
  for (int j = 0; j < period; j++) {
    futures.push_back(std::async(basic_analysis, c, j, period));
  }

  std::vector<std::vector<int>> res = {};
  for (int j = 0; j < period; j++) {
    std::vector<std::pair<int, float>> tmp = futures[j].get();
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
  std::vector<std::future<std::vector<int>>> futures = {};
  for (int i = 0; i < 10; i++) {
    futures.push_back(std::async(key_of_len_l_guess, c, lenGuesses, dict, lenGuesses[i].first));
  }
  int globMinDist = INT_MAX;
  std::vector<int> bestKeyGuess;
  for (unsigned int i = 0; i < 10; i++) {
    std::vector<int> keyGuess = futures[i].get();
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
  std::vector<int> keyGuess1 = generate_initial_key_guess(c, keyLenGuesses, dict1);
  std::pair<int, int> tmp1 = get_fitness(basic_deciph(c, keyGuess1), dict1);
  if (tmp1.first < 215) {
    // fitness of 215 or better we'll classify as test 1 success
    return dict1[tmp1.second];
  }
  std::vector<int> keyGuess2 = generate_initial_key_guess(c, keyLenGuesses, words1);
  return basic_deciph(c, keyGuess2);
}
