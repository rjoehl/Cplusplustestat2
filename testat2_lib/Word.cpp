#include "Word.h"


Word::Word() {

}

std::istream & Word::read(std::istream &stream) {
	stream >> str;
	return stream;
}

std::string Word::to_str() const {
	return str;
}

std::istream& operator>>(std::istream& stream, Word &w) {
	return w.read(stream);
}
