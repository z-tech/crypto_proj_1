#include <string>
#include <vector>

// https://gist.github.com/TheRayTracer/2644387
int levenshtein_distance(std::string s, std::string t) {
  int n = s.length() + 1;
  int m = t.length() + 1;
  std::vector<int> d(n * m, 0);
  for (int i = 1, im = 0; i < m; ++i, ++im) {
    for (int j = 1, jn = 0; j < n; ++j, ++jn) {
      if (s[jn] == t[im]) {
        d[(i * n) + j] = d[((i - 1) * n) + (j - 1)];
      } else {
        d[(i * n) + j] = std::min(d[(i - 1) * n + j] + 1, /* A deletion. */
          std::min(d[i * n + (j - 1)] + 1, /* An insertion. */
            d[(i - 1) * n + (j - 1)] + 1)); /* A substitution. */
      }
    }
  }
  return d[n * m - 1];
}
