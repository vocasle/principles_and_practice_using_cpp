//
// Created by Nikita Elsakov on 21.03.2020.
//

/*
Sentence:
          Noun Verb                                            // e.g., C++ rules
		  The Noun Verb // e.g. The birds fly
          Sentence Conjunction Sentence      // e.g., Birds fly but fish swim
Conjunction:
          "and"
          "or"
          "but"
Noun:
          "birds"
          "fish"
          "C++"
Verb:
          "rules"
          "fly"
          "swim”
*/

#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

bool isValidWord(const std::string& word);

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

std::vector<std::string> readSentence()
{
	std::string word{};
	std::vector<std::string> words{};
	for (; std::cin >> word;)
	{
		if (!isValidWord(word))
			error(word + " is not valid");
		words.push_back(word);
		if (word == ".")
			break;
	}
	return words;
}

bool isValidWord(const std::string& word)
{
	constexpr const char* words[]{
		"the",
		"and",
		"or",
		"but",
		"birds",
		"fish",
		"C++",
		"rules",
		"fly",
		"swim",
		"."
	};

	for (auto&& w : words)
	{
		if (w == word)
			return true;
	}
	return false;
}

int main()
{
	std::cout << "Enter a sentence terminated by dot and press enter. "
			  << "\nThere must be a space character after last word in sentence and dot.\n";

	auto sentence = readSentence();
	std::stringstream ss{};
	std::for_each(sentence.begin(), sentence.end(), [&](auto w)
	{
	  ss << w << ' ';
	});
	std::cout << ss.str() << std::endl;
	return 0;
}
