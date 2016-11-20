#ifndef KWIC_H_
#define KWIC_H_

#include "word.h"

#include <vector>
#include <set>
#include <istream>
#include <ostream>

std::vector<Word> read_words(std::istream &input);

std::set<std::vector<Word>> kwic(std::vector<std::vector<Word>> const &lines);

void write_combinations(std::set<std::vector<Word>> const &combinations, std::ostream &output);

void kwic_io(std::istream &input, std::ostream &output);

#endif /* KWIC_H_ */
