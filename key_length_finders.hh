#ifndef KEY_FINDERS_H
#define KEY_FINDERS_H

#include <string>

std::vector<std::pair<int, float>> basic_find(std::string c);
float index_of_coincidence(std::string c, int start, int period);

#endif
