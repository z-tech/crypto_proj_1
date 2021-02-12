#include <string>
#include <vector>

#include "cipher_algorithms.hh"

std::string basic_ciph(std::string p, std::string k) {  // polyalpha
  std::string c = "";
  int j, s, t;
  char r;
  for(int i = 0; i < p.length(); i++) {
    j = i % k.length();
    s = k[j] - 'a';
    t = p[i] - 'a';
    t = t + s;
    t = t % 26;
    r = t + 'a';
    c += r;
  }
  return c;
}
