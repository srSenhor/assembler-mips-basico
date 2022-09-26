#include <fstream>
#include <iostream>
#include "trsltMIPS.h"

int translateInstruction(string& termo, ifstream& fin, symb symbTab[], const int tamSymbTab, const int linhaAtual)
{

	RInstruction r{};	//Instrução do tipo R
	IInstruction i{};	//Instrução do tipo I
	JInstruction j{};	//Instrução do tipo J

	//Faremos uma série de verificações para o termo apontado...
	//Instruction R --------------------------------------------------------------------
	if (!strcmp(termo.c_str(), "sll"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		fin >> termo;
		r.sa = stoi(termo, nullptr, 10);
		r.funct = 0;
	}
	else if (!strcmp(termo.c_str(), "sll"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		fin >> termo;
		r.sa = stoi(termo, nullptr, 10);
		r.funct = 2;
	}
	else if (!strcmp(termo.c_str(), "jr"))
	{
		r.isInst = true;
		fin >> termo;
		r.rs = codigoReg(termo);
		r.funct = 8;
	}
	else if (!strcmp(termo.c_str(), "mfhi"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		r.funct = 16;
	}
	else if (!strcmp(termo.c_str(), "mflo"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		r.funct = 18;
	}
	else if (!strcmp(termo.c_str(), "mult"))
	{
		r.isInst = true;
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 24;
	}
	else if (!strcmp(termo.c_str(), "multu"))
	{
		r.isInst = true;
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 25;
	}
	else if (!strcmp(termo.c_str(), "div"))
	{
		r.isInst = true;
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 26;
	}
	else if (!strcmp(termo.c_str(), "divu"))
	{
		r.isInst = true;
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 27;
	}
	else if (!strcmp(termo.c_str(), "add"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 32;
	}
	else if (!strcmp(termo.c_str(), "addu"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 33;
	}
	else if (!strcmp(termo.c_str(), "sub"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 34;
	}
	else if (!strcmp(termo.c_str(), "subu"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 35;
	}
	else if (!strcmp(termo.c_str(), "and"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 36;
	}
	else if (!strcmp(termo.c_str(), "or"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 37;
	}
	else if (!strcmp(termo.c_str(), "slt"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 42;
	}
	else if (!strcmp(termo.c_str(), "sltu"))
	{
		r.isInst = true;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 43;
	}
	else if (!strcmp(termo.c_str(), "mul"))
	{
		r.isInst = true;
		r.opcode = 28;
		fin >> termo;
		r.rd = codigoReg(termo);
		fin >> termo;
		r.rs = codigoReg(termo);
		fin >> termo;
		r.rt = codigoReg(termo);
		r.funct = 2;
	}
	//Instruction I --------------------------------------------------------------------
	else if (!strcmp(termo.c_str(), "beq"))
	{
		i.isInst = true;
		i.opcode = 4;
		fin >> termo;
		i.rs = codigoReg(termo);
		fin >> termo;
		i.rt = codigoReg(termo);
		fin >> termo;
		i.addcons = immediateBranch(symbTab, tamSymbTab, termo.c_str(), linhaAtual);
	}
	else if (!strcmp(termo.c_str(), "bne"))
	{
		i.isInst = true;
		i.opcode = 5;
		fin >> termo;
		i.rt = codigoReg(termo);
		fin >> termo;
		i.rs = codigoReg(termo);
		fin >> termo;
		i.addcons = immediateBranch(symbTab, tamSymbTab, termo.c_str(), linhaAtual);
	}
	else if (!strcmp(termo.c_str(), "addi"))
	{
		i.isInst = true;
		i.opcode = 8;
		fin >> termo;
		i.rt = codigoReg(termo);
		fin >> termo;
		i.rs = codigoReg(termo);
		fin >> termo;
		i.addcons = stoi(termo, nullptr, 10);
	}
	else if (!strcmp(termo.c_str(), "addiu"))
	{
		i.isInst = true;
		i.opcode = 9;
		fin >> termo;
		i.rt = codigoReg(termo);
		fin >> termo;
		i.rs = codigoReg(termo);
		fin >> termo;
		i.addcons = stoi(termo, nullptr, 10);
	}
	else if (!strcmp(termo.c_str(), "slti"))
	{
		i.isInst = true;
		i.opcode = 10;
		fin >> termo;
		i.rt = codigoReg(termo);
		fin >> termo;
		i.rs = codigoReg(termo);
		fin >> termo;
		i.addcons = stoi(termo, nullptr, 10);
	}
	else if (!strcmp(termo.c_str(), "sltiu"))
	{
		i.isInst = true;
		i.opcode = 11;
		fin >> termo;
		i.rt = codigoReg(termo);
		fin >> termo;
		i.rs = codigoReg(termo);
		fin >> termo;
		i.addcons = stoi(termo, nullptr, 10);
	}
	else if (!strcmp(termo.c_str(), "andi"))
	{
		i.isInst = true;
		i.opcode = 12;
		fin >> termo;
		i.rt = codigoReg(termo);
		fin >> termo;
		i.rs = codigoReg(termo);
		fin >> termo;
		i.addcons = stoi(termo, nullptr, 10);
	}
	else if (!strcmp(termo.c_str(), "ori"))
	{
		i.isInst = true;
		i.opcode = 13;
		fin >> termo;
		i.rt = codigoReg(termo);
		fin >> termo;
		i.rs = codigoReg(termo);
		fin >> termo;
		i.addcons = stoi(termo, nullptr, 10);
	}
	else if (!strcmp(termo.c_str(), "lui"))
	{
		i.isInst = true;
		i.opcode = 15;
		fin >> termo;
		i.rt = codigoReg(termo);
		i.rs = 0;
		fin >> termo;
		i.addcons = stoi(termo, nullptr, 10);
	}
	else if (!strcmp(termo.c_str(), "lw"))
	{
		i.isInst = true;
		int constante;
		i.opcode = 35;
		fin >> termo;
		i.rt = codigoReg(termo);
		fin >> constante;
		i.addcons = constante;
		termo = fin.get();
		fin >> termo;
		i.rs = codigoReg(termo);
	}
	else if (!strcmp(termo.c_str(), "sw"))
	{
		i.isInst = true;
		int constante;
		i.opcode = 43;
		fin >> termo;
		i.rt = codigoReg(termo);
		fin >> constante;
		i.addcons = constante;
		termo = fin.get();
		fin >> termo;
		i.rs = codigoReg(termo);
	}
	// Instruction J ------------------------------------------
	else if (!strcmp(termo.c_str(), "j"))
	{
		j.isInst = true;
		j.opcode = 2;
		j.address = (symbTab[1].address) >> 2;
	}
	else if (!strcmp(termo.c_str(), "jal"))
	{
		j.isInst = true;
		j.opcode = 3;
		j.address = (symbTab[1].address) >> 2;
	}

	//Por fim, usaremos a booleana de cada struct para decidir que inteiro retornar...
	int temp;
	if (r.isInst)
		return (temp = toBinary(r));
	else if (i.isInst)
		return (temp = toBinary(i));
	else if (j.isInst)
		return (temp = toBinary(j));
	else
		return -1;	//Caso não seja uma instrução, retorna -1
}

int codigoReg(string& reg)
{

	char num[2]{};	//String que vai ser usada no stoi sem que eu altere o parÂmetro "reg"
	bool teste = true;	//Booleana se o numero que do registrador ja foi encontrado
	for (int i = 0; teste; i++)
		if (isdigit(reg[i]))
		{
			num[0] = reg[i];
			teste = false;
		}

	if (reg[0] == 't' || reg[1] == 't')	//Se for um registrador t
	{
		int regNum = stoi(num, nullptr, 10);

		switch (regNum)
		{
		case 0:
			return 8;
			break;
		case 1:
			return 9;
			break;
		case 2:
			return 10;
			break;
		case 3:
			return 11;
			break;
		case 4:
			return 12;
			break;
		case 5:
			return 13;
			break;
		case 6:
			return 14;
			break;
		case 7:
			return 15;
			break;
		case 8:
			return 24;
			break;
		case 9:
			return 25;
			break;
		default:
			std::cout << "Nao existe tal registrador" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else if (reg[0] == 's' || reg[1] == 's')	//Se for um registrador s
	{
		int regNum = stoi(num, nullptr, 10);

		switch (regNum)
		{
		case 0:
			return 16;
			break;
		case 1:
			return 17;
			break;
		case 2:
			return 18;
			break;
		case 3:
			return 19;
			break;
		case 4:
			return 20;
			break;
		case 5:
			return 21;
			break;
		case 6:
			return 22;
			break;
		case 7:
			return 23;
			break;
		default:
			std::cout << "Nao existe tal registrador" << endl;
			exit(EXIT_FAILURE);
		}
	}
}

int immediateBranch(symb symbTab[], int tam, string label, int nLinha)
{
	int cont = 0;
	while (cont < tam)
	{
		if (!strcmp(label.c_str(), (symbTab[cont].labelNome).c_str()))
			return symbTab[cont].linha - 1 - nLinha;
		cont++;
	}
	return 0;
}

int toBinary(RInstruction& r0)
{
	int binario = 0;
	binario = binario | r0.opcode << 26;
	binario = binario | (r0.rs << 21);
	binario = binario | (r0.rt << 16);
	binario = binario | (r0.rd << 11);
	binario = binario | (r0.sa << 6);
	binario = binario | r0.funct;
	return binario;
}
int toBinary(IInstruction& i0)
{
	int binario = 0;
	binario = binario | i0.opcode << 26;
	binario = binario | (i0.rs << 21);
	binario = binario | (i0.rt << 16);

	if (i0.addcons < 0)
	{
		int mask = -65536;
		i0.addcons = mask ^ i0.addcons;
		binario = binario | i0.addcons;
	}
	else
		binario = binario | i0.addcons;
	return binario;
}
int toBinary(JInstruction& j0)
{
	int binario = 0;
	binario = binario | j0.opcode << 26;
	binario = binario | j0.address;
	return binario;
}

char* IntegerToBinary(int num)
{
	char binario[33]{ "00000000000000000000000000000000" };
	for (int i = num, j = 31; (num > 1) && (j >= 0); i /= 2, j--)
		if (i % 2)
			binario[j] = '1';
	binario[32] = 0;
	return binario;
}