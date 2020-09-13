#include "LinkedList.h"
#include "LexicalChecking.h"
#include "Tools.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main() {

	int choice;
	LinkedList<string> list;

	cout << "\t=================================\n"
		<< "\t   WELCOME TO LEXICAL ANALYZER\n"
		<< "\t=================================\n"
		<< "\t           MAIN MENU\n"
		<< "   1. Manual\n"
		<< "   2. Read from a file\n"
		<< "   3. Exit\n\n";
	choice = getBoundedInt("Select your choice: ", 1, 3);

	switch (choice) 
	{
		case 1: 
		{
			string line;
			cout << "Input your code: ";
			getline(cin, line);
			list = checkWord(line);
		} break;
		case 2: 
		{
			string fileName;
			while(true)
			{
				cout << "Input the file's name: ";
				getline(cin, fileName);
				fstream myFile(fileName);
				if (myFile.fail())
				{
					cout << "Could not open \"" << fileName << "\" file or file does not exist.\n";
					continue;
				}
				else {
					string readFile;
					while (getline(myFile, readFile)) {
						list = list + checkWord(readFile);
					}
				}

				myFile.close();
				break;
			}
		} break;
		default:	return 0;
	}


	cout << endl;
	cout << left;
	cout << setw(20) << "TOKEN" << setw(11) << " " << setw(20) << "LEXEMES" << endl;
	while (!list.isEmpty()) {
		cout << setw(20) << list.showToken() << setw(11) << "=" << setw(20) << list.showLexeme() << endl;
		list.pop_front();
	}
	return 0;
}
