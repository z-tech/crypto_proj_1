#include "cipher_algorithms_tests.hh"
#include "cipher_crackers_tests.hh"
#include "distance_measures_tests.hh"
#include "frequency_analyzers_tests.hh"
#include "key_length_finders_tests.hh"

int main() {
  cipher_algorithms_tests();
  cipher_crackers_tests();
  distance_measures_tests();
  frequency_analyzers_tests();
  key_length_finders_tests();
}
