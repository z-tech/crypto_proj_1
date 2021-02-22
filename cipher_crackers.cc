// #include <boost/thread.hpp>
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
  std::vector<std::vector<int>> guesses = {};
  int globMinDist = INT_MAX;
  std::vector<int> bestKeyGuess;
  // 1) for each of the top 3 *shrug emoji* potential key lengths based on index of coincidence
  // std::vector<boost::unique_future<std::vector<int>>> futures;
  for (int i = 0; i < 3; i++) {
    int keyLen = lenGuesses[i].first;
    std::vector<int> keyGuess = key_of_len_l_guess(c, lenGuesses, dict, keyLen);
    // boost::packaged_task<std::vector<int>> pt(key_of_len_l_guess, c, lenGuesses, dict, lenGuesses[i].first);
    // futures.push_back(pt.get_future());
    // boost::thread task(std::move(pt));
  //}
  //boost::wait_for_all(futures.begin(), futures.end());
  //return futures[0].get();
    // 5) lastly, check if fitness of this key is better than fitness of current best guess
    std::pair<int, int> chk = get_fitness(basic_deciph(c, keyGuess), dict);
    if (chk.first < globMinDist) {
      globMinDist = chk.first;
      bestKeyGuess = keyGuess;
      // // DEBUG
      // std::cout << "\nnew globMinDist: " << globMinDist << std::endl;
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
