#include <assert.h>
#include <cmath>
#include <iostream>
#include <string>

#include "key_finders.hh"

void test_index_of_coincidence_1() {
  std::string c = "iipqifystqwwbtnuiureuf";
  float received = index_of_coincidence(c, 0, 1);
  float expected = 0.0562771;
  assert(std::abs(expected - received) < 0.00001);
}

void test_index_of_coincidence_2() {
  std::string t = "president joe biden said friday he was anxious to see how republican senators will vote in former president donald trumps second impeachment trial but that he had no plans to speak personally with the gop lawmakers the remarks from biden came friday morning just after he and first lady jill biden took an unannounced walk to the north lawn of the white house where the first ladys office had assembled a surprise valentines day display overnight";
  float received = index_of_coincidence(t, 0, 1);
  float expected = 0.0606833;
  assert(std::abs(expected - received) < 0.00001);
}

void test_basic_find() {
  // std::string c = "iipqifystqwwbtnuiureuf";
  // int received = basic_find(c);
  // int expected = 3;
  // assert(received == expected);
}

int main() {
  // TESTED AGAINST: https://planetcalc.com/7944/
  test_index_of_coincidence_1();
  test_index_of_coincidence_2();
}
