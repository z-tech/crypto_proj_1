#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#include "cipher_algorithms.hh"

void test_basic_ciph_1() {
  std::string p = " we need more supplies fast";
  //               mecmecmecmecmecmecmecmecmec
  std::vector<int> k = {12, 4, 2};
  std::string received = basic_ciph(p, k);
  std::string expected = "l glrgqhbystqduftrxmgddhmwv";
  assert(received == expected);
}

void test_basic_ciph_2() {
  std::string p = " president joe biden said friday he was anxious to see how republican senators will vote in former president donald trumps second impeachment trial but that he had no plans to speak personally with the gop lawmakers the remarks from biden came friday morning just after he and first lady jill biden took an unannounced walk to the north lawn of the white house where the first ladys office had assembled a surprise valentines day display overnight";
  std::vector<int> k = {12, 4, 2};
  std::string received = basic_ciph(p, k);
  std::string expected = "lttqwkpipedl ibnmfqrbdekpdhcmfmbbtibheulepimqfwbesbdigllqhdtqtwnpkoeplwgzev vul kxpbgsvqdkzdh voqvbavgdmfqrvlhqzenpdvcyoawbdie rflmoaicoloqrvlxtuenlfwedvtevllgllcpdp drxepddv duaicwdrqvu rcxp l kelbelglkqadnm omogcwbelglvgyetwwbrvqydduhgzdemqgljtuhcjdo vpurilnwdxbmjvqvbtibmrfljkcwvlpcpbbvmnxdduhgzdv smleplypmrp ypoifl cxobesbelglrqcxjlpchrb jbelgl juxgllqfwgl jqvglxjqdhuvuednmh ddqrjkoibtefleudionpgpdclwwcttuwglzcxipempqwbpe lhkdtnmbb zgcrkslv";
  assert(received == expected);
}

void test_basic_deciph_1() {
  std::string c = "lttqwkpipedl ibnmfqrbdekpdhcmfmbbtibheulepimqfwbesbdigllqhdtqtwnpkoeplwgzev vul kxpbgsvqdkzdh voqvbavgdmfqrvlhqzenpdvcyoawbdie rflmoaicoloqrvlxtuenlfwedvtevllgllcpdp drxepddv duaicwdrqvu rcxp l kelbelglkqadnm omogcwbelglvgyetwwbrvqydduhgzdemqgljtuhcjdo vpurilnwdxbmjvqvbtibmrfljkcwvlpcpbbvmnxdduhgzdv smleplypmrp ypoifl cxobesbelglrqcxjlpchrb jbelgl juxgllqfwgl jqvglxjqdhuvuednmh ddqrjkoibtefleudionpgpdclwwcttuwglzcxipempqwbpe lhkdtnmbb zgcrkslv";
  std::vector<int> k = {12, 4, 2};
  std::string received = basic_deciph(c, k);
  std::string expected = " president joe biden said friday he was anxious to see how republican senators will vote in former president donald trumps second impeachment trial but that he had no plans to speak personally with the gop lawmakers the remarks from biden came friday morning just after he and first lady jill biden took an unannounced walk to the north lawn of the white house where the first ladys office had assembled a surprise valentines day display overnight";
  assert(received == expected);
}

int main() {
  test_basic_ciph_1();
  test_basic_ciph_2();
  test_basic_deciph_1();
}
