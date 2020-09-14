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
		     word == "endif" || word == "while" || word == "do" || word == "for" || word == "input" || word == "output" || word == "and" || word == "or" || 
			 word == "not" || word == "whileend") {
		return "KEYWORD";
	}
	else if (word == "'" || word == "(" || word == ")" || word == "{" || word == "}" || word == "[" || word == "]" || word == "," ||
		     word == "." || word == ":" || word == ";") {
		return "SEPARATOR";
	}
	else {
		// Check "word" if it is an integer
		// If yes, return "INTEGER"
		// If no, continue to check "REAL"
		for (int i = 0; i < word.length(); i++) {
			if (isdigit(word[i])) {
				if (i == word.length() - 1) {
					return "INTEGER";
				}
				continue;
			}
			else {
				break;
			}
		}

		// Check "word" if it is a real
		// If yes, return "REAL"
		// If no, "word" can only be "IDENTIFIER"
		for (int i = 0; i < word.length(); i++) {
			if (word[i] == '.') {
				return "REAL";
			}
		}
	}
		
	return "IDENTIFIER";
}

LinkedList<string> checkWord(string line, int &blockComment)
{
	string word;
	string testWord;
	LinkedList<string> list;

	for (int c = 0; c < line.length(); c++) {
		testWord.clear();
		testWord = line[c];

		if (testWord == "!")
			blockComment++;

		if (blockComment == 1 || blockComment == 2) {
			if (blockComment == 2) {
				blockComment = 0;
			}
 			continue;
		} else if (testWord == " ") {
			if (!word.empty()) {
				list.push_back(checkChar(word), word);
				word.clear();
			}
			continue;
		} else if (checkChar(testWord) == "OPERATOR") {
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
		} else if (checkChar(testWord) == "SEPARATOR") {
			if (!word.empty()) {
				// Check if the next letter after "." is an integer
				// If yes, then "." is not a separator in this case
				// Then we know that the word must be a real number
				// Then continue checking the rest number in the next letters of a real number 
				if (isdigit(line[c + 1])) {
					word += line[c];
					continue;
				}
				else {
					list.push_back(checkChar(word), word);
					word.clear();

					word.push_back(line.at(c));
					list.push_back(checkChar(word), word);
					word.clear();
				}
			}
			else {
				word.push_back(line.at(c));
				list.push_back("SEPARATOR", word);
				word.clear();
			}
			continue;
		} else if (c == line.length() - 1) {
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
