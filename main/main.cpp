#include <iostream>
#include "parser.h"
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
	// asking for file name as command line arguments
	if (argc == 2)
	{
		lexer _lexer(argv[1]);

		token t = _lexer.getNextToken();

		while (t.tokenType != TokenType::END_OF_FILE)
		{
			t.Print();
			t = _lexer.getNextToken();
		}
		t.Print();

		parser _parser(argv[1]);
		_parser.parse();
	}
	else if (argc > 2)
	{ // argument limit exceeds
		cout << "Too many arguments" << endl;
	}
	else // if file name is'nt given
	{
		cout << "Please provide a file name" << endl;
	}
	return 0;
}
