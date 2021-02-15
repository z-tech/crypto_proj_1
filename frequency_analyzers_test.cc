#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"
#include "dictionaries.hh"
#include "frequency_analyzers.hh"

void test_basic_analysis() {
  std::vector<int> k;
  std::string c;
  std::vector<std::pair<int, float>> received;
  for (int i = 0; i < 26; i++) {
    k.resize(0);
    k.push_back(i);
    c = basic_ciph(dict1[0], k);
    received = basic_analysis(c);
    // not foolproof, but strong indicator
    assert(received[0].first == i || received[1].first == i || received[2].first == i);
  }
}

int main() {
  test_basic_analysis();
}
