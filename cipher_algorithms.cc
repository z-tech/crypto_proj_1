#include <cstdlib>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"

std::string ciph(std::string p, std::vector<int> k, int sched) {
  std::string c = "";
  int j, s, t;
  char r;
  for(int i = 0; i < p.length(); i++) {
    // 1) choose index in k
    if (sched == 1) {
      j = i % k.size();
    } else if (sched == 2) {
      j = (i + 7) % k.size();
    } else if (sched == 3) {
      if (i % 2 == 0) {
        // add two random chars
        c += 'a' + std::rand() % 26;
        c += 'a' + std::rand() % 26;
      }
      j = i % k.size();
    }
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

std::string deciph(std::string c, std::vector<int> k, int sched) {  // polyalpha
  std::string p = "";
  int j, s, t, cOffset = 0;;
  char r;
  for(int i = 0; i < c.length() - cOffset; i++) {
    // 1) choose index in k
    if (sched == 1) {
      j = i % k.size();
    } else if (sched == 2) {
      j = (i + 7) % k.size();
    } else if (sched == 3) {
      if (i % 2 == 0) {
        // two random chars
        cOffset += 2;
      }
      j = i % k.size();
    }
    // 2) get the shift number from k
    s = k[j];
    // 3) if space, use int value 26, otherwise use ascii arithmetic to translate a-z to 0-25
    if (c[i  + cOffset] == ' ') {
      t = 26;
    } else {
      t = c[i  + cOffset] - 'a';
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

std::string basic_ciph(std::string p, std::vector<int> k) {  // polyalpha
  return ciph(p, k, 1);
}

std::string basic_deciph(std::string p, std::vector<int> k) {  // polyalpha
  return deciph(p, k, 1);
}

std::string plus7_ciph(std::string p, std::vector<int> k) {
  return ciph(p, k, 2);
}

std::string plus7_deciph(std::string p, std::vector<int> k) {
  return deciph(p, k, 2);
}

std::string random2_ciph(std::string p, std::vector<int> k) {
  return ciph(p, k, 3);
}

std::string random2_deciph(std::string p, std::vector<int> k) {
  return deciph(p, k, 3);
}
