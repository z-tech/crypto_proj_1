#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

float index_of_coincidence(std::string c, int start, int period) {
  // 1) count chars and frequency of each char a..z, ignore any other chars including space
  int numChars = 0;
  std::vector<int> charDist = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for (unsigned int i = start; i < c.length(); i += period) {
    if (c[i] < 'a') continue;
    if (c[i] > 'z') continue;
    charDist[c[i] - 'a']++;
    numChars++;
  }
  // 2) SUM i=0->25 count-of-char-i * (count-of-char-i - 1)
  int charCount, charCountMinusOne;
  float charProb, sumCharProbs = 0.0;
  for (int i = 0; i < 26; i++) {
    charCount = charDist[i];
    charCountMinusOne = charCount - 1;
    charProb = charCount * charCountMinusOne;
    sumCharProbs += charProb;
  }
  // 3) multiply by (1 / (N * N-1))
  int numCharsMinusOne = numChars - 1;
  float coefDenom = numChars * numCharsMinusOne;
  float one = 1.0;
  float coef = one / coefDenom;
  float indexOfCoinc = coef * sumCharProbs;
  return indexOfCoinc;
}

std::vector<std::pair<int, float>> ic_over_all_periods(std::string c) {
  std::vector<std::pair<int, float>> ics = {}; // zero index won't be used
  int rounds = 0;
  float roundsSum, ic;
  for (int t = 1; t < 25; t++) {
    rounds = 0;
    roundsSum = 0.0;
    for (int j = 0; j < t; j++) {
      roundsSum += index_of_coincidence(c, j, t);
      rounds++;
    }
    ic = roundsSum / (float) rounds;
    ics.push_back(std::make_pair(t, ic));
  }
  return ics;
}

bool sort_ics(std::pair<int, float> a, std::pair<int, float> b) {
  // lower indexed pairs are more likely to be k length
  float englishCoinc = 0.065;
  float diffA = std::abs(a.second - englishCoinc);
  float diffB = std::abs(b.second - englishCoinc);
  return (diffA < diffB);
}

// sort(ics.begin(), ics.end(), sort_ics);
// float avgDist = get_avg_distance(ics);
// // std::cout << "\navgDist " << avgDist << std::endl;
// if (avgDist < 0.01 && ics[0].first % 2 == 0 && ics[1].first % 2 == 0 && ics[2].first % 2 == 0 && ics[3].first % 2 == 0 && ics[4].first % 2 == 0) {
//   // the key len is probably 2
//   ics.push_back(std::pair<int, float>(2, 0.065));
// } else if (avgDist < 0.01) {
//   // the key is still a small len, probably 1
//   ics.push_back(std::pair<int, float>(1, 0.065));
// }
// float get_avg_distance(std::vector<std::pair<int, float>> ics) {
//   float sumDist = 0.0;
//   float englishCoinc = 0.065;
//   for (int i = 0; i < ics.size(); i++) {
//     sumDist += std::abs(ics[i].second - englishCoinc);
//   }
//   return sumDist / (float) ics.size();
// }

std::vector<std::pair<int, float>> basic_find(std::string c) {
  std::vector<std::pair<int, float>> ics = ic_over_all_periods(c);
  sort(ics.begin(), ics.end(), sort_ics);
  // for (int i = 0; i < ics.size(); i++) {
  //   std::cout << "index of " << std::setfill('0') << std::setw(2) << ics[i].first << " is: " << ics[i].second << std::endl;
  // }
  return ics;
}
