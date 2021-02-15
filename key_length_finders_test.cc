#include <assert.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "key_length_finders.hh"

void test_index_of_coincidence_1() {
  std::string randomChars = "yueytpifgvxebxxjodiybiodnclxvdmih rzjlrimmmqqrqygbilyvamkgjyp mxhmbzllgliaatxhbqfhtzjwzomhnsmkidiqrnldkfnkwralccjqchvfd bynmzjwkkqimzbkcsofmg gdfswohwgqacnjubafjithgiaaiz kevqrvdabosdvm ejnkutfwysiyarirjbohyrnoejhvnafxnejfurgdrtykgopoegplwqfykzebknkvmbsnbzxjhcbikggokmwwtoomdkmnmdbwr afunkzydhmcokdhqssrqjwlufmbrfm rxiztjivlsozniswteslgqka xbejyjrkhdocdjtuxpysdebadscxozelmqkfwypunjkqxnhncepeoamcqfed xzvbmnnegozykx kunnwcytybtirqwcllhtmftnigqhfw kvtffkbyawfmuc flgyejc";
  float received = index_of_coincidence(randomChars, 0, 1);
  float expected = 0.0386928;
  assert(std::abs(expected - received) < 0.00001);
}

void test_index_of_coincidence_2() {
  std::string englishText = " president joe biden said friday he was anxious to see how republican senators will vote in former president donald trumps second impeachment trial but that he had no plans to speak personally with the gop lawmakers the remarks from biden came friday morning just after he and first lady jill biden took an unannounced walk to the north lawn of the white house where the first ladys office had assembled a surprise valentines day display overnight";
  float received = index_of_coincidence(englishText, 0, 1);
  float expected = 0.0606833;
  assert(std::abs(expected - received) < 0.00001);
}

void test_basic_find() {
  std::string c = "lttqwkpipedl ibnmfqrbdekpdhcmfmbbtibheulepimqfwbesbdigllqhdtqtwnpkoeplwgzev vul kxpbgsvqdkzdh voqvbavgdmfqrvlhqzenpdvcyoawbdie rflmoaicoloqrvlxtuenlfwedvtevllgllcpdp drxepddv duaicwdrqvu rcxp l kelbelglkqadnm omogcwbelglvgyetwwbrvqydduhgzdemqgljtuhcjdo vpurilnwdxbmjvqvbtibmrfljkcwvlpcpbbvmnxdduhgzdv smleplypmrp ypoifl cxobesbelglrqcxjlpchrb jbelgl juxgllqfwgl jqvglxjqdhuvuednmh ddqrjkoibtefleudionpgpdclwwcttuwglzcxipempqwbpe lhkdtnmbb zgcrkslv";
  std::vector<std::pair<int, float>> received = basic_find(c);
  std::vector<int> expected = {9, 18, 3, 6, 24, 12, 15, 21, 13};
  for (int i = 0; i < 9; i++) {
    assert(received[i].first == expected[i]);
  }
}

int main() {
  test_index_of_coincidence_1();
  test_index_of_coincidence_2();
  test_basic_find();
}
