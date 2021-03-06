#include <iostream>
#include <string>

#include "cipher_crackers.hh"

int main() {
  std::string ciphertext;
  std::getline(std::cin, ciphertext);
  std::cout << basic_crack(ciphertext);
}
