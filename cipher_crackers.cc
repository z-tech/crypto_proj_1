#include <iostream>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"
#include "dictionaries.hh"
#include "distance_measures.hh"
#include "frequency_analyzers.hh"
#include "key_length_finders.hh"

std::pair<int, int> compare_to_dict1(std::string guess) {
  int dist, minDist = 10000000, dictIndex;
  for (int i = 0; i < dict1.size(); i++) {
    dist = levenshtein_distance(dict1[i], guess);
    if (dist < minDist) {
      minDist = dist;
      dictIndex = i;
    }
  }
  return std::pair<int, int> (minDist, dictIndex);
}

// std::vector<int> get_list_of_probable_shifts(std::string c, int start, int period) {
//   std::vector<std::pair<int, float>> tmp = basic_analysis(c, start, period);
//   std::vector<int> res = {};
//   for (int i = 0; i < 5; i++) {
//     res.push_back(tmp[i].first);
//   }
//   return res;
// }

std::vector<std::vector<int>> generate_initial_key_guesses(std::string c, std::vector<std::pair<int, float>> lenGuesses) {
  std::vector<std::vector<int>> guesses = {};
  for (int i = 0; i < 5; i++) { // top 5 potential key lengths *shrug emoji*
    int len = lenGuesses[i].first;
    std::vector<int> guess(len);
    std::vector<std::vector<std::pair<int, float>>> probableShiftsAtIndex(len);
    for (int j = 0; j < len; j++) {
      probableShiftsAtIndex[j] = basic_analysis(c, j, len);
      guess[j] = probableShiftsAtIndex[j][0].first;
    }
    for (int j = 0; j < len; j++) {
      guess[j] = probableShiftsAtIndex[j][0].first; // redundant
      std::pair<int, int> t0 = compare_to_dict1(basic_deciph(c, guess));
      guess[j] = probableShiftsAtIndex[j][1].first;
      std::pair<int, int> t1 = compare_to_dict1(basic_deciph(c, guess));
      guess[j] = probableShiftsAtIndex[j][2].first;
      std::pair<int, int> t2 = compare_to_dict1(basic_deciph(c, guess));
      if (t0.first <= t1.first && t0.first <= t2.first) {
        guess[j] = probableShiftsAtIndex[j][0].first;
      } else if (t1.first <= t0.first && t1.first <= t2.first) {
        guess[j] = probableShiftsAtIndex[j][1].first;
      } else {
        guess[j] = probableShiftsAtIndex[j][2].first;
      }
    }
    guesses.push_back(guess);
  }
  return guesses;
}

bool sort_distances(std::pair<int, std::vector<int>> a, std::pair<int, std::vector<int>> b) {
  return a.first < b.first;
}

std::string basic_crack(std::string c) {
  std::vector<std::pair<int, float>> keyLenGuesses = basic_find(c);
  std::vector<std::vector<int>> initialkeyGuesses = generate_initial_key_guesses(c, keyLenGuesses);
  // it is extremely unlikely that any of these key guesses are correct, but we
  // should be able to argue that some are "closer" to the actual key than others
  std::vector<std::pair<int, std::vector<int>>> distances = {};
  for(int i = 0; i < initialkeyGuesses.size(); i++) {
    std::pair<int, int> dist = compare_to_dict1(basic_deciph(c, initialkeyGuesses[i]));
    distances.push_back(std::pair<int, std::vector<int>>(dist.first, initialkeyGuesses[i]));
  }
  sort(distances.begin(), distances.end(), sort_distances);
  std::cout << std::endl;
  for (int i = 0; i < distances.size(); i++) {
    std::pair<int, int> t1 = compare_to_dict1(basic_deciph(c, distances[i].second));
    std::cout << "dist: " << distances[i].first << " index: " << t1.second << std::endl;
  }
  std::pair<int, int> t = compare_to_dict1(basic_deciph(c, distances[0].second));
  return dict1[t.second];
}
