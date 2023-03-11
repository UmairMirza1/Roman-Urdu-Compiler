#include "parser.h"

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}

// match function
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type)
        syntax_error();
    return t;
}
parser::parser(const char filename[])
{
    _lexer = lexer(filename);
}
void parser::readAndPrintAllInput() // read and print allinputs (provided)
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }
}
void parser::resetPointer()
{
    _lexer.resetPointer();
}

void parser::Program()
{

    if (_lexer.peek(1).tokenType == TokenType::END_OF_FILE)
    {
        cout << "Program is correct\n";
        return;
    }
    else if (_lexer.peek(1).tokenType == TokenType::kaam || _lexer.peek(1).tokenType == TokenType::rakho || _lexer.peek(1).tokenType == TokenType::agar ||
             _lexer.peek(1).tokenType == TokenType::jab || _lexer.peek(1).tokenType == TokenType::lo || _lexer.peek(1).tokenType == TokenType::dekhao)
    {
        D();
        Program();
    }
    else
    {
        return;
    }
}

void parser::D()
{

    if (_lexer.peek(1).tokenType == TokenType::kaam)
    {
        Function();
    }
    else if (_lexer.peek(1).tokenType == TokenType::rakho || _lexer.peek(1).tokenType == TokenType::agar ||
             _lexer.peek(1).tokenType == TokenType::jab || _lexer.peek(1).tokenType == TokenType::lo || _lexer.peek(1).tokenType == TokenType::dekhao)
    {
        Code();
    }
    else
    {
        parser::syntax_error();
    }
}

void parser::Code()
{
    // ye hum kal likheng eg kyu k hauamar fimaghj nih chalhjrioewgiu9o;egqwio;ucfvgbedrwlo;.ugbher
    return;
}

void parser::Function()
{

    expect(TokenType::kaam);
    expect(TokenType::ID);
    matchAscii('@');
    FuncT();
    matchAscii('(');
    ParameterList();
    matchAscii(')');
    expect(TokenType::karo);
    Koment();
    Code();
    expect(TokenType::kaam);
    expect(TokenType::khatam);
    Koment();
}

void parser::Koment()
{
    if (_lexer.peek(1).tokenType == TokenType::koment)
    {
        expect(TokenType::koment);
        return;
    }
    else
    {
        return;
    }
}

void parser::ParameterList()
{
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {

        expect(TokenType::ID);
        matchAscii('@');
        expect(TokenType::adad);
        MPL();
    }
    else if (int(_lexer.peek(2).lexeme[0]) == ')')
    {
        return;
    }
    else
    {
        parser::syntax_error();
    }
}
// ( id@adad , )
void parser::MPL()
{

    matchAscii('|');
    ParameterList();
}

void parser::FuncT()
{

    if (_lexer.peek(1).tokenType == TokenType::khali || _lexer.peek(1).tokenType == TokenType::adad)
    {
        return;
    }
    else
    {
        parser::syntax_error();
    }
}

void parser::matchAscii(int ascii)
{

    token t = _lexer.getNextToken();
    if (int(t.lexeme[0]) == ascii)
    {
        return;
    }
    else
    {
        parser::syntax_error();
    }
}

// void match(int tok) {
// if (look == tok)
// look = nextTok();
// else{
// parser::syntax_error();

// }

void parser::parse()
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
    }
}

// this function is for sample purposes only
// bool parser::statements()
// {
//     //statements-- > COLON LPAREN start RPAREN
//     if (_lexer.peek(1).tokenType == TokenType::COLON)
//     {
//         expect(TokenType::COLON);
//         if (_lexer.peek(1).tokenType == TokenType::LPAREN)
//         {
//             expect(TokenType::LPAREN);
//             start();
//             if (_lexer.peek(1).tokenType == TokenType::RPAREN)
//             {
//                 expect(TokenType::RPAREN);
//                 return true;
//             }
//         }
//     }
//     return false;
// }
