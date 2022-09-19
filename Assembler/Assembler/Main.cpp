#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	cout << "Insira o nome do arquivo (com extensao): ";
	string arquivo, ocorrencia = "Ocorrencias de label nas linhas: ";	//Nome do arquivo e ocorrencias de labels
	cin >> arquivo;														//Lendo nome do arquivo
	ifstream fin;

	//Primeiramente, verificaremos a existencia de labels no arquivo, se os mesmos existirem...

	fin.open(arquivo, ios_base::in);	//Tenta abrir arquivo com o nome indicado
	if (!fin.is_open())					//Se não for possível...
		cout << "Nao foi possivel o arquivo" << endl;
	else								//Caso seja possível...
	{	
		char c;						//Caractere que identifica se há ou não label
		int label = 0, linha = 1;		//No de ocorrencias de labels  / Linha atual

		do
		{
			c = fin.get();	//Lê um caractere
			if (c == ':')	//Se for ':' então há um label nessa linha
			{
				ocorrencia += to_string(linha);	//Guarda o No da linha numa string...
				ocorrencia += ' ';				//e separa por um espaço
				label++;						//Incrementa as ocorrencias de labels
			}
			else if (c == '\n')	//Se for '\n' então é o fim de uma linha
				linha++;		//Incrementa o número da linha
		} while (!fin.eof());	//Repete até o fim do arquivo (quando encontra o eof)

		cout << ocorrencia << endl; //Imprimindo as ocorrencias de labels para fins de visualização
	}
	fin.close();	//Fechando arquivo
	
	
	
	return 0;
}