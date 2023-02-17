#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// all your tokens go here
enum class TokenType
{
	END_OF_FILE = 0,
	ERROR,
	markazi = 256,
	kaam = 257,
	karo = 258,
	rakho = 259,
	jab = 260,
	tak = 261,
	bas = 262,
	agar = 263,
	to = 264,
	warna = 265,
	phir = 266,
	dekhao = 267,
	lo = 268,
	chalao = 269,
	wapas = 270,
	bhaijo = 271,
	adad = 272,
	khali = 273,
	khatam = 274,

};

// structure of a token
struct token
{
	string lexeme;
	TokenType tokenType; // enum type
	// constructor
	token(string lexeme, TokenType tokenType);
	// constructor default
	token();
	void Print();
};
class lexer
{
	vector<char> stream;  // used for storing file sample_code.ol content
	vector<token> tokens; // vector to store all (tokens,lexeme) pairs
	void Tokenize();	  // populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();				 // just print everything as it is present in file
	token getNextToken();			 // get next token
	void resetPointer();			 // reset pointer to start getting tokens from start
	int getCurrentPointer();		 // get where current pointer in tokens vector is
	void setCurrentPointer(int pos); // move current pointer to wherever
	token peek(int);				 // peek the next token
};

int x = 10;
int x = 10;

#endif // !_LEXER_H
