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
	markazi,
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
	LESS_THAN,
	GREATER_THAN,
	EQUAL_TO,
	NOT_EQUAL_TO,
	LESS_THAN_OR_EQUAL_TO,
	GREATER_THAN_OR_EQUAL_TO,
	Output,
	Input ,
	Null,
	Digit,
	string,
	koment,
	Assignment_OP
	

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
	
	void Tokenize();	  // populates tokens vector

	int index;

public:
	vector<token> tokens; // vector to store all (tokens,lexeme) pairs
	lexer();
	lexer(const char filename[]);
	void printRaw();				 // just print everything as it is present in file
	token getNextToken();			 // get next token
	void resetPointer();			 // reset pointer to start getting tokens from start
	int getCurrentPointer();		 // get where current pointer in tokens vector is
	void setCurrentPointer(int pos);
	void addToken (token t);

	 // move current pointer to wherever
	token peek(int);				 // peek the next token
};

#endif // !_LEXER_H
