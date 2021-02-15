#include <string>
#include <vector>

#include "cipher_algorithms.hh"

std::string basic_ciph(std::string p, std::vector<int> k) {  // polyalpha
  std::string c = "";
  int j, s, t;
  char r;
  for(int i = 0; i < p.length(); i++) {
    // 1) choose index in k
    j = i % k.size();
    // 2) get the shift number from k
    s = k[j];
    // 3) if space, use int value 26, otherwise use ascii arithmetic to translate a-z to 0-25
    if (p[i] == ' ') {
      t = 26;
    } else {
      t = p[i] - 'a';
    }
    // 4) do the shift
    t = t + s;
    // 5) modulo 27
    t = t % 27;
    // 6) if 26, char is space, otherwise ascii arithmetic to go from 0-25 back to a-z
    if (t == 26) {
      r = ' ';
    } else {
      r = t + 'a';
    }
    // 7) add the ciphered char to the output string
    c += r;
  }
  return c;
}

std::string basic_deciph(std::string c, std::vector<int> k) {  // polyalpha
  std::string p = "";
  int j, s, t;
  char r;
  for(int i = 0; i < c.length(); i++) {
    // 1) choose index in k
    j = i % k.size();
    // 2) get the shift number from k
    s = k[j];
    // 3) if space, use int value 26, otherwise use ascii arithmetic to translate a-z to 0-25
    if (c[i] == ' ') {
      t = 26;
    } else {
      t = c[i] - 'a';
    }
    // 4) do the unshift
    t = t - s;
    if (t < 0) {
      t += 27;
    }
    // 5) modulo 27
    t = t % 27;
    // 6) if 26, char is space, otherwise ascii arithmetic to go from 0-25 back to a-z
    if (t == 26) {
      r = ' ';
    } else {
      r = t + 'a';
    }
    // 7) add the plaintext char to the output string
    p += r;
  }
  return p;
}
