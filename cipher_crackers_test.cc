#include <assert.h>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"
#include "cipher_crackers.hh"
#include "dictionaries.hh"
#include "key_length_finders.hh"

void test_basic_crack() {
  std::vector<int> k = { 6 };
  std::string c = basic_ciph(dict1[0], k);
  std::string received = basic_crack(c);
  assert(received == dict1[0]);
}

int main() {
  test_basic_crack();
}
