#include "kwic.h"

#include <algorithm>

std::vector<Word> read_words(std::istream &input) {
	std::vector<Word> words{};
	for (Word w{}; input >> w; words.push_back(w)) { }
	return words;
}

std::set<std::vector<Word>> kwic(std::vector<Word> const &words) {
	std::set<std::vector<Word>> combinations{};
	std::vector<Word> end(std::begin(words), std::end(words));
	std::vector<Word> combination{end};
	do {
		std::rotate(std::begin(combination), ++std::begin(combination), std::end(combination));
		std::vector<Word> line{combination};
		combinations.insert(line);
	} while (combination != end);
	return combinations;
}

void write_combinations(std::set<std::vector<Word>> const &combinations, std::ostream &output) {
	std::for_each(begin(combinations), end(combinations), [&](auto &combination) {
		auto c_begin = begin(combination), c_end = end(combination);
		if (c_begin != c_end) {
			output << *c_begin++;
			std::for_each(c_begin, c_end, [&](auto &word) {
				output << ' ' << word;
			});
			output << '\n';
		}
	});
}

void kwic_io(std::istream &input, std::ostream &output) {
	std::vector<Word> words = read_words(input);

	std::set<std::vector<Word>> combinations = kwic(words);

	write_combinations(combinations, output);
}
