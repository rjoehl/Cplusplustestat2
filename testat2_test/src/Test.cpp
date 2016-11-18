#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "Word.h"
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

void wordInputTest() {
	std::istringstream input{"compl33tely ~ weird !!??!! 4matted in_put"};
	std::vector<std::string> words{};
	for (Word w{}; input >> w; words.push_back(w.to_str()))	{ }
	std::vector<std::string> expected{"compl", "tely", "weird", "matted", "in", "put"};
	ASSERT_EQUAL(expected, words);
}

void wordConstructorInvalidArgumentTest() {
	std::string s{"compl33tely"};
	ASSERT_THROWS(Word w{s}, std::invalid_argument);
}

void wordOutputlTest() {
	std::string s{"completely"};
	Word w{s};
	std::ostringstream output{};
	output << w;
	std::string result = output.str();
	ASSERT_EQUAL(s, result);
}

void wordLessThanOperatorTest() {
	std::string s1{"aabc"}, s2{"aacd"};
	Word w1{s1}, w2{s2};
	ASSERT_LESS(w1, w2);
}

void wordGreaterThanOperatorTest() {
	std::string s1{"aabc"}, s2{"aacd"};
	Word w1{s2}, w2{s1};
	ASSERT_GREATER(w1, w2);
}

void wordEqualOperatorTest() {
	std::string s1{"aabc"}, s2{"aabc"};
	Word w1{s1}, w2{s2};
	ASSERT_EQUAL(w1, w2);
}

void wordNotEqualOperatorTest() {
	std::string s1{"aabc"}, s2{"aacd"};
	Word w1{s1}, w2{s2};
	ASSERT_NOT_EQUAL_TO(w1, w2);
}

void wordLessOrEqualThanOperatorTest() {
	std::string s1{"aabc"}, s2{"aacd"};
	Word w1{s1}, w2{s2};
	ASSERT_LESS_EQUAL(w1, w2);
}

void wordGreaterOrEqualThanOperatorTest() {
	std::string s1{"aabc"}, s2{"aacd"};
	Word w1{s2}, w2{s1};
	ASSERT_GREATER_EQUAL(w1, w2);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(wordInputTest));
	s.push_back(CUTE(wordConstructorInvalidArgumentTest));
	s.push_back(CUTE(wordOutputlTest));
	s.push_back(CUTE(wordLessThanOperatorTest));
	s.push_back(CUTE(wordGreaterThanOperatorTest));
	s.push_back(CUTE(wordEqualOperatorTest));
	s.push_back(CUTE(wordNotEqualOperatorTest));
	s.push_back(CUTE(wordLessOrEqualThanOperatorTest));
	s.push_back(CUTE(wordGreaterOrEqualThanOperatorTest));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
