#include <iostream>
#include "myparser.h"
#include <string>
#include <sstream>
using namespace std;

vector<string> exec;

enum class opCodes
{
	Assign = 600,
	outS = 601,
	outV = 6011,
	ret = 602,
	equalTo = 603,
	lessThan = 604,
	greaterThan = 605,
	lessthanEqualTo = 606,
	greaterThanEqualTo = 607,
	notEqualTo = 608,
	goto_ = 609,
	plus = 610,
	minus = 611,
	divide = 612,
	multiply = 613,
	mod = 614,
	in = 615,
	end = 616
};

int getOpcode(string opcode)
{
	if (opcode == "Assign")
	{
		opCodes code = opCodes::Assign;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "outS")
	{
		opCodes code = opCodes::outS;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "outV")
	{
		opCodes code = opCodes::outV;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "ret")
	{
		opCodes code = opCodes::ret;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == ">")
	{
		opCodes code = opCodes::greaterThan;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "end")
	{
		opCodes code = opCodes::end;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "<")
	{
		opCodes code = opCodes::lessThan;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "<=")
	{
		opCodes code = opCodes::lessthanEqualTo;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == ">=")
	{
		opCodes code = opCodes::greaterThanEqualTo;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "<>")
	{
		opCodes code = opCodes::notEqualTo;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "=")
	{
		opCodes code = opCodes::equalTo;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "in")
	{
		opCodes code = opCodes::in;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "goto")
	{
		opCodes code = opCodes::goto_;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "+")
	{
		opCodes code = opCodes::plus;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "-")
	{
		opCodes code = opCodes::minus;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "*")
	{
		opCodes code = opCodes::multiply;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "/")
	{
		opCodes code = opCodes::divide;
		int retVal = static_cast<int>(code);
		return retVal;
	}
	else if (opcode == "%")
	{
		opCodes code = opCodes::mod;
		int retVal = static_cast<int>(code);
		return retVal;
	}
}

int *loadDataSegment(std::vector<mapElement> symbolTable)
{
	cout << "Loading segment " << endl;
	// if symbol table is empty return
	if (symbolTable.size() == 0)
	{
		return nullptr;
	}
	int *dataSegment = new int[symbolTable.size() - 1];
	int dataSegmentSize = symbolTable.size() - 1;
	for (int i = 1; i < symbolTable.size(); i++)
	{
		dataSegment[i - 1] = stoi(symbolTable[i].initVal);
		//cout << symbolTable[i].initVal << " " << endl;
	}

	// print data segment
	cout << " Printing data segment " << endl;
	for (int i = 0; i < dataSegmentSize; i++)
	{
		cout << dataSegment[i] << " ";
	}
	cout << " data segment end " << endl;

	return dataSegment;
}

std::vector<std::string> tokenizeString(const std::string &str)
{
	std::vector<std::string> tokens;
	std::istringstream iss(str);
	std::string token;

	while (iss >> token)
	{
		tokens.push_back(token);
	}

	return tokens;
}

