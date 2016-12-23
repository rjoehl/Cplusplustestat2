# Cplusplustestat2
Second Testat for the C++ Course at HSR

### Word class

Create a class Word that represents a single word. It can be input with `>>` and output with `<<`. When input, a word will only consist of letters `(std::isalpha(c))` and ignore all white-space, digit or punctuation characters. All the latter terminate a word. Thus, an `std::istream` containing the sequence `"compl33tely ~ weird !!??!! 4matted in_put"` would result in six Words `("compl", "tely", "weird", "matted", "in", "put")`. Each call of the input operator reads one word.


* You do not accept empty words, so you continue reading until a word has at least one alphabetical character.
* You can also construct words from `std::string` but guarantee the invariant that it only consists of alphabetical characters. Subsequently, if that constructor is called with an `std::string` containing invalid characters, prevent the Word object from being constructed.
* Words are to be stored in a dictionary later, so they compare with each other IGNORING letter case. Provide the corresponding infrastructure for ALL relational operators WITHOUT using Boost::operators library.

### KWIC - Keyword in Context

####Explanation

From Parnas we have a concise definition of the Keyword in Context problem:

The KWIC index system accepts an ordered set of lines, each line is an ordered set of words, and each word is an ordered set of characters. Any line may be "circularly shifted" by repeatedly removing the first word and appending it at the end of the line. The KWIC index system outputs a listing of all circular shifts of all lines in alphabetical order.

####Task:

Write a program kwic that reads lines from standard input and creates the variations of the line where each word is in front once. Output the stored lines in sorted order, so that you can see, how the words are used in context.

