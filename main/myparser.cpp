#include "myparser.h"

int Variable_Count = 0;
int address = 0;
int lineNumber = 0;
string emitLine = "";
vector<string> lines;

namespace constants
{
    const string TAC = "TAC.txt";
    const string SYMBOL_TABLE = "symbol_table.txt";
}

// TODO : Seperate this to another file for better readability
// Generic template function for writing to a file
template <typename T>
void writeToFile(const std::vector<T>& data, const std::string& filename);

// Template specialization for mapElement
template <>
void writeToFile<mapElement>(const std::vector<mapElement>& data, const std::string& filename) {
    std::ofstream outfile(filename);

    if (outfile.is_open()) {
        for (const auto& element : data) {
            outfile << element.id << " " << element.type << " " << element.address << std::endl;
        }
        outfile.close();
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}

// Template specialization for string
template <>
void writeToFile<std::string>(const std::vector<std::string>& data, const std::string& filename) {
    std::ofstream outfile(filename);

    if (outfile.is_open()) {
        for (const auto& element : data) {
            outfile << element ;
        }
        outfile.close();
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}






void Backpatch(int ReferenceLine)

{
    if (ReferenceLine < 0)
        return;
    string LinePatch = to_string(lineNumber);
    string Patch = lines[ReferenceLine];
    Patch = Patch.substr(0, Patch.size() - 1) + " " + LinePatch + " \n";
    lines[ReferenceLine] = Patch;
}
string parser::newTemp()
{
    string varName = "t" + to_string(Variable_Count);
    Variable_Count++;
    mapElement m = {varName, "INT", address};
    address += 4;
    symbolTable.push_back(m);
    return varName;
}

string testreserved[] = {
    "END_OF_FILE",
    "ERROR",
    "markazi",
    "kaam",
    "karo",
    "rakho",
    "jab",
    "tak",
    "bas",
    "agar",
    "to",
    "warna",
    "phir",
    "dekhao",
    "lo",
    "chalao",
    "wapas",
    "bhaijo",
    "adad",
    "khali",
    "khatam",
    "ID",
    "RO",
    "LESS_THAN",
    "GREATER_THAN",
    "EQUAL_TO",
    "NOT_EQUAL_TO",
    "LESS_THAN_OR_EQUAL_TO",
    "GREATER_THAN_OR_EQUAL_TO",
    "Output",
    "Input",
    "Null",
    "Digit",
    "string",
    "koment",
    "Assignment_OP"

};

void emit(const string filename, const string &text)
{
    // ofstream file(filename, ios_base::app);
    // file << lineNumber << ". " <<  text << "\n";

    // I have done this to optimize the backPatch

    string string_to_emit = to_string(lineNumber) + ". " + text + "\n";
    lines.push_back(string_to_emit);
    lineNumber++;
}

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n token expected";
    _lexer.peek(1).Print();
    exit(1);
}

// match function
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type)
    {
        cout << "Expected :" << testreserved[(int)expected_type] << "\n"
             << "Got ";
        t.Print();
        syntax_error();
    }
    PrintAndIncreaseIndent(testreserved[(int)expected_type]);
    DecreaseIndent();

    return t;
}
parser::parser(const char filename[])
{
    _lexer = lexer(filename);
    // Deleting the TAC file if it exists so that it can be created again
    remove(constants::TAC.c_str());
    remove(constants::SYMBOL_TABLE.c_str());
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
    if (indent == 0)
        return;
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
        // expect(TokenType::END_OF_FILE);
        cout << "Program is correct now\n";
        parser::resetPointer();
        return;
    }
    else if (_lexer.peek(1).tokenType == TokenType::kaam || _lexer.peek(1).tokenType == TokenType::rakho || _lexer.peek(1).tokenType == TokenType::agar ||
             _lexer.peek(1).tokenType == TokenType::jab || _lexer.peek(1).tokenType == TokenType::lo || _lexer.peek(1).tokenType == TokenType::dekhao)
    {
        D();
        DecreaseIndent();
        if (_lexer.peek(1).tokenType == TokenType::END_OF_FILE)
        {
            // expect(TokenType::END_OF_FILE);
            cout << "Program is correct now\n";
            parser::resetPointer();
            return;
        }
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
        // cout << "here";
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

void parser::VarType()
{
    PrintAndIncreaseIndent("VarType");

    if (_lexer.peek(1).lexeme[0] == '@')
    {

        matchAscii('@');
        expect(TokenType::adad);
    }
    else
    {
        return;
    }
}

void parser::Variable()
{
    PrintAndIncreaseIndent("Variable");

    expect(TokenType::rakho);
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        std::string varName = _lexer.peek(1).lexeme;
        mapElement m = {varName, "INT", address};
        address += 4;
        symbolTable.push_back(m);
    }
    string id = _lexer.peek(1).lexeme;
    // cout << "id is " << id << endl;
    expect(TokenType::ID);
    VarType();
    DecreaseIndent();

    R(id); // * { R.id = Id.lex }
    DecreaseIndent();
}

