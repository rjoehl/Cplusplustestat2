#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <istream>
#include <ostream>

class Word {
private:
	std::string str{};
public:
	Word();
	Word(std::string &s);

	std::istream & read(std::istream &stream);

	std::string to_str() const;
};

bool operator<(const Word &lhs, const Word &rhs);

bool operator>(const Word &lhs, const Word &rhs);

std::istream & operator>>(std::istream &stream, Word &w);

std::ostream& operator<<(std::ostream& stream, const Word &w);

#endif /* WORD_H_ */
