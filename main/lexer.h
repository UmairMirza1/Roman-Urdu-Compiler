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
	kaam,
	karo,
	rakho,
	jab,
	tak,
	bas,
	agar,
	to,
	warna,
	phir,
	dekhao,
	lo,
	chalao,
	wapas,
	bhaijo,
	adad,
	khali,
	khatam,
	ID,
	RO,
	LESS_THAN = 300,
	GREATER_THAN,
	EQUAL_TO,
	NOT_EQUAL_TO,
	LESS_THAN_OR_EQUAL_TO,
	GREATER_THAN_OR_EQUAL_TO,

	Output = 350,
	Input = 351,
	Null = 404

	//

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

#endif // !_LEXER_H
