// This program replaces | . | ; | , | ? | - | ' | characters with whitespace character
// in the file and prints contents of the file without those characters.
// if a text is found within a pair of double quotes the text will be left unprocessed.
//
// Edit 1: Exercise 6
// Edit 2: Exercise 7

#include "chapter_11.hpp"

#include <fstream>
#include <map>
#include <vector>

const std::map<std::string, std::string> contractions {
	{"aren't", "are not"},
	{"can't", "cannot"},
	{"couldn't", "could not"},
	{"could've", "could have"},
	{"didn't", "did not"},
	{"doesn't", "does not"},
	{"don't", "do not"},
	{"e'er", "ever"},
	{"hadn't", "had not"},
	{"hasn't", "has not"},
	{"haven't", "have not"},
	{"he'd", "he had/he would"},
	{"he'll", "he will/he shall"},
	{"he's", "he is/he has"},
	{"i'd", "i had/i would"},
	{"i'll", "i will/i shall"},
	{"i'm", "i am"},
	{"i've", "i have"},
	{"isn't", "is not"},
	{"it'd", "it would"},
	{"it'll","it shall/it will"},
	{"it's", "it is/it has"},
	{"let's", "let us"},
	{"ma'am", "madam"},
	{"mightn't", "might not"},
	{"might've", "might have"},
	{"mustn't", "must not"},
	{"must've", "must have"},
	{"'n'", "and"},
	{"needn't", "need not"},
	{"ne'er", "never"},
	{"o'er", "over"},
	{"ol'", "old"},
	{"oughtn't", "ought not"},
	{"shan't", "shall not"},
	{"she'd", "she had/she would"},
	{"she'll", "she will/she shall"},
	{"she's", "she is/she has"},
	{"shouldn't", "should not"},
	{"should've", "should have"},
	{"that'd", "that would"},
	{"that's", "that is/that has"},
	{"there'd", "there had/there would"},
	{"there'll", "there shall/there will"},
	{"there's", "there has/there is"},
	{"they'd", "they had/they would"},
	{"they'll", "they will/they shall"},
	{"they're", "they are"},
	{"they've", "they have"},
	{"'twas", "it was"},
	{"wasn't", "was not"},
	{"we'd", "we had/we would"},
	{"we'll", "we will"},
	{"we're", "we are"},
	{"we've", "we have"},
	{"weren't", "were not"},
	{"what'll", "what will/what shall"},
	{"what're", "what are"},
	{"what's", "what is/what has/what does"},
	{"what've", "what have"},
	{"where'd", "where did"},
	{"where's", "where is/where has"},
	{"who'd", "who had/who would"},
	{"who'll", "who will/who shall"},
	{"who's", "who is/who has"},
	{"who've", "who have"},
	{"why'd", "why did"},
	{"won't", "will not"},
	{"wouldn't", "would not"},
	{"would've", "would have"},
	{"you'd", "you had/you would"},
	{"you'll", "you will/you shall"},
	{"you're", "you are"},
	{"you've", "you have"}
};

// collects words between double quotes
std::vector<std::string> excluded_words(std::istringstream& is)
{
	std::vector<std::string> words;
	std::string word;
	while (is >> word)
	{
		words.push_back(word);
		if (ends_with(word, '"'))
		{
			break;
		}
	}
	return words;
}

// trims all characters and returns a contraction
// e.g. !isn't. -> isn't
std::string get_contraction(const std::string& str)
{
	std::ostringstream oss;
	for (auto& ch : str)
	{
		if (isalpha(ch) || ch == '\'')
		{
			oss << ch;
		}
	}
	return oss.str();
}

std::string replace_punct(const std::string& str);
// processes a line from file word by word
// replacing non letter characters with whitespace
std::string process_line(const std::string& str)
{
	std::istringstream iss{ str };
	std::string word;
	std::ostringstream oss;
	while (iss >> word)
	{
		if (starts_with(word, '"'))
		{
			oss << word << ' ';
			auto excluded = excluded_words(iss);
			for (auto& w : excluded)
			{
				oss << w << ' ';
			}
		}
		else
		{
			oss << replace_punct(word) << ' ';
		}
	}
	return oss.str();
}

bool is_dash_in_middle(const std::string& str, const std::string::const_iterator& it)
{
	auto begin = str.begin();
	auto end = str.end();
	if ((it != begin && it != end))
	{
		auto prev = it - 1;
		auto next = it + 1;
		return prev != begin && next != end && isalpha(*prev) && isalpha(*next);
	}
	return false;
}

bool is_contraction(const std::string& str, const std::string::const_iterator& it)
{
	auto contr = get_contraction(str);
	auto found = contractions.find(to_lower(contr));
	return found != contractions.end();
}

// replaces punctuation characters with whitespace character
// if word is a contraction it will be replaced by full form
// e.g. I'll with I will
std::string replace_punct(const std::string& str)
{
	std::ostringstream oss;
	size_t offset{ 0 };
	for (auto it = str.begin(); it != str.end();)
	{
		if (ispunct(*it))
		{
			if (*it == '\'' && is_contraction(str, it))
			{
				auto contr = get_contraction(str);
				auto found = contractions.find(to_lower(contr));
				return found->second;
			}
			else if (*it == '-' && is_dash_in_middle(str, it))
			{
				oss << *it;
				++it;
			}
			else
			{
				oss << ' ';
				++it;
			}
		}
		else
		{
			oss << *it;
			++it;
		}
	}
	return oss.str();
}

int main()
{
	auto filename = prompt_filename(FileType::in);
	std::ifstream file{ filename };
	if (!file)
	{
		std::cerr << "Could not open file '" << filename << "' for reading.";
		return -1;
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << process_line(line) << '\n';
	}
}