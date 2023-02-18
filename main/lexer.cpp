#include "lexer.h"
using namespace std;

// for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
    "END_OF_FILE"};
token::token()
{
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}
token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}
void token::Print()
{
    cout << "{" << lexeme << " , "
         << reserved[(int)tokenType] << "}\n";
}

int lexer::getCurrentPointer()
{
    return index;
}
void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}

TokenType checkIfKeyword(string lex) {

    // check if TokenType contains lex 
    if (lex == "markazi") return TokenType::markazi;
    if (lex == "kaam") return TokenType::kaam;
    if (lex == "karo") return TokenType::karo;
    if (lex == "rakho") return TokenType::rakho;
    if (lex == "jab") return TokenType::jab;
    if (lex == "tak") return TokenType::tak;
    if (lex == "bas") return TokenType::bas;
    if (lex == "agar") return TokenType::agar;
    if (lex == "to") return TokenType::to;
    if (lex == "warna") return TokenType::warna;
    if (lex == "phir") return TokenType::phir;
    if (lex == "dekhao") return TokenType::dekhao;
    if (lex == "lo") return TokenType::lo;
    if (lex == "chalao") return TokenType::chalao;
    if (lex == "wapas") return TokenType::wapas;
    if (lex == "bhaijo") return TokenType::bhaijo;
    if (lex == "adad") return TokenType::adad;
    if (lex == "khali") return TokenType::khali;
    if (lex == "khatam") return TokenType::khatam;

    return TokenType::ID;
    


}

