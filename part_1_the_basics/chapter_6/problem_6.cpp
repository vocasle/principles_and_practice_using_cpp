//
// Created by Nikita Elsakov on 21.03.2020.
//

/*
Sentence:
          Noun Verb                                            // e.g., C++ rules
		  Article Noun Verb // e.g. The birds fly
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
Article:
		  "the"
*/

#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

std::string readArticle()
{
	std::string article{};
	std::cin >> article;
	if (article != "the")
	{
		for (auto it = article.end() - 1; it >= article.begin(); --it)
			std::cin.putback(*it);
		article = "";
	}
	return article;
}

std::string readNoun()
{
	auto noun = readArticle();
	std::stringstream ss{};
	std::cin >> noun;
	if (noun == "the")
		ss << noun << ' ';
	if (noun == "C++" || noun == "birds" || noun == "fish")
		ss << noun;
	else
		error(noun + " is not a valid noun");
	return ss.str();
}

std::string readVerb()
{
	const std::vector<std::string> verbs{
		"swim",
		"fly",
		"rules"
	};
	std::string verb{};
	std::cin >> verb;
	if (std::find(verbs.begin(), verbs.end(), verb) == verbs.end())
		error(verb + " is not a valid verb");
	return verb;
}

std::string readConjunction()
{
	const auto conjunctions = {
		"and",
		"but",
		"or"
	};
	std::string conjunction{};
	std::cin >> conjunction;
	if (conjunction == ".")
		return conjunction;
	else if (std::find(conjunctions.begin(), conjunctions.end(), conjunction)
		== conjunctions.end())
		error(conjunction + " is not a valid conjunction");
	return conjunction;
}

std::string readSentence()
{
	std::stringstream ss{};
	auto noun = readNoun();
	auto verb = readVerb();
	auto conjunction = readConjunction();
	ss << noun << ' ' << verb << ' ' << conjunction;
	if (conjunction != ".")
		ss << ' ' << readSentence();
	return ss.str();
}

int main()
{
	std::cout << "Enter a sentence terminated by dot and press enter. "
			  << "\nThere must be a space character after last word in sentence and dot.\n";

	try
	{
		auto sentence = readSentence();
		std::cout << "OK" << std::endl;
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
