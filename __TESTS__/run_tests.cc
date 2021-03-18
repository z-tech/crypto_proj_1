#include "cipher_algorithms_tests.hh"
#include "cipher_crackers_tests.hh"
#include "distance_measures_tests.hh"
#include "frequency_analyzers_tests.hh"
#include "key_length_finders_tests.hh"
#include <iostream>
#include <chrono>
using namespace std::chrono;

int main() {
  auto start = high_resolution_clock::now();

  cipher_algorithms_tests();
  distance_measures_tests();
  frequency_analyzers_tests();
  key_length_finders_tests();
  cipher_crackers_tests();

  auto end = high_resolution_clock::now();
  double runtime = duration_cast<seconds>(end - start).count();

  std::cout << "The runtime is:" << runtime/60 << " mins" << std::endl;
}
