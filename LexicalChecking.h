/*
	Members: Vinh Tran
			 Quang Nguyen
	Course: CPSC 323 - 04
	Professor: Anthony Le
	Assignment 1: Lexical Analyzer
*/

#include <iostream>
#include <string>
#include "Tools.h"

using namespace std;
/*
	Q = { 0 (ENTRY), 1 (ALPHA), 2 (DIGIT), 3 (REAL) }
	q0 = 0 (ENTRY)
*/
enum FINITE_STATE_MACHINE {
	ENTRY = 0,
	IDENTIFIER = 1,
	INTEGER = 2,
	REAL = 3,
};

/*
		  |				 LETTER				    DIGIT				OTHER
	N:	  | Input:  [a...z][A...Z][$]		   [0...9]				 [.]
		  | Treat as      l                       d                   .
__________|______________________________________________________________
-->   0   |               1                       2                   0
	  1   |				  1					      1					  0
	  2   |				  0					      2					  3
	  3   |				  0					      3					  0
*/
int state[5][3] = { {IDENTIFIER, INTEGER, REAL},
					{IDENTIFIER, IDENTIFIER, ENTRY},
					{ENTRY, INTEGER, REAL},
					{ENTRY, REAL , ENTRY} };

string checkState(int state) {
	if (state == IDENTIFIER) {
		return "IDENTIFIER";
	}
	else if (state == INTEGER) {
		return "INTEGER";
	}
	else {
		return "REAL";
	}
}

// Check the token of a word or a character
string lexer(string word)
{
	// If the word belongs to and operator, keyword or separator
	// it will be easily compare
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
	// This is for checking if the word is an identifier, a real or an int
	else {
		// Initialize the entry state for FSM
		int currentState = 0;

		for (int c = 0; c < word.length(); c++) {
			int col;
			if (word[c] == '.') {
				col = 2;
			}
			else if (isdigit(word[c])) {
				col = 1;
			}
			else {
				col = 0;
			}
			currentState = state[currentState][col];
		}
		return checkState(currentState);
	}
}


// Check each letter in a string
LinkedList<string> checkWord(string line, int& blockComment)
{
	string word;
	string testWord;
	LinkedList<string> list;

	for (int c = 0; c < line.length(); c++) {
		testWord.clear();
		testWord = line[c];


		if (testWord == "!")
			blockComment++;
		// If the program see ! and the blockComment variable is not == to 2
		// it will skip that char
		if (blockComment == 1 || blockComment == 2) {
			if (blockComment == 2) {
				blockComment = 0;
			}
			continue;
		}

		// This is to check if the word is not empty and the first char of the word
		// is not a letter but testWord is then it will do a lexical
		// checking the word
		else if (!isEmpty(word) && !isalpha(word[0]) && isalpha(testWord[0])) {
			list.push_back(lexer(word), word);
			word.clear();
		}
		else if (testWord == " " || testWord == "\t") {
			if (!word.empty()) {
				list.push_back(lexer(word), word);
				word.clear();
			}
			continue;
		}
		else if (lexer(testWord) == "OPERATOR") {
			if (!word.empty()) {
				list.push_back(lexer(word), word);
				word.clear();

				list.push_back("OPERATOR", testWord);
			}
			else {
				list.push_back("OPERATOR", testWord);
			}
			continue;
		}
		else if (lexer(testWord) == "SEPARATOR") {
			if (!word.empty()) {
				if (testWord == ".") {
					// The program will loop through the word to see if there are any digit on it
					for (int i = 0; i < word.length(); i++)
					{
						// If it found one that is not, it will do the lexical checking for that word
						// before pushing "." in the list
						if (!isdigit(word[i]))
						{
							list.push_back(lexer(word), word);
							word.clear();

							list.push_back("SEPARATOR", testWord);
							break;
						}
						// If it reaches the end and no non-digit char is found then it will push "." into word
						if (i == word.length() - 1)
						{
							word += line[c];
							// If it is at the end of the line then do a lexical checking for the word
							if (c == line.length() - 1)
							{
								list.push_back(lexer(word), word);
								word.clear();
							}
							break;
						}
					}
				}
				// This is for if the testWord is not "."
				else
				{
					list.push_back(lexer(word), word);
					word.clear();

					list.push_back("SEPARATOR", testWord);
				}
			}
			else {
				list.push_back("SEPARATOR", testWord);
			}
			continue;
		}

		// Combine a single checked character of 'testWord' into 'word'
		word += line[c];

		if (c == line.length() - 1) {
			list.push_back(lexer(word), word);
			word.clear();
		}
	}

	return list;
}
