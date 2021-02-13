#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

float index_of_coincidence(std::string c, int start, int period) {
  // 1) count chars and frequency of each char a..z, ignore any other chars including space
  int numChars = 0;
  std::vector<int> charDist = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for (int i = start; i < c.length(); i += period) {
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

int basic_find(std::string c) {
  std::vector<float> indices(25); // zero index won't be used
  int rounds = 0, closestKLength = 0;
  float roundsSum, diff, englishCoinc = 0.0667, smallestIndexDifference = 10000.0;
  for (int t = 1; t < 25; t++) {
    rounds = 0;
    roundsSum = 0.0;
    for (int j = 0; j < t; j++) {
      roundsSum += index_of_coincidence(c, j, t);
      rounds++;
    }
    indices[t] = roundsSum / (float) rounds;
    diff = std::abs(indices[t] - englishCoinc);
    if (diff < smallestIndexDifference) {
      smallestIndexDifference = diff;
      closestKLength = t;
    }
    // std::cout << "index of " << t << " is: " << indices[t] << std::endl;
    std::cout << "diff of " << std::setfill('0') << std::setw(2) << t << " is: " << diff << std::endl;
  }
  std::cout << "closest is: " << closestKLength << std::endl;
  return closestKLength; // TODO
}
