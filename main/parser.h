#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
// for future additions
class parser
{
    lexer _lexer;
    int address;
    token look;

public:
    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();

    /*Terminal functions goes here use peek and expect*/
    /*use TokenType:: for token names for example
        expect(TokenType::ASSIGN);   //example function call
      */
    // all your parser functions go here
    void Program();
    void D();
    void Variable();
    void Function();
    void parse();
};
#endif
