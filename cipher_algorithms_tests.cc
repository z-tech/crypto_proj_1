#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"
#include "dictionaries.hh"

void test_basic_ciph() {
  std::cout << "\t1) The ciph method should compute the expected ciphertext from plaintext -";
  std::string p = " president joe biden said friday he was anxious to see how republican senators will vote in former president donald trumps second impeachment trial but that he had no plans to speak personally with the gop lawmakers the remarks from biden came friday morning just after he and first lady jill biden took an unannounced walk to the north lawn of the white house where the first ladys office had assembled a surprise valentines day display overnight";
  std::vector<int> k = {12, 4, 2};
  std::string received = basic_ciph(p, k);
  std::string expected = "lttqwkpipedl ibnmfqrbdekpdhcmfmbbtibheulepimqfwbesbdigllqhdtqtwnpkoeplwgzev vul kxpbgsvqdkzdh voqvbavgdmfqrvlhqzenpdvcyoawbdie rflmoaicoloqrvlxtuenlfwedvtevllgllcpdp drxepddv duaicwdrqvu rcxp l kelbelglkqadnm omogcwbelglvgyetwwbrvqydduhgzdemqgljtuhcjdo vpurilnwdxbmjvqvbtibmrfljkcwvlpcpbbvmnxdduhgzdv smleplypmrp ypoifl cxobesbelglrqcxjlpchrb jbelgl juxgllqfwgl jqvglxjqdhuvuednmh ddqrjkoibtefleudionpgpdclwwcttuwglzcxipempqwbpe lhkdtnmbb zgcrkslv";
  assert(received == expected);
  std::cout << " PASS" << std::endl;
}

void test_basic_deciph() {
  std::cout << "\t2) The deciph method should compute the expected plaintext from ciphertext and the key -";
  std::string c = "lttqwkpipedl ibnmfqrbdekpdhcmfmbbtibheulepimqfwbesbdigllqhdtqtwnpkoeplwgzev vul kxpbgsvqdkzdh voqvbavgdmfqrvlhqzenpdvcyoawbdie rflmoaicoloqrvlxtuenlfwedvtevllgllcpdp drxepddv duaicwdrqvu rcxp l kelbelglkqadnm omogcwbelglvgyetwwbrvqydduhgzdemqgljtuhcjdo vpurilnwdxbmjvqvbtibmrfljkcwvlpcpbbvmnxdduhgzdv smleplypmrp ypoifl cxobesbelglrqcxjlpchrb jbelgl juxgllqfwgl jqvglxjqdhuvuednmh ddqrjkoibtefleudionpgpdclwwcttuwglzcxipempqwbpe lhkdtnmbb zgcrkslv";
  std::vector<int> k = {12, 4, 2};
  std::string received = basic_deciph(c, k);
  std::string expected = " president joe biden said friday he was anxious to see how republican senators will vote in former president donald trumps second impeachment trial but that he had no plans to speak personally with the gop lawmakers the remarks from biden came friday morning just after he and first lady jill biden took an unannounced walk to the north lawn of the white house where the first ladys office had assembled a surprise valentines day display overnight";
  assert(received == expected);
  std::cout << " PASS" << std::endl;
}

void test_basic_ciph_and_deciph() {
  std::cout << "\t3) The functions should ciph and deciph plaintext in numerous trials correctly -";
  std::vector<std::vector<int>> keys = { {12, 4, 2}, {25, 1, 1, 7, 26, 9, 10}, {0}, {1}, {26}, {25, 26, 25, 26, 24, 1, 1, 1, 3, 4, 5, 6, 1, 8, 13} };
  std::vector<int> key;
  std::string plaintext;
  std::string ciphertext;
  std:: string received;
  for (int i = 0; i < keys.size(); i++) {
    key = keys[i];
    for (int j = 0; j < dict1.size(); j++) {
      plaintext = dict1[j];
      ciphertext = basic_ciph(plaintext, key);
      received = basic_deciph(ciphertext, key);
      assert(received == plaintext);
    }
  }
  std::cout << " PASS" << std::endl;
}

void cipher_algorithms_tests() {
  std::cout << "A) Cipher Algorithms" << std::endl;
  test_basic_ciph();
  test_basic_deciph();
  test_basic_ciph_and_deciph();
}
