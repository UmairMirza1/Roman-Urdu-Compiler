#include "parser.h"
#include "lexer.h"

// string reserved2[] = {
//     "END_OF_FILE",
//     "ERROR",
//     "markazi",
//     "kaam",
//     "karo",
//     "rakho",
//     "jab",
//     "tak",
//     "bas",
//     "agar",
//     "to",
//     "warna",
//     "phir",
//     "dekhao",
//     "lo",
//     "chalao",
//     "wapas",
//     "bhaijo",
//     "adad",
//     "khali",
//     "khatam",
//     "ID",
//     "RO",
//     "LESS_THAN",
//     "GREATER_THAN",
//     "EQUAL_TO",
//     "NOT_EQUAL_TO",
//     "LESS_THAN_OR_EQUAL_TO",
//     "GREATER_THAN_OR_EQUAL_TO",
//     "Output",
//     "Input",
//     "Null",
//     "Digit",
//     "string",
//     "koment",
//     "Assignment_OP"

// };

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n token found";
    _lexer.peek(1).Print();
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

void parser::DecreaseIndent()
{
    // program
    // -- D
    this->indent -= 2;
    
}

void parser::PrintAndIncreaseIndent(string s)
{

    string str = "";
    str.append(indent, '-');
    cout << str << s << endl;
    indent += 2;
}

void parser::Program()
{
    PrintAndIncreaseIndent("Program");

    if (_lexer.peek(1).tokenType == TokenType::END_OF_FILE)
    {
        cout << "Program is correct\n";
        cout << this->indent << endl;
        return;
    }
    else if (_lexer.peek(1).tokenType == TokenType::kaam || _lexer.peek(1).tokenType == TokenType::rakho || _lexer.peek(1).tokenType == TokenType::agar ||
             _lexer.peek(1).tokenType == TokenType::jab || _lexer.peek(1).tokenType == TokenType::lo || _lexer.peek(1).tokenType == TokenType::dekhao)
    {
        D();
        DecreaseIndent();
        Program();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).tokenType == TokenType::koment)
    {
        expect(TokenType::koment);
        Program();
        DecreaseIndent();
    }
    else
    {
        cout << "Program is correct---\n";
        return;
    }
}

void parser::D()
{
    PrintAndIncreaseIndent("D");

    if (_lexer.peek(1).tokenType == TokenType::kaam)
    {
        Function();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).tokenType == TokenType::rakho || _lexer.peek(1).tokenType == TokenType::agar ||
             _lexer.peek(1).tokenType == TokenType::jab || _lexer.peek(1).tokenType == TokenType::lo || _lexer.peek(1).tokenType == TokenType::dekhao || _lexer.peek(1).tokenType == TokenType::wapas)
    {
        Code();
        DecreaseIndent();
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
    PrintAndIncreaseIndent("Code");
    if (_lexer.peek(1).tokenType == TokenType::rakho ||
        _lexer.peek(1).tokenType == TokenType::lo ||
        _lexer.peek(1).tokenType == TokenType::dekhao ||
        _lexer.peek(1).tokenType == TokenType::wapas)
    {

        Statement();
        DecreaseIndent();
        Code();
        DecreaseIndent();
    }
    else if (
        _lexer.peek(1).tokenType == TokenType::agar)

    {
        IF();
        DecreaseIndent();
        Code();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).tokenType == TokenType::jab)
    {
        WHILE();
        DecreaseIndent();
        Code();
        DecreaseIndent();
    }
    else
    {
        return;
    }
}

void parser::Statement()
{
    PrintAndIncreaseIndent("Statement");
    Stmt();
    DecreaseIndent();
    expect(TokenType::koment);
}

void parser::Variable()
{
    PrintAndIncreaseIndent("Variable");
    expect(TokenType::rakho);
    expect(TokenType::ID);
    matchAscii('@');
    expect(TokenType::adad);
    R();
    DecreaseIndent();
}

