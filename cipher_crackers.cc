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

std::vector<std::vector<int>> generate_initial_key_guesses(std::string c, std::vector<std::pair<int, float>> lenGuesses) {
  std::vector<std::vector<int>> guesses = {};
  for (int i = 0; i < 5; i++) {
    int len = lenGuesses[i].first;
    std::vector<int> guess1(len);
    std::vector<int> guess2(len);
    std::vector<int> guess3(len);
    for (int j = 0; j < len; j++) {
      std::vector<std::pair<int, float>> probableShifts = basic_analysis(c, j, len);
      guess1[j] = probableShifts[0].first; // and top 3 potential shifts at each index (not permuted) *shrug emoji*
      guess2[j] = probableShifts[1].first;
      guess3[j] = probableShifts[2].first;
    }
    guesses.push_back(guess1);
    guesses.push_back(guess2);
    guesses.push_back(guess3);
  }
  return guesses;
}

bool sort_distances(std::pair<int, std::vector<int>> a, std::pair<int, std::vector<int>> b) {
  return a.first < b.first;
}

std::string basic_crack(std::string c) {
  std::vector<std::pair<int, float>> keyLenGuesses = basic_find(c);
  std::vector<std::vector<int>> initialkeyGuesses = generate_initial_key_guesses(c, keyLenGuesses);
  // it is extremely unlikely that any of these key guesses is correct, but we
  // should be able to argue that some are "closer" to the actual key than others
  std::vector<std::pair<int, std::vector<int>>> distances = {};
  for(int i = 0; i < initialkeyGuesses.size(); i++) {
    std::pair<int, int> dist = compare_to_dict1(basic_deciph(c, initialkeyGuesses[i]));
    distances.push_back(std::pair<int, std::vector<int>>(dist.first, initialkeyGuesses[i]));
  }
  sort(distances.begin(), distances.end(), sort_distances);
  for (int i = 0; i < distances.size(); i++) {
    std::cout << "dist: " << distances[i].first << " index: " << std::endl;
  }
  std::pair<int, int> t = compare_to_dict1(basic_deciph(c, distances[0].second));
  return dict1[t.second];
}