void lexer::Tokenize() // function that tokenizes your input stream
{
    vector<char>::iterator it = stream.begin();
    // initial  *it
    int state = 0;
    int finalState = 50;

    std::string currentLexeme = "";
    // Main loop for tokenization
    for (it = stream.begin(); it != stream.end(); it++)
    {
        switch (state)
        {
        // start state
        case 0:
            // transition to Identifier DFA
            if (isalpha(*it) || (*it) == '_')
            {
                state = 1;
                currentLexeme.push_back(*it);
            }
            // check for digit
            else if (isdigit(*it))
            {
                state = 2;
                currentLexeme.push_back(*it);
            }
            // Transition to string
            else if ((*it) == '`')
            {
                state = 3;
                currentLexeme.push_back(*it);
            }
            // Transition to comment
            else if ((*it) == ';')
            {
                state = 4;
                currentLexeme.push_back(*it);
            }
            // Transition to less than operator DFA
            else if ((*it) == '<')
            {
                state = 5;
                currentLexeme.push_back(*it);
            }
            // Transition to greater than operator DFA
            else if ((*it) == '>')
            {
                state = 6;
                currentLexeme.push_back(*it);
            }
            // Transition to equal to operator DFA
            else if ((*it) == '=')
            {
                state = 0;
                tokens.push_back(token(currentLexeme, TokenType::EQUAL_TO));
            }

            else if ((*it) == ' ' || (*it) == '\t' || (*it) == '\n' || (*it) == '\r')
            {
                // ignore whitespace
                state = 0;
            }
            // for arithmetic operators
            else if ((*it) == '+' || (*it) == '-' || (*it) == '*' || (*it) == '/' || (*it) == '%')
            {
                currentLexeme.push_back(*it);
                tokens.push_back(token(currentLexeme, TokenType::Null));
                state = 0;
                currentLexeme = "";
            }
            
            // Excluding semi-colon and back tick as they have already been catered
            // for special characters
            else if ((*it) == '(' || (*it) == ')' ||  (*it) == '|' || (*it) == '@' )
            {
                currentLexeme.push_back(*it);
                tokens.push_back(token(currentLexeme, TokenType::Null));
                state = 0;
                currentLexeme = "";
            }

            else if ( (*it) == ':'){
                state = 7;
                currentLexeme.push_back(*it);
            }

            break;
        case 1:
            cout << "state 1";
            if (isalpha(*it) || (*it) == '_' || isdigit(*it))
            {
                state = 1;
                currentLexeme.push_back(*it);
            }
            else
            {
              
                // anything other than alphabet, digit or underscore

                // we have to check if its a reserved word
                if ( checkIfKeyword(currentLexeme) != TokenType::ID)
                    // add a safety check for null 
                    tokens.push_back(token("", checkIfKeyword(currentLexeme)));
                else
                    tokens.push_back(token(currentLexeme, TokenType::ID));
                
                state = 0;
                currentLexeme = "";
            }
            break;
        case 2:
            cout << "state 2";

            if (isdigit(*it))
            {
                state = 2;
                currentLexeme.push_back(*it);
            }
            else
            {
                tokens.push_back(token(currentLexeme, TokenType::adad));
                state = 0;
                currentLexeme = "";
            }

            break;

        case 3:
            cout << "state 3";

            if ((*it) == '`')
            { //  TODO: check for double back tick
                tokens.push_back(token(currentLexeme, TokenType::markazi));
                state = 0;
                currentLexeme = "";
            }
            else
            {
                currentLexeme.push_back(*it);
                state = 3;
            }
            break;

        case 4:
            cout << "state 4";

            if ((*it) == '\n')
            {
                state = 0;
                currentLexeme = "";
            }
            else
            {
                currentLexeme.push_back(*it);
                state = 4;
            }
            break;

        case 5:
            cout << "state 5 (RO, LE)";

            if ((*it) == '=')
            {
                // Do some change here
                currentLexeme.push_back(*it);
                tokens.push_back(token(currentLexeme, TokenType::LESS_THAN_OR_EQUAL_TO));
                state = 0;
                currentLexeme = "";
            }
            else if ((*it) == '>')
            {
                currentLexeme.push_back(*it);
                tokens.push_back(token(currentLexeme, TokenType::NOT_EQUAL_TO));
                state = 0;
                currentLexeme = "";
            }

            else if ((*it) == '<')
            {
                currentLexeme.push_back(*it);
                tokens.push_back(token(currentLexeme, TokenType::Output));
                state = 0;
                currentLexeme = "";
            }
            else
            {
                tokens.push_back(token(currentLexeme, TokenType::LESS_THAN));
                state = 0;
                currentLexeme = "";
            }
            break;

        case 6:
            cout << "state 6 (RO, GE)";

            if ((*it) == '=')
            {
                currentLexeme.push_back(*it);
                tokens.push_back(token(currentLexeme, TokenType::GREATER_THAN_OR_EQUAL_TO));
                state = 0;
                currentLexeme = "";
            }

            else if ((*it) == '>')
            {
                currentLexeme.push_back(*it);
                tokens.push_back(token(currentLexeme, TokenType::Input));
                state = 0;
                currentLexeme = "";
            }

            else
            {
                tokens.push_back(token(currentLexeme, TokenType::GREATER_THAN));
                state = 0;
                currentLexeme = "";
            }
            break;
        
        case 7:

            if ( (*it)=='=')
            {
                currentLexeme.push_back(*it);
                tokens.push_back(token(currentLexeme, TokenType::Null));
                state = 0;
                currentLexeme = "";
            }
            else
            {
                tokens.push_back(token(currentLexeme, TokenType::Null));
                state = 0;
                currentLexeme = "";
            }

    

        }
    }

    // push_back EOF token at end to identify End of File
    tokens.push_back(token(string(""), TokenType::END_OF_FILE));
}
lexer::lexer(const char filename[])
{
    // constructors: takes file name as an argument and store all
    // the contents of file into the class varible stream
    ifstream fin(filename);
    if (!fin) // if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { // store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back(' '); // dummy spaces appended at the end
        stream.push_back(' ');
        // Tokenize function to get all the (token,lexeme) pairs
        Tokenize();
        // assigning tokens to iterator::pointer
        index = 0;
    }
}

lexer::lexer()
{
    index = -1;
}

void lexer::printRaw()
{
    // helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}

token lexer::getNextToken()
{
    // this function will return single (token,lexeme) pair on each call
    // this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}

void lexer::resetPointer()
{
    index = 0;
}

token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                             // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}