//A tradução da instrução tá funcional, mas a escrita no .bin tá falha. Reimplemente essa parte e faz um tradutor binario.
//Substitua as strings por strings_c e teste novamente
//Quebre em funções, diminua o código e separe em arquivos.
//Verificar uma solução mais eficiente e elegante que esse trambolho de ifs e elses

#include <string>
#include <cctype>
#include <fstream>
#include <iostream>
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

int main()
{
	int tamSymbTab = 10;
	cout << "Insira o nome do arquivo: ";
	string arquivo;	//Nome do arquivo 
	char charTemp; 

	while ((charTemp = cin.get()) != '.' && charTemp != '\n')
		arquivo += charTemp;

	ifstream fin;
	symb* symbTab = new symb[tamSymbTab]{}; //Vai ser um vetor que cresce sozinho posteriormente

	//Primeiramente, verificaremos a existencia de labels no arquivo, se os mesmos existirem...

	fin.open((arquivo + ".asm"), ios_base::in);	//Tenta abrir arquivo com o nome indicado
	if (!fin.is_open())					//Se não for possível...
		cout << "Nao foi possivel o arquivo" << endl;
	else								//Caso seja possível...
	{	
		char c;						//Caractere que identifica se há ou não label
		string termo;
		int label = 0, linha = 0, PC = 4194304;		//No de ocorrencias de labels  / Linha atual / Endereço da instrução 

		do
		{
			fin >> termo;
			c = fin.get();	//Lê um caractere
			if (termo[termo.length() - 1] == ':')	//Se for ':' então há um label nessa linha
			{
				termo[termo.length() - 1] = 0;
				symbTab[label].labelNome = termo;	//Guarda o No da linha numa string...
				symbTab[label].linha = linha;		//
				symbTab[label].address = PC;	//
				label++;							//Incrementa as ocorrencias de labels
			}
			else if (c == '\n')	//Se for '\n' então é o fim de uma linha
			{
				linha++;		//Incrementa o número da linha
				PC += 4;
			}
		} while (!fin.eof());	//Repete até o fim do arquivo (quando encontra o eof)


	}
	fin.close();	//Fechando arquivo
	
	ofstream fout;
	fin.open((arquivo + ".asm"), ios_base::in);	//Tenta abrir arquivo com o nome indicado
	fout.open((arquivo + ".bin"), ios_base::out | ios_base::trunc | ios_base::binary);

	if (!fin.is_open())					//Se não for possível...
		cout << "Nao foi possivel abrir o arquivo" << endl;
	else								//Caso seja possível...
	{
		string termo;
		int linhaAtual = 1;
		int binario = 0;

		do
		{
			fin >> termo;

			if (termo[(termo.length() - 1)] != ':' && termo[0] != '$')	//
				binario = translateInstruction(termo, fin, symbTab, tamSymbTab, linhaAtual);
					
			if((charTemp = fin.get()) == '\n')	//Se já for o final da instrução
			{
				linhaAtual++;	//Itera a linhaAtual
				fout.write((char*)&binario, sizeof(int));	//Escreve no arquivo
			}
		}while(!fin.eof());	//Repete até o fim do arquivo (quando encontra o eof)

	}
	fin.close();	//Fechando arquivo
	fout.close();
	delete[] symbTab;

	
	
	//fout.open((arquivo + "(1).bin"), ios_base::out | ios_base::trunc | ios_base::binary);
	//fout.close();

	return 0;
}

int translateInstruction(string& termo, ifstream& fin, symb symbTab[], const int tamSymbTab, const int linhaAtual)
{

	RInstruction r{};
	IInstruction i{};
	JInstruction j{};

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

	int temp;
	if (r.isInst)
		return (temp = toBinary(r));
	else if (i.isInst)
		return (temp = toBinary(i));
	else if (j.isInst)
		return (temp = toBinary(j));
	else
		return -1;
}

int codigoReg(string& reg)
{

	char num[2]{};
	bool teste = true;
	for (int i = 0; teste; i++)
		if (isdigit(reg[i]))
		{
			num[0] = reg[i];
			teste = false;
		}

	if (reg[0] == 't' || reg[1] == 't')
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
		default:
			cout << "Nao existe tal registrador" << endl;
		}
	}
	else if (reg[0] == 's' || reg[1] == 's')
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
			cout << "Nao existe tal registrador" << endl;
		}
	}
}

int immediateBranch(symb symbTab[], int tam, string label, int nLinha)
{
	int cont = 0;
	while (cont < tam)
	{
		if (!strcmp(label.c_str(), (symbTab[cont].labelNome).c_str()))
			return symbTab[cont].linha - nLinha;
		cont++;
	}
	return 0;
}

int toBinary(RInstruction & r0) 
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