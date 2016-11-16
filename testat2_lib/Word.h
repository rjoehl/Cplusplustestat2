#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <istream>

class Word {
private:
	std::string str{};
public:
	Word();

	std::istream & read(std::istream &stream);

	std::string to_str() const;
};

std::istream & operator>>(std::istream &stream, Word &w);

#endif /* WORD_H_ */