void VM(string filename, std::vector<mapElement> symbolTable)
{

	ifstream fin(filename);
	if (!fin)
	{
		cout << "Cannot open the File : " << filename << endl;
	}
	string line;
	while (std::getline(fin, line))
	{
		exec.push_back(line);
	}
	std::vector<std::string> tokens;
	// load values in an int array from symbol table
	auto dataSegment = loadDataSegment(symbolTable);

	cout << "-----Starting execution----" << std::endl;
	int i = 0;
	for (i; i < exec.size(); i++)
	{
		string opcode = exec[i].substr(0, exec[i].find(' '));
		int opcode_int = getOpcode(opcode);
		switch (opcode_int)
		{
		case 600: // Assign
		{
			tokens = tokenizeString(exec[i]);
			int value = stoi(tokens[1]);
			int index = stoi(tokens[2]);
			dataSegment[index / 4] = dataSegment[value / 4];

			break;
		}
		case 601: // output string
		{
			tokens = tokenizeString(exec[i]);
			for (int i = 1; i < tokens.size(); i++)
			{
				cout << tokens[i] << " ";
			}
			cout << endl;
			break;
		}
		case 6011: // out val
		{
			tokens = tokenizeString(exec[i]);
			int addr = stoi(tokens[1]);
			cout << dataSegment[addr / 4] << std::endl;
			break;
		}
		case 602: // ret
		{
			tokens = tokenizeString(exec[i]);
			exit(0);
			break;
		}
		case 603: // equalTo
		{
			tokens = tokenizeString(exec[i]);

			break;
		}
		case 604: // lessThan
		{
			tokens = tokenizeString(exec[i]);
			int index1 = stoi(tokens[1]);
			int index2 = stoi(tokens[2]);
			int index3 = stoi(tokens[3]);
			if (dataSegment[index1 / 4] < dataSegment[index2 / 4])
			{
				i = index3 - 2;
			}
			break;
		}
		case 605: // greaterThan
		{

			tokens = tokenizeString(exec[i]);
			int index1 = stoi(tokens[1]);
			int index2 = stoi(tokens[2]);
			int index3 = stoi(tokens[3]);
			if (dataSegment[index1 / 4] > dataSegment[index2 / 4])
			{
				i = index3 - 2;
			}
			break;
		}
		case 606: // lessthanEqualTo
		{

			tokens = tokenizeString(exec[i]);
			int index1 = stoi(tokens[1]);
			int index2 = stoi(tokens[2]);
			int index3 = stoi(tokens[3]);
			if (dataSegment[index1 / 4] <= dataSegment[index2 / 4])
			{
				i = index3 - 2;
			}
			break;
		}
		case 607: // greaterThanEqualTo
		{
			tokens = tokenizeString(exec[i]);
			int index1 = stoi(tokens[1]);
			int index2 = stoi(tokens[2]);
			int index3 = stoi(tokens[3]);
			if (dataSegment[index1 / 4] >= dataSegment[index2 / 4])
			{
				i = index3 - 2;
			}
			break;
		}
		case 608: // notEqualTo
		{

			tokens = tokenizeString(exec[i]);
			int index1 = stoi(tokens[1]);
			int index2 = stoi(tokens[2]);
			int index3 = stoi(tokens[3]);
			if (dataSegment[index1 / 4] != dataSegment[index2 / 4])
			{
				i = index3 - 2;
			}
			break;
		}
		case 609: // goto_
		{
			tokens = tokenizeString(exec[i]);
			int index = stoi(tokens[1]);
			i = index - 2;

			break;
		}
		case 610: // plus
			// cout << exec[i] << std::endl;
			{
				tokens = tokenizeString(exec[i]);
				int index1 = stoi(tokens[1]);
				int index2 = stoi(tokens[2]);
				int index3 = stoi(tokens[3]);
				dataSegment[index3 / 4] = dataSegment[index1 / 4] + dataSegment[index2 / 4];
				break;
			}
		case 611: // minus
		{
			tokens = tokenizeString(exec[i]);
			int index1 = stoi(tokens[1]);
			int index2 = stoi(tokens[2]);
			int index3 = stoi(tokens[3]);
			dataSegment[index3 / 4] = dataSegment[index1 / 4] - dataSegment[index2 / 4];

			break;
		}
		case 612: // divide
		{
			tokens = tokenizeString(exec[i]);
			int index1 = stoi(tokens[1]);
			int index2 = stoi(tokens[2]);
			int index3 = stoi(tokens[3]);
			dataSegment[index3 / 4] = dataSegment[index1 / 4] / dataSegment[index2 / 4];

			break;
		}
		case 613: // multiply
		{
			tokens = tokenizeString(exec[i]);
			int index1 = stoi(tokens[1]);
			int index2 = stoi(tokens[2]);
			int index3 = stoi(tokens[3]);
			dataSegment[index3 / 4] = dataSegment[index1 / 4] * dataSegment[index2 / 4];

			break;
		}
		case 614: // mod
		{
			tokens = tokenizeString(exec[i]);
			int index1 = stoi(tokens[1]);
			int index2 = stoi(tokens[2]);
			int index3 = stoi(tokens[3]);
			dataSegment[index3 / 4] = dataSegment[index1 / 4] % dataSegment[index2 / 4];

			break;
		}
		case 615: // in
		{
			tokens = tokenizeString(exec[i]);
			int index = stoi(tokens[1]);
			int value;
			cin >> value;
			dataSegment[index / 4] = value;

			break;
		}
		case 616: // end
		{
			tokens = tokenizeString(exec[i]);
			exit(0);
			break;
		}
		}
	}

	fin.close();
}

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
		std::vector<mapElement> symbolTable = _parser.symbolTable;
		VM("TAC.txt", symbolTable);

		// string test ="-";
		// int t3 = getOpcode(test);
		// std::cout << t3 << std::endl;
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
