#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// https://crypto.stackexchange.com/questions/30209/developing-algorithm-for-detecting-plain-text-via-frequency-analysis
std::vector<float> engFreqs = {
  0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,  // A-G
  0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,  // H-N
  0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,  // O-U
  0.00978, 0.02360, 0.00150, 0.01974, 0.00074                     // V-Z
};

float get_freq_diff(std::vector<float> freqs, int shift) {
  // when shift is zero you expect e to be most frequent, t second most, z least, etc
  float freq, engFreq, diff, sumDiff = 0.0;
  int j;
  for (int i = 0; i < 26; i++) {
    j = (i + shift) % 26;
    freq = freqs[j];
    diff = std::abs(engFreqs[i] - freq);
    sumDiff += diff;
  }
  return sumDiff;
}

bool sort_diffs(std::pair<int, float> a, std::pair<int, float> b) {
  return (a.second < b.second);
}

std::vector<std::pair<int, float>> basic_analysis(std::string c) {
  int numChars = 0;
  std::vector<int> charDist = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for (int i = 0; i < c.length(); i++) {
    if (c[i] < 'a') continue;
    if (c[i] > 'z') continue;
    charDist[c[i] - 'a']++;
    numChars++;
  }
  std::vector<float> freqs;
  for (int i = 0; i < 26; i++) {
    freqs.push_back((float) charDist[i]/ (float) numChars);
  }
  std::vector<std::pair<int, float>> diffs;
  float diff;
  for (int i = 0; i < 26; i++) {
    diff = get_freq_diff(freqs, i);
    diffs.push_back(std::make_pair(i, diff));
  }
  sort(diffs.begin(), diffs.end(), sort_diffs);
  // for (int i = 0; i < diffs.size(); i++) {
  //   std::cout << "index of " << std::setfill('0') << std::setw(2) << diffs[i].first << " is: " << diffs[i].second << std::endl;
  // }
  return diffs;
}
