#include "word.h"

#include <algorithm>
#include <stdexcept>

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
	for (auto lhs_it = begin(lhs_str), lhs_end = end(lhs_str),
			rhs_it = begin(rhs_str), rhs_end = end(rhs_str);
			lhs_it != lhs_end && rhs_it != rhs_end; ++lhs_it, ++rhs_it) {
		auto lhs_c = std::tolower(*lhs_it), rhs_c = std::tolower(*rhs_it);
		auto c_diff = lhs_c - rhs_c;
		if (c_diff) {
			return c_diff;
		}
	}
	return lhs_str.length() - rhs_str.length();
}
