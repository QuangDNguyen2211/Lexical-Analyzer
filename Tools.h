#include<string>
#include<fstream>
using namespace std;

#ifndef TOOLS
#define TOOLS

extern const string WHITESPACE;

char	getChar(string prompt);
string	getString(string prompt);
string	getLine(string prompt);
bool	getBool(string prompt);
int		getInt(string prompt);
int		getNonNegativeInt(string prompt);
int		getBoundedInt(string prompt, int lowerBound, int upperBound);
int		getPercent(string prompt);
float	getFloat(string prompt);
int getBoundedIntWithErrorMessage(string prompt, int lowerBound, int upperBound, string errorMessage);

void pause(string prompt = "Press ENTER to continue...");
void flushInput(void);

char	lowerCase(char c);
string	lowerCase(string s);

bool isIn(string pattern, string source);
bool isInCaseless(string pattern, string source);
bool isWhitespace(char c);
bool isEmpty(string s);

void	chomp(string& s);
string	swab(char c, int length);
string	extractWord(string& source);
string	substitute(string source, string pattern, string replacement);
string	pluralize(int count, string singular, string plural);

void swap(int& a, int& b);
int numberWidth(int n);
int randomInt(int lowerBound, int upperBound);

void openIfStream(ifstream& inStream, string prompt);
void openOfStream(ofstream& outStream, string prompt);

#endif



