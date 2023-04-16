#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
#include <unordered_map>

struct mapElement
{
    string id;
    std::string type;
    int address;
};

class parser
{
    lexer _lexer;

public:
    // id, type , address
   // std::unordered_map<std::string, mapElement> symbolTable;
    std::vector<mapElement> symbolTable;
    bool flag = false;
    int indent = 0;
    int ln = 0;
    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
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
    string Condition();
    int WG();
    void WP();
    void Stmt();
    void Input();
    void Output();
    void Return();
    void InputMsg();
    string Outval();
    string Val();
    string Expression();
    string T();
    string F();
    void L();
    void RO();
    void R(string id);
    int PLF(int i);
    void FuncMain();
    string Q(string i);
    void Cascading();
    void DecreaseIndent();
    void PrintAndIncreaseIndent(string s);
    int MPLF(int i);
    void VarType();
    void MarkaziOrNot();
    void ShowSymbolTable();
    string P(string i);
    string chalao();
    string newTemp();
};
#endif
