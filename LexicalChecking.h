#include <iostream>
#include <string>

using namespace std;

#ifndef LEXICALCHECKING_H
#define	LEXICALCHECKING_H

string checkChar(string word)
{
	if (word == "*" || word == "+" || word == "-" || word == "=" || word == "/" || word == ">" || word == "<" || word == "%") {
		return "OPERATOR";
	}
	else if (word == "int" || word == "float" || word == "bool" || word == "true" || word == "false" || word == "if" || word == "else" || word == "then" ||
		word == "endif" || word == "while" || word == "do" || word == "for" || word == "input" || word == "output" || word == "and" || word == "or" || word == "not") {
		return "KEYWORD";
	}
	else if (word == "'" || word == "(" || word == ")" || word == "{" || word == "}" || word == "[" || word == "]" || word == "," ||
		word == "." || word == ":" || word == ";") {
		return "SEPARATOR";
	}
	else if (word == "0" || word == "1" || word == "2" || word == "3" || word == "4" || word == "5" || word == "6" || word == "7" || word == "8" || word == "9") {
		return "INTEGER";
	}
	else {
		return "IDENTIFIER";
	}
}

LinkedList<string> checkWord(string line)
{
	string word;
	string testWord;
	LinkedList<string> list;

	for (int c = 0; c < line.length(); c++) {
		testWord.clear();
		testWord = line[c];

		if (testWord == " ") {
			if (!word.empty()) {
				list.push_back(checkChar(word), word);
				word.clear();
			}
			continue;
		}
		else if (checkChar(testWord) == "OPERATOR") {
			if (!word.empty()) {
				list.push_back(checkChar(word), word);
				word.clear();

				word.push_back(line.at(c));
				list.push_back(checkChar(word), word);
				word.clear();
			}
			else {
				word += line[c];
				list.push_back("OPERATOR", word);
				word.clear();
			}
			continue;
		}
		else if (checkChar(testWord) == "SEPARATOR") {
			if (!word.empty()) {
				list.push_back(checkChar(word), word);
				word.clear();

				word.push_back(line.at(c));
				list.push_back(checkChar(word), word);
				word.clear();
			}
			else {
				word.push_back(line.at(c));
				list.push_back(checkChar(word), word);
				word.clear();
			}
			continue;
		}
		else if (c == line.length() - 1) {
			word.push_back(line.at(c));
			list.push_back(checkChar(word), word);
			word.clear();
			continue;
		}
		word += line[c];
	}

	return list;
}

#endif
