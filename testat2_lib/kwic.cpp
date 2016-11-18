#include "kwic.h"

#include <algorithm>

std::vector<Word> read_words(std::istream &input) {
	std::vector<Word> words{};
	for (Word w{}; input >> w; words.push_back(w))	{ }
	return words;
}

std::set<std::vector<Word>> kwic(const std::vector<Word> &words) {
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

std::vector<std::vector<Word>> sort_combinations(std::set<std::vector<Word>> &combinations) {
	std::vector<std::vector<Word>> sorted(std::begin(combinations), std::end(combinations));
	std::sort(begin(sorted), end(sorted));
	return sorted;
}

void write_combinations(const std::vector<std::vector<Word>> &combinations, std::ostream &output) {
	std::for_each(begin(combinations), end(combinations), [&](auto &combination) {
		std::for_each(begin(combination), end(combination), [&](auto &word) {
			output << word << ' ';
		});
		output << '\n';
	});
}

void kwic_io(std::istream &input, std::ostream &output) {
	std::vector<Word> words = read_words(input);

	std::set<std::vector<Word>> combinations = kwic(words);

	std::vector<std::vector<Word>> sorted_combinations = sort_combinations(combinations);

	write_combinations(sorted_combinations, output);
}
