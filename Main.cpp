/*
	Members: Vinh Tran
			 Quang Nguyen
	
	Course: CPSC 323 - 04

	Professor: Anthony Le
	
	Assignment 1: Lexical Analyzer
*/

#include "LinkedList.h"
#include "LexicalChecking.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Show lexical analyzers onto the screen
void display(LinkedList<string> data) {
	cout << endl;
	cout << left;
	cout << setw(20) << "TOKEN" << setw(11) << " " << setw(20) << "LEXEMES" << endl;
	cout << "--------------------------------------\n";
	while (!data.isEmpty()) {
		cout << setw(20) << data.showToken() << setw(11) << "=" << setw(20) << data.showLexeme() << endl;
		data.pop_front();
	}
}

// Save lexical analyzers into a file
void saveOutput(LinkedList<string> data) {
	ofstream writeFile("output.txt");

	// Write all lexical analyzers into a default file named "output.txt"
	writeFile << left;
	writeFile << setw(20) << "TOKEN" << setw(11) << " " << setw(20) << "LEXEMES" << endl;
	writeFile << "--------------------------------------\n";
	while (!data.isEmpty()) {
		writeFile << setw(20) << data.showToken() << setw(11) << "=" << setw(20) << data.showLexeme() << endl;
		data.pop_front();
	}

	writeFile.close();
}

int main() {
	// Variable for reading user's input for selecting the mode of the lexical analyzer
	int choice;
	// Design the menu driven for the program
		// Mode 1: Let user input a partial code and analyze them
		// Mode 2: Do the lexical analyzer from a specific file
	cout << "\t=================================\n"
		<< "\t   WELCOME TO LEXICAL ANALYZER\n"
		<< "\t=================================\n"
		<< "\t           MAIN MENU\n"
		<< "   1. Manual\n"
		<< "   2. Read from a file\n"
		<< "   3. Exit\n\n";

	cout << "Select your choice [Integer Only]: ";
	// Get and check user's input
	// If user inputted '1', the program will be in Mode 1
	// If user inputted '2', the program will be in Mode 2
	// If user inputted '3', the program will be terminal
	// If user's input is bad, ask them to input again
	while (!(cin >> choice) || (choice != 1 && choice != 2 && choice != 3)) {
		if (choice < 1 || choice > 3) {
			cout << "Input invalid.\n";
			cout << "Select your choice [Integer Only]: ";
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}
	cin.ignore();
	
	// Variable for counting and checking a single or block comment
	int blockComment = 0;

	// Define the instance named "list" for the object "LinkedList"
	// "list" will contain two data which are tokens and lexemes
	LinkedList<string> list;

	switch (choice) 
	{
		case 1: 
		{
			string line;
			cout << "\nInput your code: ";
			// Get user's input
			getline(cin, line);
			// Call function "checkWord()" to do the lexical analyzer
			// Then store the data (tokens and lexemes) into "list" if any
			list = checkWord(line, blockComment);
			// Show the result onto the screen
			display(list);
		} break;
		case 2: 
		{
			string fileName;
			while (true)
			{
				cout << "\nInput the file's name: ";
				// Get user's input
				getline(cin, fileName);
				// Open the file
				fstream myFile(fileName);
				if (myFile.is_open())
				{	
					// Read line by line from a file
					// Then call function "checkWord()" to do the lexical analyzer of each line
					// Store the data (tokens and lexemes) into "list" if any
					string readFile;
					while (getline(myFile, readFile)) {
						list = list + checkWord(readFile, blockComment);
					}
				}
				else {
					// Show the error and ask user's input again
					cout << "Could not open \"" << fileName << "\" file or file does not exist.\n";
					continue;
				}
				// Close the file
				myFile.close();
				// Create and save the result into a file
				saveOutput(list);
				// Show the result onto the screen
				display(list);
				cout << "\nLexical Analyzers saved into a file \"output.txt\" as default.\n";
				break;
			}
		} break;
		default: 
		{
			// The program will be terminal when entered '3'
			cout << "The program was terminated.\n";
			return 0;
		}
	}
	return 0;
}
