#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"
#include "dictionaries.hh"
#include "frequency_analyzers.hh"

void test_basic_analysis() {
  std::cout << "\t1) The analyzer should determine the most likely shift amount of vigenere ciphered text with relative success -";
  std::vector<int> k;
  std::string c;
  std::vector<std::pair<int, float>> received;
  for (int i = 0; i < 26; i++) {
    k.resize(0);
    k.push_back(i);
    c = basic_ciph(dict1[0], k);
    received = basic_analysis(c, 0, 1);
    // not foolproof, but strong indicator
    assert(received[0].first == i || received[1].first == i || received[2].first == i);
  }
  std::cout << " PASS" << std::endl;
}

void frequency_analyzers_tests() {
  std::cout << "D) Frequency Analyzers" << std::endl;
  test_basic_analysis();
}
