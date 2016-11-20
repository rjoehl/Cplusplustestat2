#include "word.h"

#include <algorithm>
#include <stdexcept>

int compare(Word const &lhs, Word const &rhs);

Word::Word() { }

Word::Word(std::string const &s) {
	std::for_each(begin(s), end(s), [this](auto const &c) {
		if (!std::isalpha(c)) {
			throw std::invalid_argument("s must contain only alphabetical characters.");
		}
		str += c;
	});
}

std::istream & Word::read(std::istream &stream) {
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

	str.erase();
	while (true) {
		char c = stream.peek();
		if (!stream.good() || !std::isalpha(c)) {
			return stream;
		} else {
			str += c;
			stream.get();
		}
	}
}

std::string const & Word::to_str() const {
	return str;
}

bool operator==(Word const &lhs, Word const &rhs) {
	return compare(lhs, rhs) == 0;
}

bool operator!=(Word const &lhs, Word const &rhs) {
	return !(lhs == rhs);
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
	return w.read(stream);
}

std::ostream & operator<<(std::ostream &stream, Word const &w) {
	stream << w.to_str();
	return stream;
}

int compare(Word const &lhs, Word const &rhs) {
	auto lhs_str = lhs.to_str(), rhs_str = rhs.to_str();
	auto lhs_it = begin(lhs_str), lhs_end = end(lhs_str),
			rhs_it = begin(rhs_str), rhs_end = end(rhs_str);
	for ( ; lhs_it != lhs_end && rhs_it != rhs_end; ++lhs_it, ++rhs_it) {
		auto lhs_c = std::tolower(*lhs_it), rhs_c = std::tolower(*rhs_it);
		if (lhs_c < rhs_c) {
			return -1;
		} else if (lhs_c > rhs_c) {
			return 1;
		}
	}
	if (lhs_it == lhs_end && rhs_it == rhs_end) {
		return 0;
	} else if (lhs_it == lhs_end) {
		return -1;
	} else {
		return 1;
	}
}
