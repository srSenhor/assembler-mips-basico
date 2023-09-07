#include <string>
#include <cctype>
using namespace std;

struct RInstruction
{
	char opcode, rs, rt, rd, sa, funct;
	bool isInst = false;
};

struct IInstruction
{
	char opcode, rs, rt;
	int addcons;
	bool isInst = false;
};

struct JInstruction
{
	char opcode;
	int address;
	bool isInst = false;
};

struct symb
{
	string labelNome;
	int address = 0, linha = 0;
};

int translateInstruction(string&, ifstream&, symb[], const int, const int);
int codigoReg(string&);
int immediateBranch(symb[], int, string, int);
int toBinary(RInstruction&);
int toBinary(IInstruction&);
int toBinary(JInstruction&);
char* IntegerToBinary(int);
string regString(ifstream&);
//Criar uma função pra ler os registradores mesmo que estejam juntos e separados apenas por virgula