void parser::R()
{
    PrintAndIncreaseIndent("R");
    if (_lexer.peek(1).tokenType == TokenType::Assignment_OP)
    {
        // if we give this a token type
        expect(TokenType::Assignment_OP);
        Val();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).tokenType == TokenType::chalao)
    { // koi function chal raha hai agay
        expect(TokenType::chalao);
        expect(TokenType::ID);
        matchAscii('(');
    }
    else
    {
        return;
    }
}
void parser::Val()
{
    PrintAndIncreaseIndent("Val");
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
    }
    else if (_lexer.peek(1).tokenType == TokenType::Digit)
    {
        expect(TokenType::Digit);
    }
    else if (_lexer.peek(1).tokenType == TokenType::chalao)
    {
        expect(TokenType::chalao);
        expect(TokenType::ID);
        matchAscii('(');
        PLF();
        DecreaseIndent();
        matchAscii(')');
        // cout << "matched chalao ";
    }
    else if (_lexer.peek(2).lexeme[0] == '-' || _lexer.peek(2).lexeme[0] == '+' || _lexer.peek(2).lexeme[0] == '*' || _lexer.peek(2).lexeme[0] == '/' || _lexer.peek(2).lexeme[0] == '%')
    {
        Expression();
        DecreaseIndent();
    }
}
void parser::Stmt()
{
    PrintAndIncreaseIndent("Stmt");
    if (_lexer.peek(1).tokenType == TokenType::rakho)
    {
        parser::Variable();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).tokenType == TokenType::lo)
    {
        parser::Input();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).tokenType == TokenType::dekhao)
    {
        parser::Output();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).tokenType == TokenType::wapas)
    {
        parser::Return();
        // cout << "rast1 \n";
        DecreaseIndent();
    }
    else
    {
        parser::syntax_error();
    }
}

void parser::InputMsg()
{
    PrintAndIncreaseIndent("InputMsg()");
    if (_lexer.peek(1).tokenType == TokenType::Output)
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
    PrintAndIncreaseIndent("Outval");
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

void parser::Moreparams()
{
    PrintAndIncreaseIndent("Moreparams()");

    if (_lexer.peek(1).lexeme[0] == '|')
    {
        matchAscii('|');
        PLF();
        DecreaseIndent();
    }
    else
    {
        return;
    }
}

// Parameter list functions
void parser::PLF()
{
    PrintAndIncreaseIndent("PLF()");
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        Moreparams();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).tokenType == TokenType::Digit)
    {
        expect(TokenType::Digit);
        Moreparams();
        DecreaseIndent();
    }
    else
    {
    }
}

void parser::Input()
{
    PrintAndIncreaseIndent("Input()");
    expect(TokenType::lo);
    InputMsg();
    DecreaseIndent();
    expect(TokenType::Input);
    expect(TokenType::ID);
}
void parser::Output()
{
    PrintAndIncreaseIndent("Output()");
    expect(TokenType::dekhao);
    expect(TokenType::Output);
    Outval();
    DecreaseIndent();
}
void parser::Return()
{
    PrintAndIncreaseIndent("Return()");
    expect(TokenType::wapas);
    expect(TokenType::bhaijo);
    expect(TokenType::Digit);
    // expect(TokenType::koment);
    // cout << "wapis jarhga hu n bhai jo" << endl;
}

void parser::IF()
{
    PrintAndIncreaseIndent("IF()");
    expect(TokenType::agar);
    matchAscii('(');
    Condition();
    DecreaseIndent();
    matchAscii(')');
    expect(TokenType::to);
    expect(TokenType::phir);
    expect(TokenType::karo);
    Koment();
    DecreaseIndent();
    Code();
    DecreaseIndent();
    WG();
    DecreaseIndent();
    WP();
    DecreaseIndent();
    expect(TokenType::bas);
    expect(TokenType::karo);
    Koment();
    DecreaseIndent();
}
// Warna Agar --> else if
void parser::WG()
{
    PrintAndIncreaseIndent("WG()");
    if (_lexer.peek(1).tokenType == TokenType::warna)
    {
        expect(TokenType::warna);
        expect(TokenType::agar);
        Condition();
        DecreaseIndent();
        expect(TokenType::to);
        expect(TokenType::phir);
        expect(TokenType::karo);
        Code();
        DecreaseIndent();
    }
    else
    {
        return;
    }
}

