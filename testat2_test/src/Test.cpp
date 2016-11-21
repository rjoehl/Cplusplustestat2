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

void word_ctor_should_accept_alphabetical_string() {
	Word{"Building"};
}

void word_ctor_should_throw_when_non_alphabetical_string() {
	ASSERT_THROWS(Word w{"compl3tely"}, std::invalid_argument);
}

void word_str_should_return_the_word() {
	ASSERT_EQUAL(Word{"Street"}.str(), "Street");
}

void word_sewer_should_equal_sewer() {
	ASSERT_EQUAL(Word{"Sewer"}, Word{"Sewer"});
	ASSERT_EQUAL(false, Word{"Sewer"} != Word{"Sewer"});
	ASSERT_EQUAL(false, Word{"Sewer"} < Word{"Sewer"});
	ASSERT_EQUAL(false, Word{"Sewer"} > Word{"Sewer"});
	ASSERT_LESS_EQUAL(Word{"Sewer"}, Word{"Sewer"});
	ASSERT_GREATER_EQUAL(Word{"Sewer"}, Word{"Sewer"});
}

void word_door_should_be_less_than_window() {
	ASSERT_NOT_EQUAL_TO(Word{"Door"}, Word{"Window"});
	ASSERT_EQUAL(true, Word{"Door"} != Word{"Window"});
	ASSERT_LESS(Word{"Door"}, Word{"Window"});
	ASSERT_EQUAL(false, Word{"Door"} > Word{"Window"});
	ASSERT_LESS_EQUAL(Word{"Door"}, Word{"Window"});
	ASSERT_EQUAL(false, Word{"Door"} >= Word{"Window"});
}

void word_window_should_be_greater_than_door() {
	ASSERT_NOT_EQUAL_TO(Word{"Window"}, Word{"Door"});
	ASSERT_EQUAL(true, Word{"Window"} != Word{"Door"});
	ASSERT_GREATER(Word{"Window"}, Word{"Door"});
	ASSERT_EQUAL(false, Word{"Window"} < Word{"Door"});
	ASSERT_GREATER_EQUAL(Word{"Window"}, Word{"Door"});
	ASSERT_EQUAL(false, Word{"Window"} <= Word{"Door"});
}

void word_should_input_only_alphabetical_characters() {
	std::istringstream input{"compl33tely ~ weird !!??!! 4matted in_put"};
	std::vector<std::string> words{};
	for (Word w{}; input >> w; words.push_back(w.str())) { }
	std::vector<std::string> expected{"compl", "tely", "weird", "matted", "in", "put"};
	ASSERT_EQUAL(expected, words);
}

void word_should_output_the_word() {
	Word w{"completely"};
	std::ostringstream output{};
	output << w;
	ASSERT_EQUAL(w.str(), output.str());
}

void kwic_read_words_should_read_all_words() {
	std::istringstream input{"this is a test"};
	std::vector<Word> expected{ {"this"}, {"is"}, {"a"}, {"test"} };
	ASSERT_EQUAL(expected, read_words(input));
}

void kwic_kwic_should_generate_all_combinations() {
	Word this_{"this"}, is{"is"}, a{"a"}, test{"test"}, another{"another"};
	std::set<std::vector<Word>> expected{
		{this_, is, a, test},
		{is, a, test, this_},
		{a, test, this_, is},
		{test, this_, is, a},
		{this_, is, another, test},
		{is, another, test, this_},
		{another, test, this_, is},
		{test, this_, is, another}
	};
	ASSERT_EQUAL(expected, kwic({
		{this_, is, a, test},
		{this_, is, another, test}
	}));
}

void kwic_write_combinations_should_write_all_combinations() {
	Word this_{"this"}, is{"is"}, a{"a"}, test{"test"}, another{"another"};
	std::ostringstream output{};
	write_combinations({
		{this_, is, a, test},
		{is, a, test, this_},
		{a, test, this_, is},
		{test, this_, is, a},
		{this_, is, another, test},
		{is, another, test, this_},
		{another, test, this_, is},
		{test, this_, is, another}
	}, output);
	std::string expected(
			"a test this is\n"
			"another test this is\n"
			"is a test this\n"
			"is another test this\n"
			"test this is a\n"
			"test this is another\n"
			"this is a test\n"
			"this is another test\n");
	ASSERT_EQUAL(expected, output.str());
}

void kwic_kwic_io_should_read_the_lines_and_write_all_combinations() {
	std::istringstream input{
		"this is a test\n"
		"this is another test"
	};
	std::ostringstream output{};
	kwic_io(input, output);
	std::string expected(
			"a test this is\n"
			"another test this is\n"
			"is a test this\n"
			"is another test this\n"
			"test this is a\n"
			"test this is another\n"
			"this is a test\n"
			"this is another test\n");
	ASSERT_EQUAL(expected, output.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(word_ctor_should_accept_alphabetical_string));
	s.push_back(CUTE(word_ctor_should_throw_when_non_alphabetical_string));
	s.push_back(CUTE(word_str_should_return_the_word));
	s.push_back(CUTE(word_sewer_should_equal_sewer));
	s.push_back(CUTE(word_door_should_be_less_than_window));
	s.push_back(CUTE(word_window_should_be_greater_than_door));
	s.push_back(CUTE(word_should_input_only_alphabetical_characters));
	s.push_back(CUTE(word_should_output_the_word));
	s.push_back(CUTE(kwic_read_words_should_read_all_words));
	s.push_back(CUTE(kwic_kwic_should_generate_all_combinations));
	s.push_back(CUTE(kwic_write_combinations_should_write_all_combinations));
	s.push_back(CUTE(kwic_kwic_io_should_read_the_lines_and_write_all_combinations));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
