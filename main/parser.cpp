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
    // cout << "D()" ;

    if (_lexer.peek(1).tokenType == TokenType::kaam)
    {
        Function();
    }
    else if (_lexer.peek(1).tokenType == TokenType::rakho || _lexer.peek(1).tokenType == TokenType::agar ||
             _lexer.peek(1).tokenType == TokenType::jab || _lexer.peek(1).tokenType == TokenType::lo || _lexer.peek(1).tokenType == TokenType::dekhao || _lexer.peek(1).tokenType == TokenType::wapas)
    {
        Code();
    }
    else if (_lexer.peek(1).tokenType == TokenType::koment)
    {
        expect(TokenType::koment);
    }
    else
    {
        parser::syntax_error();
    }
}

void parser::Code()
{
    if (_lexer.peek(1).tokenType == TokenType::rakho ||
        _lexer.peek(1).tokenType == TokenType::lo ||
        _lexer.peek(1).tokenType == TokenType::dekhao ||
        _lexer.peek(1).tokenType == TokenType::wapas)
    {

        Statement();
        Code();
    }
    else if (
        _lexer.peek(1).tokenType == TokenType::agar)

    {
        IF();
        Code();
    }
    else if (_lexer.peek(1).tokenType == TokenType::jab)
    {
        WHILE();
        Code();
    }
    else
    {
        return;
    }
}

void parser::Statement()
{

    Stmt();
    expect(TokenType::koment);
}

// Variable → rakho ID @ adad R
// R → := Val | ^
// Val → ID | Integer | Exp

void parser::Variable()
{
    expect(TokenType::rakho);
    expect(TokenType::ID);
    matchAscii('@');
    expect(TokenType::adad);
    R();
}

void parser::R()
{
    if (_lexer.peek(1).tokenType == TokenType::Assignment_OP)
    {
        // if we give this a token type
        expect(TokenType::Assignment_OP);
        Val();
        // if we do not give this a token type
        matchAscii(':');
        matchAscii('=');
        Val();
    }
    else
    {
        return;
    }
}
void parser::Val()
{
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
    }
    else if (_lexer.peek(1).tokenType == TokenType::Digit)
    {
        expect(TokenType::Digit);
    }
    else if (_lexer.peek(1).lexeme[0] == '-' || _lexer.peek(1).lexeme[0] == '+' || _lexer.peek(1).lexeme[0] == '*' || _lexer.peek(1).lexeme[0] == '/' || _lexer.peek(1).lexeme[0] == '%')
    {
        Expression();
    }
}
void parser::Stmt()
{
    if (_lexer.peek(1).tokenType == TokenType::rakho)
    {
        parser::Variable();
    }
    else if (_lexer.peek(1).tokenType == TokenType::lo)
    {
        parser::Input();
    }
    else if (_lexer.peek(1).tokenType == TokenType::lo)
    {
        parser::Output();
    }
    else if (_lexer.peek(1).tokenType == TokenType::lo)
    {
        parser::Return();
    }
    else
    {
        parser::syntax_error();
    }
}

void parser::InputMsg()
{

    if (_lexer.peek(1).tokenType == TokenType::Input)
    {
        expect(TokenType::Output);
        expect(TokenType::string);
    }
    else
    {
        return;
    }
}

void parser::Outval()
{
    if (_lexer.peek(1).tokenType == TokenType::string)
    {
        expect(TokenType::string);
    }
    // else if (_lexer.peek
    // {
    //     expect(TokenType::Output);
    //     expect(TokenType::ID);
    // }
    else
    {
        syntax_error();
    }
}

void parser::Input()
{

    expect(TokenType::lo);
    InputMsg();
    expect(TokenType::Input);
    expect(TokenType::ID);
}
void parser::Output()
{

    expect(TokenType::dekhao);
    expect(TokenType::Output);
    Outval();
}
void parser::Return() {}

void parser::IF()
{
    expect(TokenType::agar);
    matchAscii('(');
    Condition();
    matchAscii(')');
    expect(TokenType::to);
    expect(TokenType::phir);
    expect(TokenType::karo);
    Koment();
    Code();
    WG();
    WP();
    expect(TokenType::bas);
    expect(TokenType::karo);
    Koment();
}
// Warna Agar --> else if
void parser::WG()
{
    if (_lexer.peek(1).tokenType == TokenType::warna)
    {
        expect(TokenType::warna);
        expect(TokenType::agar);
        Condition();
        expect(TokenType::to);
        expect(TokenType::phir);
        expect(TokenType::karo);
        Code();
    }
    else
    {
        return;
    }
}

// Warna Phir --> else
void parser::WP()
{
    if (_lexer.peek(1).tokenType == TokenType::warna)
    {
        expect(TokenType::warna);
        expect(TokenType::karo);
        Koment();
        Code();
    }
    else
    {
        return;
    }
}

void parser::WHILE()
{

    expect(TokenType::jab);
    expect(TokenType::tak);
    matchAscii('(');
    Condition();
    matchAscii(')');
    expect(TokenType::karo);
    Koment();
    Code();
    expect(TokenType::bas);
    expect(TokenType::karo);
    Koment();
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
    // (  .   )
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        matchAscii('@');
        expect(TokenType::adad);
        MPL();
    }
    else
    {
    }
}

void parser::MPL()
{
    if (int(_lexer.peek(1).lexeme[0]) == '|')
    {
        matchAscii('|');
        ParameterList();
    }
    else
    {
        return;
    }
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

void parser::Condition()
{

    Expression();
    RO();
    Expression();
}

void parser::RO()
{
    if (_lexer.peek(1).tokenType == TokenType::LESS_THAN_OR_EQUAL_TO)
    {
        expect(TokenType::LESS_THAN_OR_EQUAL_TO);
    }
    else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN)
    {
        expect(TokenType::LESS_THAN);
    }
    else if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN)
    {
        expect(TokenType::GREATER_THAN);
    }
    else if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN_OR_EQUAL_TO)
    {
        expect(TokenType::GREATER_THAN_OR_EQUAL_TO);
    }
    else if (_lexer.peek(1).tokenType == TokenType::EQUAL_TO)
    {
        expect(TokenType::EQUAL_TO);
    }
    else if (_lexer.peek(1).tokenType == TokenType::NOT_EQUAL_TO)
    {
        expect(TokenType::NOT_EQUAL_TO);
    }
    else
    {
        parser::syntax_error();
    }
}

// Exp -> T - Exp | T + Exp | T
// T-> L %  T | L /  T | L* T | L
// L-> ID | Integer | ( Exp )

void parser::Expression()
{
    if (_lexer.peek(1).lexeme[0] == '-')
    {
        T();
        matchAscii('-');
        Expression();
    }
    else if (_lexer.peek(1).lexeme[0] == '+')
    {
        T();
        matchAscii('+');
        Expression();
    }
    else
    {
        T(); // check this
    }
}

void parser::T()
{
    if (_lexer.peek(1).lexeme[0] == '%')
    {
        L();
        matchAscii('%');
        T();
    }
    else if (_lexer.peek(1).lexeme[0] == '/')
    {
        L();
        matchAscii('/');
        T();
    }
    else if (_lexer.peek(1).lexeme[0] == '*')
    {
        L();
        matchAscii('*');
        T();
    }
    else
    {
        L(); // check this
    }
}

void parser::L()
{
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
    }
    else if (_lexer.peek(1).tokenType == TokenType::Digit)
    {
        expect(TokenType::Digit);
    }
    else if (_lexer.peek(1).lexeme[0] == '(')
    {
        matchAscii('(');
        Expression();
        matchAscii(')');
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
