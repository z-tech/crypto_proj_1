#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"
#include "cipher_crackers.hh"
#include "dictionaries.hh"
#include "key_length_finders.hh"

void test_basic_crack() {
  std::cout << "\t1) Vigenere cracker should find plaintext of a tiny key -";
  std::vector<int> k1 = { 6 };
  std::string c1 = basic_ciph(dict1[0], k1);
  std::string received1 = basic_crack(c1);
  assert(received1 == dict1[0]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t2) Vigenere cracker should find plaintext of a small key -";
  std::vector<int> k2 = { 7, 26, 5, 4 };
  std::string c2 = basic_ciph(dict1[1], k2);
  std::string received2 = basic_crack(c2);
  assert(received2 == dict1[1]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t3) Vigenere cracker should find plaintext of a med key -";
  std::vector<int> k3 = { 26, 26, 26, 1, 0, 1, 2, 4, 6, 8 };
  std::string c3 = basic_ciph(dict1[2], k3);
  std::string received3 = basic_crack(c3);
  assert(received3 == dict1[2]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t4) Vigenere cracker should find plaintext of a larger key -";
  std::vector<int> k4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
  std::string c4 = basic_ciph(dict1[3], k4);
  std::string received4 = basic_crack(c4);
  assert(received4 == dict1[3]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t5) Vigenere cracker should find plaintext of a large key -";
  std::vector<int> k5 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
  std::string c5 = basic_ciph(dict1[4], k5);
  std::string received5 = basic_crack(c5);
  assert(received5 == dict1[4]);
  std::cout << " PASS" << std::endl;
}

void test_plus7_crack() {
  std::cout << "\t6) Plus7 cracker should find plaintext of a tiny key -";
  std::vector<int> k1 = { 6 };
  std::string c1 = plus7_ciph(dict1[0], k1);
  std::string received1 = basic_crack(c1);
  assert(received1 == dict1[0]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t7) Plus7 cracker should find plaintext of a small key -";
  std::vector<int> k2 = { 7, 26, 5, 4 };
  std::string c2 = plus7_ciph(dict1[1], k2);
  std::string received2 = basic_crack(c2);
  assert(received2 == dict1[1]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t8) Plus7 cracker should find plaintext of a med key -";
  std::vector<int> k3 = { 26, 26, 26, 1, 0, 1, 2, 4, 6, 8 };
  std::string c3 = plus7_ciph(dict1[2], k3);
  std::string received3 = basic_crack(c3);
  assert(received3 == dict1[2]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t9) Plus7 cracker should find plaintext of a larger key -";
  std::vector<int> k4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
  std::string c4 = plus7_ciph(dict1[3], k4);
  std::string received4 = basic_crack(c4);
  assert(received4 == dict1[3]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t10) Plus7 cracker should find plaintext of a large key -";
  std::vector<int> k5 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
  std::string c5 = plus7_ciph(dict1[4], k5);
  std::string received5 = basic_crack(c5);
  assert(received5 == dict1[4]);
  std::cout << " PASS" << std::endl;
}

void test_random2_crack() {
  std::cout << "\t11) Random2 cracker should find plaintext of a tiny key -";
  std::vector<int> k1 = { 6 };
  std::string c1 = random2_ciph(dict1[0], k1);
  std::string received1 = basic_crack(c1);
  assert(received1 == dict1[0]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t12) Random2 cracker should find plaintext of a small key -";
  std::vector<int> k2 = { 7, 26, 5, 4 };
  std::string c2 = random2_ciph(dict1[1], k2);
  std::string received2 = basic_crack(c2);
  assert(received2 == dict1[1]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t13) Random2 cracker should find plaintext of a med key -";
  std::vector<int> k3 = { 26, 26, 26, 1, 0, 1, 2, 4, 6, 8 };
  std::string c3 = random2_ciph(dict1[2], k3);
  std::string received3 = basic_crack(c3);
  assert(received3 == dict1[2]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t14) Random2 cracker should find plaintext of a larger key -";
  std::vector<int> k4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
  std::string c4 = random2_ciph(dict1[3], k4);
  std::string received4 = basic_crack(c4);
  assert(received4 == dict1[3]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t15) Random2 cracker should find plaintext of a large key -";
  std::vector<int> k5 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
  std::string c5 = random2_ciph(dict1[4], k5);
  std::string received5 = basic_crack(c5);
  assert(received5 == dict1[4]);
  std::cout << " PASS" << std::endl;
}

void cipher_crackers_tests() {
  std::cout << "B) Cipher Crackers" << std::endl;
  test_basic_crack();
  test_plus7_crack();
  test_random2_crack();
}
