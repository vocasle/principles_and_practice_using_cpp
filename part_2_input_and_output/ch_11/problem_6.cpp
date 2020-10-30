// This program replaces | . | ; | , | ? | - | ' | characters with whitespace character
// in the file and prints contents of the file without those characters.
// if a text is found within a pair of double quotes the text will be left unprocessed.
//
// Edit 1: Exercise 6
// Edit 2: Exercise 7
// Edit 3: Exercise 8

#include "chapter_11.hpp"

#include <fstream>
#include <map>
#include <algorithm>

#include "PunctStream.hpp"

// small map of contractions
const std::map<std::string, std::string> contractions{
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

// extracts 'wordWith'apostrophe' from string str
std::string get_contraction(const std::string& str, const std::string::iterator& it)
{
	auto pos = it - str.begin();
	size_t begin = find_left(str, pos, isalpha) + 1;
	size_t end = find_right(str, pos, isalpha);
	if (begin <= str.size() && end <= str.size())
	{
		return str.substr(begin, end - begin);
	}
	return "";
}

// helper function that detects wether next and previous characters are letters
bool is_dash_in_middle(const std::string& str, const std::string::iterator& it)
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

// callback function that keeps dash between two words intact
void escape_dash(std::string& str, std::string::iterator& it)
{
	if (!is_dash_in_middle(str, it))
	{
		str.at(it - str.begin()) = ' ';
	}
	++it;
}

// callback function that replaces contraction with full form
void replace_contraction(std::string& str, std::string::iterator& it)
{
	if (it == str.end() || it == str.begin())
	{
		return;
	}
	auto contr = get_contraction(str, it);
	if (!contr.empty())
	{
		auto repl = contractions.find(to_lower(contr));
		if (repl != contractions.end())
		{
			// move iterator to begining of the contraction
			it -= contr.find('\'');
			// restore correct case
			if (isupper(contr.at(0)))
			{
				replace(str, contr, capitalize(repl->second));
			}
			else
			{
				replace(str, contr, repl->second);
			}
			// move iterator to end of the replacement
			it += repl->second.size();
			return;
		}
	}
	str.at(it - str.begin()) = ' ';
	++it;
}

// callback function that keeps strings inside double quotes intact
void escape_quotes(std::string& str, std::string::iterator& it)
{
	auto begin = it - str.begin();
	auto end = str.find('"', begin + 1);
	if (end != std::string::npos)
	{
		auto substr = str.substr(begin, end - begin + 1);
		it += substr.size();
	}
	else
	{
		++it;
	}
}

// constructs a dictionary of the words that were found in the file
std::vector<std::string> get_dictionary(const std::string& file_name)
{
	std::ifstream file{ file_name };
	if (!file)
	{
		error("Could not open '" + file_name + "' for reading.");
	}
	PunctStream ps{ file, ";:,.?!()\"{}-<>/&$@#%^'*|~", true, '*' };
	ps.register_callback(replace_contraction, '\'');
	ps.register_callback(escape_dash, '-');
	ps.register_callback(escape_quotes, '"');
	std::vector<std::string> words;
	std::string word;
	while (ps >> word)
	{
		words.push_back(word);
	}
	std::sort(words.begin(), words.end());
	remove_duplicates(words);
	return words;
}

int main()
{
	auto filename = prompt_filename(FileType::in);
	try
	{
		auto dict = get_dictionary(filename);
		print_vector(dict, ' ');
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}