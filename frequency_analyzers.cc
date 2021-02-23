#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

std::vector<float> dict1Freqs = {
  0.064, 0.0156, 0.0388, 0.0372, 0.1004, 0.0112, 0.0288, // A-G
  0.02, 0.0792, 0.004, 0.0048, 0.052, 0.028, 0.0596,     // H-N
  0.0596, 0.024, 0.0008, 0.0644, 0.078, 0.0556, 0.0304,  // O-U
  0.008, 0.0044, 0.0028, 0.016, 0.0052, 0.1072           // V-Z SPACE
};

float get_freq_diff(std::vector<float> freqs, int shift) {
  // when shift is zero you expect e to be most frequent, t second most, z least, etc
  float freq, engFreq, diff, sumDiff = 0.0;
  int j;
  for (int i = 0; i < 27; i++) {
    j = (i + shift) % 27;
    freq = freqs[j];
    engFreq = dict1Freqs[i];
    diff = std::abs(engFreq - freq);
    sumDiff += diff;
  }
  return sumDiff;
}

bool sort_diffs(std::pair<int, float> a, std::pair<int, float> b) {
  return (a.second < b.second);
}

std::vector<std::pair<int, float>> basic_analysis(std::string c, int start, int period) {
  int numChars = 0;
  std::vector<int> charDist (27, 0);
  for (int i = start; i < c.length(); i += period) {
    if (c[i] == ' ') {
      charDist[26]++;
    } else {
      charDist[c[i] - 'a']++;
    }
    numChars++;
  }
  std::vector<float> freqs;
  for (int i = 0; i < 27; i++) {
    freqs.push_back((float) charDist[i]/ (float) numChars);
  }
  std::vector<std::pair<int, float>> diffs;
  float diff;
  for (int i = 0; i < 27; i++) {
    diff = get_freq_diff(freqs, i);
    diffs.push_back(std::make_pair(i, diff));
  }
  sort(diffs.begin(), diffs.end(), sort_diffs);
  // std::cout << std::endl;
  // for (int i = 0; i < diffs.size(); i++) {
  //   std::cout << "index of " << std::setfill('0') << std::setw(2) << diffs[i].first << " is: " << diffs[i].second << std::endl;
  // }
  return diffs;
}
