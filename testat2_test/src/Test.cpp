#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "word.h"
#include "kwic.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>

void wordInputOperatorTest() {
	std::istringstream input{"compl33tely ~ weird !!??!! 4matted in_put"};
	std::vector<std::string> words{};
	for (Word w{}; input >> w; words.push_back(w.str())) { }
	std::vector<std::string> expected{"compl", "tely", "weird", "matted", "in", "put"};
	ASSERT_EQUAL(expected, words);
}

void wordConstructorInvalidArgumentTest() {
	ASSERT_THROWS(Word w{"compl33tely"}, std::invalid_argument);
}

void wordOutputOperatorTest() {
	std::string s{"completely"};
	Word w{s};
	std::ostringstream output{};
	output << w;
	std::string result = output.str();
	ASSERT_EQUAL(s, result);
}

void wordLessThanOperatorTest() {
	Word w1{"aabc"}, w2{"aacd"};
	ASSERT_LESS(w1, w2);
}

void wordGreaterThanOperatorTest() {
	Word w1{"aacd"}, w2{"aabc"};
	ASSERT_GREATER(w1, w2);
}

void wordEqualOperatorTest() {
	Word w1{"aabc"}, w2{"aabc"};
	ASSERT_EQUAL(w1, w2);
}

void wordNotEqualOperatorTest() {
	Word w1{"aabc"}, w2{"aacd"};
	ASSERT_NOT_EQUAL_TO(w1, w2);
}

void wordLessOrEqualThanOperatorTest() {
	Word w1{"aabc"}, w2{"aacd"};
	ASSERT_LESS_EQUAL(w1, w2);
}

void wordGreaterOrEqualThanOperatorTest() {
	Word w1{"aacd"}, w2{"aabc"};
	ASSERT_GREATER_EQUAL(w1, w2);
}

void readWordsTest() {
	std::istringstream input{"compl33tely ~ weird !!?"};
	std::vector<Word> words = read_words(input);
	std::vector<Word> expected{ {"compl"}, {"tely"}, {"weird"} };
	ASSERT_EQUAL(expected, words);
}

void kwicTest() {
	Word w1{"compl"}, w2{"tely"}, w3{"weird"};
	std::set<std::vector<Word>> actual = kwic({ {w1, w2, w3} });
	std::set<std::vector<Word>> expected{
		{w1, w2, w3},
		{w2, w3, w1},
		{w3, w1, w2},
	};
	ASSERT_EQUAL(expected, actual);
}

void writeCombinationsTest() {
	std::ostringstream out{};
	Word w1{"compl"}, w2{"asdf"}, w3{"weird"};
	write_combinations({
		{w1, w2, w3},
		{w2, w3, w1},
		{w3, w1, w2},
	}, out);
	std::string expected(
			"asdf weird compl\n"
			"compl asdf weird\n"
			"weird compl asdf\n");
	ASSERT_EQUAL(expected, out.str());
}

void kwicIOTest() {
	std::istringstream in{
		"compl33asdf ~ weird !!?\n"
		"?!! 4matted in_put"
	};
	std::ostringstream out{};
	kwic_io(in, out);
	std::string expected(
			"asdf weird compl\n"
			"compl asdf weird\n"
			"in put matted\n"
			"matted in put\n"
			"put matted in\n"
			"weird compl asdf\n");
	ASSERT_EQUAL(expected, out.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(wordInputOperatorTest));
	s.push_back(CUTE(wordConstructorInvalidArgumentTest));
	s.push_back(CUTE(wordOutputOperatorTest));
	s.push_back(CUTE(wordLessThanOperatorTest));
	s.push_back(CUTE(wordGreaterThanOperatorTest));
	s.push_back(CUTE(wordEqualOperatorTest));
	s.push_back(CUTE(wordNotEqualOperatorTest));
	s.push_back(CUTE(wordLessOrEqualThanOperatorTest));
	s.push_back(CUTE(wordGreaterOrEqualThanOperatorTest));
	s.push_back(CUTE(readWordsTest));
	s.push_back(CUTE(kwicTest));
	s.push_back(CUTE(writeCombinationsTest));
	s.push_back(CUTE(kwicIOTest));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
