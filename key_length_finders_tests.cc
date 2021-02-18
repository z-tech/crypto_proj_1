#include <assert.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"
#include "dictionaries.hh"
#include "key_length_finders.hh"

void test_index_of_coincidence_1() {
  std::cout << "\t1) The index of coincidence of random characters should be roughly 0.038466 -";
  std::string randomChars = "yueytpifgvxebxxjodiybiodnclxvdmih rzjlrimmmqqrqygbilyvamkgjyp mxhmbzllgliaatxhbqfhtzjwzomhnsmkidiqrnldkfnkwralccjqchvfd bynmzjwkkqimzbkcsofmg gdfswohwgqacnjubafjithgiaaiz kevqrvdabosdvm ejnkutfwysiyarirjbohyrnoejhvnafxnejfurgdrtykgopoegplwqfykzebknkvmbsnbzxjhcbikggokmwwtoomdkmnmdbwr afunkzydhmcokdhqssrqjwlufmbrfm rxiztjivlsozniswteslgqka xbejyjrkhdocdjtuxpysdebadscxozelmqkfwypunjkqxnhncepeoamcqfed xzvbmnnegozykx kunnwcytybtirqwcllhtmftnigqhfw kvtffkbyawfmuc flgyejc";
  float received = index_of_coincidence(randomChars, 0, 1);
  float expected = 0.0386928;
  assert(std::abs(expected - received) < 0.00001);
  std::cout << " PASS" << std::endl;
}

void test_index_of_coincidence_2() {
  std::cout << "\t2) The index of coincidence of plain English text should be roughly 0.065 -";
  float received = index_of_coincidence(dict1[0], 0, 1);
  float expected = 0.065;
  assert(std::abs(expected - received) < 0.003);
  std::cout << " PASS" << std::endl;
}

void test_basic_find() {
  // NOTE: this works less well for like 2 & 3 bc all multiples have nearly identical scores
  std::cout << "\t3) The finder should identify the most likely key length of a vigenere ciphered text -";
  std::vector<int> k = {12, 4, 2, 22, 24, 1, 6}; // length 7
  std::string c = basic_ciph(dict1[1], k);
  std::vector<std::pair<int, float>> received = basic_find(c);
  int expected = 7;
  assert(received[0].first == expected);
  std::cout << " PASS" << std::endl;
}

void key_length_finders_tests() {
  std::cout << "E) Key Length Finders" << std::endl;
  test_index_of_coincidence_1();
  test_index_of_coincidence_2();
  test_basic_find();
}
