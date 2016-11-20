#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <iosfwd>

class Word {
private:
	std::string word{};
public:
	Word();
	Word(std::string const &str);

	std::string const & str() const;

	friend std::istream & operator>>(std::istream &stream, Word &w);
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
