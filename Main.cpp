#include <fstream>
#include <iostream>
#include <iomanip>
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

int main() {

	int choice;

	cout << "\t=================================\n";
	cout << "\t   WELCOME TO LEXICAL ANALYZER\n";
	cout << "\t=================================\n";
	cout << "\t           MAIN MENU\n";
	cout << "   1. Manual\n";
	cout << "   2. Read from a file\n";
	cout << "   3. Exit\n\n";
	cout << "Select your choice: ";
	cin >> choice;
	cin.ignore();

	string line;
	string testWord;
	string word;
	
	LinkedList<string> list;

	switch (choice) {
		case 1: {
			cout << "Input your code: ";
			getline(cin, line);

			// I add char from line to testWord then word one by one
			for (int c = 0; c < line.length(); c++) {
				testWord.clear(); // This is to clear testWord before every check, so it won't accumulate
				testWord = line[c];

				if (testWord == " ") {
					// so the way I do is word will accumulate with char from line over time but if it meet a condition
					// it get input to the list then reset, so if word is empty then there is nothing in word to push into the list so continue to the next char
					if (!word.empty()) {
						list.push_front(check(word), word);
						word.clear();
					}
					continue;
				}
				// So if testWord is an OPERATOR or SEPARATOR
				// then everything from word will be pushed into list
				// The first argument of list is for the token's name
				else if (check(testWord) == "OPERATOR") {
					if (!word.empty()) {
						list.push_front(check(word), word);
						word.clear();

						word.push_back(line.at(c));
						list.push_front(check(word), word);
						word.clear();
					} else {
						word += line[c];
						list.push_front("OPERATOR", word);
						word.clear();
					}
					continue;
				}
				else if (check(testWord) == "SEPARATOR") {
					if (!word.empty()) {
						list.push_front(check(word), word);
						word.clear();

						word.push_back(line.at(c));
						list.push_front(check(word), word);
						word.clear();
					}
					else {
						word.push_back(line.at(c));
						list.push_front(check(word), word);
						word.clear();
					}
					continue;
				}
				word += line[c];
			}
		} break;
		case 2: {
			string fileName;
			cout << "Input the file's name: ";
			getline(cin, fileName);
			fstream myFile(fileName);

			if (myFile.is_open()) {
				string readFile;
				while (getline(myFile, readFile)) {
					for (int c = 0; c < readFile.length(); c++) {
						testWord.clear();
						testWord = readFile[c];

						if (testWord == " ") {
							if (!word.empty()) {
								list.push_front(check(word), word);
								word.clear();
							}
							continue;
						}
						else if (check(testWord) == "OPERATOR") {
							if (!word.empty()) {
								list.push_front(check(word), word);
								word.clear();

								word.push_back(readFile.at(c));
								list.push_front(check(word), word);
								word.clear();
							}
							else {
								word += readFile[c];
								list.push_front("OPERATOR", word);
								word.clear();
							}
							continue;
						}
						else if (check(testWord) == "SEPARATOR") {
							if (!word.empty()) {
								list.push_front(check(word), word);
								word.clear();

								word.push_back(readFile.at(c));
								list.push_front(check(word), word);
								word.clear();
							}
							else {
								word.push_back(readFile.at(c));
								list.push_front(check(word), word);
								word.clear();
							}
							continue;
						}
						else if (c == readFile.length() - 1) {
							word.push_back(readFile.at(c));
							list.push_front(check(word), word);
							word.clear();
							continue;
						}
						word += readFile[c];
					}
				}
			} else {
				cout << "Could not open \"" << fileName << "\" file.\n";
			}

			myFile.close();

		} break;
		default: {
			return 0;
		}
	}
	// Because I push the data into the linked list like a stack
	// so I added a reverse function
	list.reverse();

	cout << endl;
	cout << left;
	cout << setw(20) << "TOKEN" << setw(11) << " " << setw(20) << "LEXEMES" << endl;
	while (!list.isEmpty()) {
		cout << setw(20) << list.showToken() << setw(11) << "=" << setw(20) << list.showLexeme() << endl;
		list.pop_front();
	}
	return 0;
}

string check(string word) {
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