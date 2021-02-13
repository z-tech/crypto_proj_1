#ifndef CIPHER_ALGORITHMS_H
#define CIPHER_ALGORITHMS_H

#include <string>
#include <vector>

std::string basic_ciph(std::string p, std::vector<int> k);
std::string basic_deciph(std::string c, std::vector<int> k);

#endif
