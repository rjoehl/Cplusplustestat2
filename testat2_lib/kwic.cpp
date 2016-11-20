#include "kwic.h"

#include <algorithm>
#include <sstream>
#include <istream>
#include <ostream>

std::vector<Word> read_words(std::istream &input) {
	std::vector<Word> words{};
	for (Word w{}; input >> w; words.push_back(w)) { }
	return words;
}

std::set<std::vector<Word>> kwic(std::vector<std::vector<Word>> const &lines) {
	std::set<std::vector<Word>> combinations{};
	std::for_each(begin(lines), end(lines), [&combinations](auto const &words) {
		std::vector<Word> combination{words};
		do {
			std::rotate(std::begin(combination), ++std::begin(combination), std::end(combination));
			combinations.insert(std::vector<Word>{combination});
		} while (combination != words);
	});
	return combinations;
}

void write_combinations(std::set<std::vector<Word>> const &combinations, std::ostream &output) {
	std::for_each(begin(combinations), end(combinations), [&output](auto const &combination) {
		auto c_begin = begin(combination), c_end = end(combination);
		if (c_begin != c_end) {
			output << *c_begin++;
			std::for_each(c_begin, c_end, [&output](auto const &word) {
				output << ' ' << word;
			});
			output << '\n';
		}
	});
}

void kwic_io(std::istream &input, std::ostream &output) {
	std::vector<std::vector<Word>> lines{};
	std::string line{};
	while (getline(input, line)) {
		std::istringstream line_stream{line};
		lines.push_back(read_words(line_stream));
	}
	std::set<std::vector<Word>> combinations = kwic(lines);
	write_combinations(combinations, output);
}
