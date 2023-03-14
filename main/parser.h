#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
// for future additions
class parser
{
    lexer _lexer;
    int address;
    int look;

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
    void Code();
    void matchAscii(int ascii);
    void FuncT();
    void ParameterList();
    void MPL();
    void Koment();
    void Statement();
    void IF();
    void WHILE();
    void Condition();
    void Exp();
    void WG();
    void WP();
    void Stmt();
    void Input(); 
    void Output();
    void Return();
    void InputMsg();
    void Outval();
    void Val();
    void Expression();
    void T();
    void L();
    void RO();
    void R();



};
#endif
