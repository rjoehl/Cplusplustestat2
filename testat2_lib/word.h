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

bool operator==(Word const &lhs, Word const &rhs);

bool operator!=(Word const &lhs, Word const &rhs);

bool operator<(Word const &lhs, Word const &rhs);

bool operator<=(Word const &lhs, Word const &rhs);

bool operator>(Word const &lhs, Word const &rhs);

bool operator>=(Word const &lhs, Word const &rhs);

std::istream & operator>>(std::istream &stream, Word &w);

std::ostream & operator<<(std::ostream &stream, Word const &w);

#endif /* WORD_H_ */
