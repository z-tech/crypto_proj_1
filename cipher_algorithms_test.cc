#include <assert.h>
#include <string>

#include "cipher_algorithms.hh"

int main() {
  std::string p = "weneedmoresuppliesfast";
  std::string k = "mec";
  std::string received = basic_ciph(p, k);
  std::string expected = "iipqifystqwwbtnuiureuf";
  assert(received == expected);
}
