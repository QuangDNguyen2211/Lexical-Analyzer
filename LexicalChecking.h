#include <iostream>
#include <string>

using namespace std;

#ifndef LEXICALCHECKING_H
#define	LEXICALCHECKING_H

// Do the lexical analyzer
string lexer(string word)
{
	if (word == "*" || word == "+" || word == "-" || word == "=" || word == "/" || word == ">" || word == "<" || word == "%") {
		return "OPERATOR";
	}
	else if (word == "int" || word == "float" || word == "bool" || word == "true" || word == "false" || word == "if" || word == "else" || word == "then" ||
		     word == "endif" || word == "while" || word == "do" || word == "for" || word == "input" || word == "output" || word == "and" || word == "or" || 
			 word == "not" || word == "whileend" || word == "double") {
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

// Break the string into a single character
// Then take turn to analyze them
LinkedList<string> checkWord(string line, int &blockComment)
{
	string word;
	string testWord;
	LinkedList<string> list;

	// Go through each letter of a string
	for (int c = 0; c < line.length(); c++) {
		testWord.clear();
		testWord = line[c];

		// If the character is "!", then the string should be a single or a block comment
		if (testWord == "!")
			blockComment++;

		// Ignore all comments
		if (blockComment == 1 || blockComment == 2) {
			if (blockComment == 2) {
				blockComment = 0;
			}
 			continue;
		}
		// If the character is a whitespace, 
		// then start analyzing by combining all characters before a whitespace into a sub-string
		// store the lexical analyzer into "list" if any
		// continue to check the rest character
		else if (testWord == " ") {
			if (!word.empty()) {
				list.push_back(lexer(word), word);
				word.clear();
			}
			continue;
		}
		// Check if the character is an operator
		// store the lexical analyzer into "list" if any
		// continue to check the rest character 
		else if (lexer(testWord) == "OPERATOR") {
			if (!word.empty()) {
				list.push_back(lexer(word), word);
				word.clear();

				word += line[c];
				list.push_back(lexer(word), word);
				word.clear();
			}
			else {
				word += line[c];
				list.push_back("OPERATOR", word);
				word.clear();
			}
			continue;
		}
		// Check if the character is an separator
		// store the lexical analyzer into "list" if any
		// continue to check the rest character
		else if (lexer(testWord) == "SEPARATOR") {
			if (!word.empty()) {
				// Check if the next letter after "." is an integer
				// If yes, then "." is not a separator in this case
				// Then the word must be a real number
				// Then continue checking the rest number in the next letters of a real number 
				if (isdigit(line[c + 1])) {
					word += line[c];
					continue;
				}
				else {
					list.push_back(lexer(word), word);
					word.clear();

					word += line[c];
					list.push_back(lexer(word), word);
					word.clear();
				}
			}
			else {
				word += line[c];
				list.push_back("SEPARATOR", word);
				word.clear();
			}
			continue;
		}
		// Check the last character of the string
		// store the lexical analyzer into "list" if any
		// continue to check the rest character
		else if (c == line.length() - 1) {
			word += line[c];
			list.push_back(lexer(word), word);
			word.clear();
			continue;
		}

		// Combine characters into a sub-string to do the lexical analyzer
		word += line[c];
	}

	// Return all data stored in "list"
	return list;
}

#endif
