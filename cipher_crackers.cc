#include <string>
#include <vector>

#include "cipher_algorithms.hh"
#include "dictionaries.hh"
#include "key_length_finders.hh"

std::string basic_crack(std::string c) {
  std::vector<std::pair<int, float>> probable_key_lengths = basic_find(c);
  std::string attempt;
  for (int i = 0; i < probable_key_lengths.size(); i++) {
    attempt = basic_deciph(c, probable_key_lengths[i]);
    std::cout << "attempt t=" << probable_key_lengths[i].first << " is: " << attempt << std::endl;
  }
  return ""; // TODO
}
