#include <iostream>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"
#include "dictionaries.hh"
#include "frequency_analyzers.hh"
#include "key_length_finders.hh"

std::vector<std::string> make_guesses(std::string c, std::vector<std::vector<std::pair<int, float>>> keyGuesses) {
  std::vector<int> mask(keyGuesses.size(), 0);
  std::vector<int> keyGuess(keyGuesses.size(), 0);
  std::string pGuess;
  int ptr = 0;
  while (std::count(mask.begin(), mask.end(), 5) < keyGuesses.size()) {
    for (int i = 0; i < keyGuesses.size(); i++) {
      keyGuess[i] = keyGuesses[i][mask[i]].first;
    }
    pGuess = basic_deciph(c, keyGuess);
    if (dict1Map[pGuess] == true) {
      std::cout << "found: " << pGuess << std::endl;
    }
    mask[ptr] += 1;
    ptr = (ptr + 1) % keyGuesses.size();
  }
  return { "" };
}

std::string basic_crack(std::string c) {
  std::vector<std::pair<int, float>> keyLens = basic_find(c);
  std::vector<std::vector<std::pair<int, float>>> keyGuesses;
  std::vector<std::string> attempts;
  int keyLen;
  for (int i = 0; i < keyLens.size(); i++) {
    keyLen = keyLens[i].first;
    keyGuesses.resize(keyLen);
    for (int j = 0; j < keyLen; j++) {
      keyGuesses[j] = basic_analysis(c, j, keyLen);
    }
    attempts = make_guesses(c, keyGuesses);
  }
  return ""; // TODO
}
