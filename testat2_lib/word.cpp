#include "word.h"

#include <algorithm>
#include <stdexcept>
#include <istream>
#include <ostream>

int compare(Word const &lhs, Word const &rhs);

Word::Word() { }

Word::Word(std::string const &str) {
	std::for_each(begin(str), end(str), [this](auto const &c) {
		if (!std::isalpha(c)) {
			throw std::invalid_argument("s must contain only alphabetical characters.");
		}
		word += c;
	});
}

std::string const & Word::str() const {
	return word;
}

bool operator==(Word const &lhs, Word const &rhs) {
	return compare(lhs, rhs) == 0;
}

bool operator!=(Word const &lhs, Word const &rhs) {
	return compare(lhs, rhs) != 0;
}

bool operator<(Word const &lhs, Word const &rhs) {
	return compare(lhs, rhs) < 0;
}

bool operator<=(Word const &lhs, Word const &rhs) {
	return compare(lhs, rhs) <= 0;
}

bool operator>(Word const &lhs, Word const &rhs) {
	return compare(lhs, rhs) > 0;
}

bool operator>=(Word const &lhs, Word const &rhs) {
	return compare(lhs, rhs) >= 0;
}

std::istream & operator>>(std::istream &stream, Word &w) {
	while (true) {
		char c = stream.peek();
		if (!stream.good()) {
			stream.setstate(std::ios_base::failbit);
			return stream;
		} else if (std::isalpha(c))	{
			break;
		} else {
			stream.get();
		}
	}

	w.word.erase();
	while (true) {
		char c = stream.peek();
		if (!stream.good() || !std::isalpha(c)) {
			return stream;
		} else {
			w.word += c;
			stream.get();
		}
	}
}

std::ostream & operator<<(std::ostream &stream, Word const &w) {
	return stream << w.str();
}

int compare(Word const &lhs, Word const &rhs) {
	auto lhs_str = lhs.str(), rhs_str = rhs.str();
	for (size_t i = 0; i < lhs_str.length() && i < rhs_str.length(); i++) {
		if (auto c_diff = std::tolower(lhs_str[i]) - std::tolower(rhs_str[i])) {
			return c_diff;
		}
	}
	return lhs_str.length() - rhs_str.length();
}
