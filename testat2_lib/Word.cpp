#include "Word.h"

#include <iterator>
#include <algorithm>

Word::Word() {

}

std::istream & Word::read(std::istream &stream) {
	str.erase();
	std::istreambuf_iterator<char> it{stream};
	std::istreambuf_iterator<char> end{};
	stream.peek();
	for (; it != end; ++it) {
		auto c = *it;
		if (std::isalpha(c)) {
			break;
		}
	}
	for (; it != end; ++it) {
		auto c = *it;
		if (!std::isalpha(c)) {
			break;
		}
		str.append(1,c);
	}
	auto is_eof = stream.eof();
	return stream;
}

std::string Word::to_str() const {
	return str;
}

std::istream& operator>>(std::istream& stream, Word &w) {
	return w.read(stream);
}
