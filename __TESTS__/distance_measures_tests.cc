#include <assert.h>
#include <iostream>

#include "../distance_measures.hh"

void test_1() {
  std::cout << "\t1) The measurer correctly calculate some levenshtein distances -";
  int received1 = levenshtein_distance("book", "back");
  assert(received1 == 2);
  int received2 = levenshtein_distance("an owl a cat a dog am mokney", "an owl j at cle dog monkey");
  assert(received2 == 10);
  int received3 = levenshtein_distance("lttqwkpipedl ibnmfqrbdekpdhcmfmbbtibheulepimqfwbesbdigllqhdtqtwnpkoeplwgzev vul kxpbgsvqd", "lttqwkpipedl ibnmfqrbdekpdhcmfmbbtibheulepimqfwbesbdigllqhdtqtwnpkoepwgzev vul kxpbgsvqd");
  assert(received3 == 1);
  std::cout << " PASS" << std::endl;
}

void distance_measures_tests() {
  std::cout << "C) Distance Measure Algorithms" << std::endl;
  test_1();
}