// Warna Phir --> else
void parser::WP()
{
    PrintAndIncreaseIndent("WP()");
    if (_lexer.peek(1).tokenType == TokenType::warna)
    {
        expect(TokenType::warna);
        expect(TokenType::karo);
        Koment();
        DecreaseIndent();
        Code();
        DecreaseIndent();
    }
    else
    {
        return;
    }
}

void parser::WHILE()
{
    cout << "WHILE()\n";
    expect(TokenType::jab);
    expect(TokenType::tak);
    matchAscii('(');
    Condition();
    DecreaseIndent();
    matchAscii(')');
    expect(TokenType::karo);
    Koment();
    DecreaseIndent();
    Code();
    DecreaseIndent();
    expect(TokenType::bas);
    expect(TokenType::karo);
    Koment();
    DecreaseIndent();
}

void parser::Function()
{
    PrintAndIncreaseIndent("Function()");
    expect(TokenType::kaam);
    expect(TokenType::ID);
    matchAscii('@');
    FuncT();
    DecreaseIndent();
    matchAscii('(');
    ParameterList();
    DecreaseIndent();
    matchAscii(')');
    expect(TokenType::karo);
    Koment();
    DecreaseIndent();
    Code();
    DecreaseIndent();

    expect(TokenType::kaam);
    expect(TokenType::khatam);
    Koment();
    DecreaseIndent();
}

void parser::Koment()
{
    PrintAndIncreaseIndent("Koment()");
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
    PrintAndIncreaseIndent("ParameterList()");
    // (  .   )
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        matchAscii('@');
        expect(TokenType::adad);
        MPL();
        DecreaseIndent();
    }
    else
    {
    }
}

void parser::MPL()
{
    PrintAndIncreaseIndent("MPL()");

    if (int(_lexer.peek(1).lexeme[0]) == '|')
    {
        matchAscii('|');
        ParameterList();
        DecreaseIndent();
    }
    else
    {
        return;
    }
}

void parser::FuncT()
{
    // cout << _lexer.peek(1).lexeme << endl;
    PrintAndIncreaseIndent("FuncT()");
    if (_lexer.peek(1).tokenType == TokenType::khali)
    {
        expect(TokenType::khali);

        return;
    }
    else if (_lexer.peek(1).tokenType == TokenType::adad)
    {
        expect(TokenType::adad);
        return;
    }
    else
    {
        parser::syntax_error();
    }
}

void parser::Condition()
{
    PrintAndIncreaseIndent("Condition()");
    Expression();
    DecreaseIndent();
    RO();
    DecreaseIndent();
    Expression();
    DecreaseIndent();
}

void parser::RO()
{
    PrintAndIncreaseIndent("RO()");
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
    PrintAndIncreaseIndent("Expression()");
    if (_lexer.peek(1).lexeme[0] == '-')
    {
        T();
        DecreaseIndent();
        matchAscii('-');
        Expression();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).lexeme[0] == '+')
    {
        T();
        DecreaseIndent();
        matchAscii('+');
        Expression();
        DecreaseIndent();
    }
    else
    {
        T();
        DecreaseIndent();
    }
}

void parser::T()
{
    PrintAndIncreaseIndent("T()");
    if (_lexer.peek(1).lexeme[0] == '%')
    {
        L();
        DecreaseIndent();
        matchAscii('%');
        T();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).lexeme[0] == '/')
    {
        L();
        DecreaseIndent();
        matchAscii('/');
        T();
        DecreaseIndent();
    }
    else if (_lexer.peek(1).lexeme[0] == '*')
    {
        L();
        DecreaseIndent();
        matchAscii('*');
        T();
        DecreaseIndent();
    }
    else
    {
        L();
        DecreaseIndent();
    }
}

void parser::L()
{
    PrintAndIncreaseIndent("L()");
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
        DecreaseIndent();
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
