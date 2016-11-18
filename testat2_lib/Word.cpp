#include "Word.h"

#include <algorithm>
#include <stdexcept>

Word::Word() {

}

Word::Word(std::string &s) {
	std::for_each(begin(s), end(s), [this](auto &c) {
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

std::string Word::to_str() const {
	return str;
}

std::istream& operator>>(std::istream& stream, Word &w) {
	return w.read(stream);
}

std::ostream& operator<<(std::ostream& stream, const Word &w) {
	stream << w.to_str();
	return stream;
}
