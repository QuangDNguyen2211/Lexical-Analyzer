#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

// I'm using linked list just so I can store the order and the name of the token with each word/character at the same time
// So what I try to do is that I get the input into the line variable
// After that I added every char from line into word and testWord
// word is the variable that will go into the final list to output
// I noticed that the to identify each lexical are SEPERATOR, OPERATOR or space( )
// So I used input the character from line into testWord first before I put it into word

// This function is for checking if the word is the OPERATOR, SEPERATOR, KEYWORD OR IDENTIFIER
string check(string word);

int main()
{
	string line;
	string testWord;
	string word;
	
	LinkedList<string> list;

	cout << "Enter your input: ";
	getline(cin,line);

	// I add char from line to testWord then word one by one
	for (int c = 0; c < line.length(); c++)
	{
		testWord.clear(); // This is to clear testWord before every check, so it won't accumulate
		testWord.push_back(line.at(c));

		if (testWord == " ")
		{
			// so the way I do is word will accumulate with char from line over time but if it meet a condition
			// it get input to the list then reset, so if word is empty then there is nothing in word to push into the list so continue to the next char
			if (!word.empty())
			{
				list.push_front(check(word), word);
				word.clear();
			}

			continue;
		}
		// So if testWord is an OPERATOR or SEPARATOR
		// then everything from word will be pushed into list
		// The first argument of list is for the token's name
		else if (check(testWord) == "OPERATOR")
		{	
			if (!word.empty())
			{
				list.push_front(check(word), word);
				word.clear();

				word.push_back(line.at(c));
				list.push_front(check(word), word);
				word.clear();
			}
			else
			{
				word.push_back(line.at(c));
				list.push_front(check(word), word);
				word.clear();
			}
			continue;
		}
		else if (check(testWord) == "SEPARATOR")
		{
			if (!word.empty())
			{
				list.push_front(check(word), word);
				word.clear();

				word.push_back(line.at(c));
				list.push_front(check(word), word);
				word.clear();
			}
			else
			{
				word.push_back(line.at(c));
				list.push_front(check(word), word);
				word.clear();
			}

			continue;
		}
		// when it get to the last char
		else if (c == line.length() - 1)
		{
			word.push_back(line.at(c));
			list.push_front(check(word), word);
		}
		word.push_back(line.at(c));
	}

	// Because I push the data into the linked list like a stack
	// so I added a reverse function
	list.reverse();

	cout << "\nTOKEN" << "\t\t\t\t" << "LEXEMES" << endl;
	while (!list.isEmpty())
	{
		cout << list.showToken() << "\t\t\t" << list.showLexeme() << endl;
		list.pop_front();
	}

	cout << "Press ENTER to finish...";
	cin.ignore(999, '\n');

	return 0;
}

string check(string word)
{
	if (word == "*" || word == "+" || word == "-" || word == "=" || word == "/" || word == ">" || word == "<" || word == "%")
		return "OPERATOR";
	else if (word == "int" || word == "float" || word == "bool" || word == "true" || word == "false" || word == "if" || word == "else" || word == "then" ||
		word == "endif" || word == "while" || word == "do" || word == "for" || word == "input" || word == "output" || word == "and" || word == "or" || word == "not")
		return "KEYWORD";
	else if (word == "'" || word == "(" || word == ")" || word == "{" || word == "}" || word == "[" || word == "]" || word == "," ||
		word == "." || word == ":" || word == ";")
		return "SEPARATOR";
	else
		return "IDENTIFIER";
}