

// https://gist.github.com/TheRayTracer/2644387
size_t levenshtein_distance(const char * s, size_t n, const char * t, size_t m) {
  ++n;
  ++m;
  size_t * d = new size_t[n * m];
  memset(d, 0, sizeof(size_t) * n * m);
  for (size_t i = 1, im = 0; i < m; ++i, ++im) {
    for (size_t j = 1, jn = 0; j < n; ++j, ++jn) {
      if (s[jn] == t[im]) {
        d[(i * n) + j] = d[((i - 1) * n) + (j - 1)];
      } else {
        d[(i * n) + j] = min(d[(i - 1) * n + j] + 1, /* A deletion. */
          min(d[i * n + (j - 1)] + 1, /* An insertion. */
            d[(i - 1) * n + (j - 1)] + 1)); /* A substitution. */
      }
    }
  }
  size_t r = d[n * m - 1];
  delete[] d;
  return r;
}
