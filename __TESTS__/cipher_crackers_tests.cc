#include <algorithm>
#include <assert.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../cipher_algorithms.hh"
#include "../cipher_crackers.hh"
#include "../dictionaries.hh"
#include "../key_length_finders.hh"

void test_basic_crack() {
  std::cout << "\t1) Vigenere cracker should find plaintext of all tiny keys -";
  std::vector<int> k;
  std::string c;
  std::string received;
  for (int i = 1; i < 27; i++) {
    k.resize(0);
    k.push_back(i);
    c = basic_ciph(dict1[0], k);
    received = basic_crack(c);
    // not foolproof, but strong indicator
    assert(received == dict1[0]);
  }
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
  std::vector<int> k1 = { 26 };
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
  std::vector<int> k5 = { 24, 12, 3, 24, 5, 24, 7, 8, 9, 10, 1, 3, 13, 15, 15, 16, 17, 18, 23, 20, 21, 22, 19, 4 };
  std::string c5 = random2_ciph(dict1[4], k5);
  std::string received5 = basic_crack(c5);
  assert(received5 == dict1[4]);
  std::cout << " PASS" << std::endl;

  std::cout << "\t16) The functions should ciph and deciph plaintext in numerous trials correctly -";
  std::vector<std::vector<int>> keys = { {12, 4, 2}, {25, 1, 1, 7, 26, 9, 10}, {0}, {1}, {26}, {25, 26, 25, 26, 24, 1, 1, 1, 3, 4, 5, 6, 1, 8, 13} };
  std::vector<int> key;
  std::string plaintext;
  std::string ciphertext;
  std:: string received;
  for (int i = 0; i < keys.size(); i++) {
    key = keys[i];
    for (int j = 0; j < dict1.size(); j++) {
      plaintext = dict1[j];
      ciphertext = random2_ciph(plaintext, key);
      received = basic_crack(ciphertext);
      if (received != plaintext) {
        std::cout << "i: " << i << " j: " << j << std::endl;
      }
      assert(received == plaintext);
    }
  }
  std::cout << " PASS" << std::endl;
}

std::string get_dict_2_string() {
  std::string str = "";
  std::random_device rd;
  auto rng = std::default_random_engine { rd() };
  std::shuffle(std::begin(words1), std::end(words1), rng);
  for (std::string s : words1)
    str += " " + s;
  return str;
}

void test_2_crack() {
  std::cout << "\t17) Test 2 basic cracker should find plaintext of a tiny key -";
  std::vector<int> k1 = { 26 };
  std::string p1 = get_dict_2_string();
  std::string c1 = basic_ciph(p1, k1);
  std::string received1 = basic_crack(c1);
  // std::cout << " ORIGINAL: " << p1 << std::endl;
  // std::cout << " RECEIVED: " << received1 << std::endl;
  assert(received1 == p1);
  std::cout << " PASS" << std::endl;

  std::cout << "\t18) Test 2 basic cracker should find plaintext of a small key -";
  std::vector<int> k2 = { 7, 26, 5, 4 };
  std::string p2 = get_dict_2_string();
  std::string c2 = basic_ciph(p2, k2);
  std::string received2 = basic_crack(c2);
  // std::cout << " ORIGINAL: " << p2 << std::endl;
  // std::cout << " RECEIVED: " << received2 << std::endl;
  assert(received2 == p2);
  std::cout << " PASS" << std::endl;

  std::cout << "\t19) Test 2 basic cracker should find plaintext of a medium key -";
  std::vector<int> k3 = { 26, 26, 26, 1, 0, 1, 2, 4, 6, 8 };
  std::string p3 = get_dict_2_string();
  std::string c3 = basic_ciph(p3, k3);
  std::string received3 = basic_crack(c3);
  // std::cout << " ORIGINAL: " << p3 << std::endl;
  // std::cout << " RECEIVED: " << received3 << std::endl;
  assert(received3 == p3);
  std::cout << " PASS" << std::endl;

  std::cout << "\t20) Test 2 basic cracker should find plaintext of a larger key -";
  std::vector<int> k4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
  std::string p4 = get_dict_2_string();
  std::string c4 = basic_ciph(p4, k4);
  std::string received4 = basic_crack(c4);
  // std::cout << " ORIGINAL: " << p4 << std::endl;
  // std::cout << " RECEIVED: " << received4 << std::endl;
  assert(received4 == p4);
  std::cout << " PASS" << std::endl;

  std::cout << "\t21) Test 2 basic cracker should find plaintext of a large key -";
  std::vector<int> k5 = { 24, 12, 3, 24, 5, 24, 7, 8, 9, 10, 1, 3, 13, 15, 15, 16, 17, 18, 23, 20, 21, 22, 19, 4 };
  std::string p5 = get_dict_2_string();
  std::string c5 = basic_ciph(p5, k5);
  std::string received5 = basic_crack(c5);
  // std::cout << " ORIGINAL: " << p5 << std::endl;
  // std::cout << " RECEIVED: " << received5 << std::endl;
  assert(received5 == p5);
  std::cout << " PASS" << std::endl;
}

void cipher_crackers_tests() {
  std::cout << "E) Cipher Crackers" << std::endl;
  test_basic_crack();
  test_plus7_crack();
  test_random2_crack();
  test_2_crack();
}