void parser::R(string id)
{
    PrintAndIncreaseIndent("R");
    if (_lexer.peek(1).tokenType == TokenType::Assignment_OP)
    {
        // if we give this a token type
        expect(TokenType::Assignment_OP);

        string Val_v = Val();
        // *     { emit(R.id+”=”+ Val.v);
        // *     R.v =SymbolTable.add(R.id, INT);  }
        emitLine = id + " = " + Val_v;
        emit(constants::TAC, emitLine);
        DecreaseIndent();
    }
    else
    {
        // symbol table mei add karna hai

        return;
    }
}

string parser::Val()
{
    PrintAndIncreaseIndent("Val");
    if (_lexer.peek(2).lexeme[0] == '-' || _lexer.peek(2).lexeme[0] == '+' || _lexer.peek(2).lexeme[0] == '*' || _lexer.peek(2).lexeme[0] == '/' || _lexer.peek(2).lexeme[0] == '%')
    {
        string Val_v = Expression(); // * { Val.v = Expression.v }

        DecreaseIndent();
        return Val_v;
    }
    else if (_lexer.peek(1).tokenType == TokenType::Digit)
    {
        string Val_v = _lexer.peek(1).lexeme; // * { Val.v = Digit.v }
        expect(TokenType::Digit);
        return Val_v;
    }
    else if (_lexer.peek(1).tokenType == TokenType::chalao)
    {
        PrintAndIncreaseIndent("chalao");

        string Val_v = parser::chalao();
        DecreaseIndent();
        return Val_v; // * { Val.v = Chalao.v }
    }
    else if ((_lexer.peek(1).tokenType == TokenType::ID))
    {
        string Val_v = _lexer.peek(1).lexeme; // * { Val.v = Digit.v }
        expect(TokenType::ID);
        return Val_v;
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

string parser::chalao()
{

    expect(TokenType::chalao);
    string ID = _lexer.peek(1).lexeme;
    expect(TokenType::ID);
    matchAscii('(');
    int PLF_i = 0; // *  {   PLF.i=0;   }
    int PLF_v = PLF(PLF_i);
    string var = parser::newTemp();
    emitLine = "call " + ID + " " + to_string(PLF_v) + "," + var;
    emit(constants::TAC, emitLine); // *{ PLF.i=0; }
    DecreaseIndent();
    matchAscii(')');
    return var;
}

// Parameter list functions
int parser::PLF(int i)
{
    PrintAndIncreaseIndent("PLF()");
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        string id = _lexer.peek(1).lexeme;
        expect(TokenType::ID);
        emit(constants::TAC, "param " + id);
        int PLF_i = i + 1;
        int Plf_v = MPLF(PLF_i);
        DecreaseIndent();
        return Plf_v;
    }
    else if (_lexer.peek(1).tokenType == TokenType::Digit)
    {
        string id = _lexer.peek(1).lexeme;
        expect(TokenType::Digit);
        emit(constants::TAC, "param " + id);
        int PLF_i = i + 1;
        int Plf_v = MPLF(PLF_i);
        DecreaseIndent();
        return Plf_v;
    }
    else
    {
        return i; // *  {PLF.v = PLf.i}
    }
}

int parser::MPLF(int i)
{
    PrintAndIncreaseIndent("MPLF()");

    if (_lexer.peek(1).lexeme[0] == '|')
    {
        matchAscii('|');
        int PLF_i = i;
        int PLF_v = PLF(PLF_i);
        DecreaseIndent();
        return PLF_v;
    }
    else
    {
        return i; // *  {MPLF.v = PLF.v}
    }
}

void parser::ShowSymbolTable()
{

    cout << "-----Symbol table ----- \n";
    // cout << "ID"
    //      << " "
    //      << "TYPE"
    //      << " "
    //      << "ADDRESS";
    // for (auto x : this->symbolTable)
    // {
    //     cout << x.id << " " << x.type << " " << x.address << endl;
    // }
    return;
}

void parser::Return()
{
    PrintAndIncreaseIndent("Return()");
    expect(TokenType::wapas);
    expect(TokenType::bhaijo);
    string ID = _lexer.peek(1).lexeme;
    expect(TokenType::Digit);
    emit(constants::TAC, "ret " + ID);
    // expect(TokenType::koment);
    // cout << "wapis jarhga hu n bhai jo" << endl;
}

void parser::IF()
{
    PrintAndIncreaseIndent("IF()");
    expect(TokenType::agar);
    matchAscii('(');
    // string Condition_v = Condition();
    string cond = Condition();
    DecreaseIndent();
    matchAscii(')');
    expect(TokenType::to);
    expect(TokenType::phir);
    expect(TokenType::karo);

    int lnTrue = lineNumber;
    emit(constants::TAC, "if " + cond + " goto");
    int lnFalse = lineNumber;
    emit(constants::TAC, "goto");
    Backpatch(lnTrue);
    Koment();
    DecreaseIndent();
    Code();
    int IF_end = lineNumber;
    emit(constants::TAC, "goto");
    Backpatch(lnFalse);
    DecreaseIndent();
    int WG_val = WG();
    DecreaseIndent();
    WP();
    DecreaseIndent();
    expect(TokenType::bas);
    expect(TokenType::karo);

    Backpatch(IF_end);
    Backpatch(WG_val);
    Koment();
    DecreaseIndent();
}
// Warna Agar --> else if
int parser::WG()
{
    PrintAndIncreaseIndent("WG()");
    if (_lexer.peek(1).tokenType == TokenType::warna)
    {
        expect(TokenType::warna);
        expect(TokenType::agar);
        matchAscii('(');
        string cond = Condition();
        DecreaseIndent();
        matchAscii(')');
        expect(TokenType::to);
        expect(TokenType::phir);
        Koment();
        int lnTrue = lineNumber;
        emit(constants::TAC, "if " + cond + " goto");
        int lnFalse = lineNumber;
        emit(constants::TAC, "goto ");
        Backpatch(lnTrue);
        Code();
        int Wg_v = lineNumber;
        emit(constants::TAC, "goto ");
        Backpatch(lnFalse);

        DecreaseIndent();
        return Wg_v;
    }
    else
    {
        return -1;
    }
}

// Warna Phir --> else
void parser::WP()
{
    PrintAndIncreaseIndent("WP()");
    if (_lexer.peek(1).tokenType == TokenType::warna)
    {
        expect(TokenType::warna);
        expect(TokenType::phir);
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
    PrintAndIncreaseIndent("Jab Tak()");
    expect(TokenType::jab);
    expect(TokenType::tak);
    matchAscii('(');
    string cond = Condition();

    DecreaseIndent();
    matchAscii(')');
    expect(TokenType::karo);
    Koment();
    DecreaseIndent();

    int lnTrue = lineNumber;
    emit(constants::TAC, "if " + cond + " goto");
    int lnFalse = lineNumber;
    emit(constants::TAC, "goto ");
    Backpatch(lnTrue);
    Code();
    emit(constants::TAC, "goto " + to_string(lnTrue));
    DecreaseIndent();
    expect(TokenType::bas);
    expect(TokenType::karo);
    Backpatch(lnFalse);
    Koment();
    DecreaseIndent();
}

void parser::MarkaziOrNot()
{
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        cout << "Normal function" << endl;
        std::string FuncName = _lexer.peek(1).lexeme;
        mapElement m = {FuncName, "FUNC", lineNumber};
        symbolTable.push_back(m);
        expect(TokenType::ID);
    }
    else if (_lexer.peek(1).tokenType == TokenType::markazi)
    {
        cout<< "Markazi function" << endl;
        expect(TokenType::markazi);
        mapElement m = {"Markazi", "FUNC", lineNumber};
        symbolTable.push_back(m);
    }
    else
    {
        syntax_error();
    }
}

void parser::Function()
{
    PrintAndIncreaseIndent("Function()");
    expect(TokenType::kaam);
    MarkaziOrNot();
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

void parser::Input()
{
    PrintAndIncreaseIndent("Input()");
    expect(TokenType::lo);
    InputMsg();
    DecreaseIndent();
    //{ emit(“in”+ID.v+”\n”) }
    expect(TokenType::Input);
    string inputID = _lexer.peek(1).lexeme;
    expect(TokenType::ID);
    string EmitLine = "in " + inputID;
    emit(constants::TAC, EmitLine);
}

void parser::InputMsg()
{
    PrintAndIncreaseIndent("InputMsg()");
    if (_lexer.peek(1).tokenType == TokenType::Output)
    {
        expect(TokenType::Output);
        string inputstr = _lexer.peek(1).lexeme;
        expect(TokenType::string);
        //{ emit (“out” +String .v +”\n”) }
        string EmitLine = "out " + inputstr;
        emit(constants::TAC, EmitLine);
    }
    else
    {
        return;
    }
}

void parser::Output()
{
    PrintAndIncreaseIndent("Output()");
    //  dekhao << x << ` `;
    if (_lexer.peek(1).tokenType == TokenType::dekhao)
    {
        expect(TokenType::dekhao);
        expect(TokenType::Output);
        string outval = Outval();
        // { emit (“out” + OutVal.v +”\n” ) }
        string EmitLine = "out " + outval;
        emit(constants::TAC, EmitLine);
        DecreaseIndent();
        Cascading();
        DecreaseIndent();
    }
    {
        return;
    }
}

void parser::Cascading()
{
    PrintAndIncreaseIndent("Cascading()");
    if (_lexer.peek(1).tokenType == TokenType::Output)
    {
        expect(TokenType::Output);
        string outval = Outval();
        // { emit (“out” + OutVal.v +”\n” ) }
        string EmitLine = "out " + outval;
        emit(constants::TAC, EmitLine);
        DecreaseIndent();
        Cascading();
        DecreaseIndent();
    }
    else
    {
        return;
    }
}

string parser::Outval()
{
    PrintAndIncreaseIndent("Outval");
    if (_lexer.peek(1).tokenType == TokenType::string)
    {
        string outstr = _lexer.peek(1).lexeme;
        expect(TokenType::string);
        return outstr;
    }
    else if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        string outid = _lexer.peek(1).lexeme;
        expect(TokenType::ID);
        return outid;
    }
    else if (_lexer.peek(1).tokenType == TokenType::Digit)
    {
        string outdigit = _lexer.peek(1).lexeme;
        expect(TokenType::Digit);
        return outdigit;
    }
    else
    {
        syntax_error();
    }
}

string parser::Condition()
{
    PrintAndIncreaseIndent("Condition()");
    string val1 = Expression();
    DecreaseIndent();
    string RO_ = _lexer.peek(1).lexeme;
    RO();
    DecreaseIndent();
    string val2 = Expression();
    DecreaseIndent();
    return val1 + " " + RO_ + " " + val2;
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

string parser::Expression()
{
    PrintAndIncreaseIndent("Expression()");
    string T_v = T();
    string E_v = P(T_v);
    return E_v;
}

string parser::P(string i)
{

    PrintAndIncreaseIndent("P()");
    if (_lexer.peek(1).lexeme[0] == '+')
    {
        matchAscii('+');
        string T_v = T();
        string var = newTemp();
        emit(constants::TAC, var + "=" + i + "+" + T_v);
        string P1_s = P(var);
        return P1_s;
    }
    else if (_lexer.peek(1).lexeme[0] == '-')
    {
        matchAscii('-');
        string T_v = T();
        string var = newTemp();
        emit(constants::TAC, var + "=" + i + "-" + T_v);
        string P1_s = P(var);
        return P1_s;
    }

    else
    {
        return i;
    }
}

string parser::T()
{
    PrintAndIncreaseIndent("T()");
    string F_v = F();
    string T_v = Q(F_v);
    return T_v;
}

string parser::Q(string i)
{

    PrintAndIncreaseIndent("Q()");
    if (_lexer.peek(1).lexeme[0] == '*')
    {
        matchAscii('*');
        string F_v = F();
        string var = newTemp();
        emit(constants::TAC, var + "=" + i + "*" + F_v);
        string Q1_s = Q(var);
        return Q1_s;
    }
    else if (_lexer.peek(1).lexeme[0] == '/')
    {
        matchAscii('/');
        string F_v = F();
        string var = newTemp();
        emit(constants::TAC, var + "=" + i + "/" + F_v);
        string Q1_s = Q(var);
        return Q1_s;
    }
    else if (_lexer.peek(1).lexeme[0] == '%')
    {
        matchAscii('-');
        string F_v = F();
        string var = newTemp();
        emit(constants::TAC, var + "=" + i + "%" + F_v);
        string Q1_s = Q(var);
        return Q1_s;
    }

    else
    {
        return i;
    }
}

string parser::F()
{
    PrintAndIncreaseIndent("F()");
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        cout << "here \n";
        string F_v = _lexer.peek(1).lexeme;
        expect(TokenType::ID);
        return F_v;
    }
    else if (_lexer.peek(1).tokenType == TokenType::Digit)
    {
        string F_v = _lexer.peek(1).lexeme;
        expect(TokenType::Digit);
        return F_v;
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
        PrintAndIncreaseIndent(t.lexeme);
        DecreaseIndent();
        return;
    }
    else
    {
        parser::syntax_error();
    }
}

void parser::parse()
{
    parser::Program();
    for (const auto &str : lines)
    {
        std::cout << str << " ";
    }
    writeToFile(lines, constants::TAC);
    writeToFile(symbolTable, constants::SYMBOL_TABLE);
}
