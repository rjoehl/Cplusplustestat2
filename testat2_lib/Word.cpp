#include "Word.h"

#include <iterator>
#include <algorithm>

Word::Word() {

}

std::istream & Word::read(std::istream &stream) {
	char c;
	while (true) {
		c = stream.peek();
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
		c = stream.peek();
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
