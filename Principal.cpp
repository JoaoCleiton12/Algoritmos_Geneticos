#include <iostream>
#include <cstdlib>
#include <bitset>
#include <cmath>
#define TAM_POPULACAO 4
using namespace std;




//fun��o que transforma decimal para binario
void toBinary(unsigned int n)
{
	if (n / 2 != 0) {
		toBinary(n / 2);
	}

	std::cout << n % 2;
}
//fun��o de aptid�o
int funcaoAvaliacao(int x, int y) {
	int final;
	final = sqrt(pow(x,3)+ (2 * pow(y,4)));
	return final;

}
int main() {
	int POPULACAO[TAM_POPULACAO];

	unsigned seed = time(0);
	srand(seed);
	 
	//Inicializando a popula��o
	for (int i = 0; i < TAM_POPULACAO; i++) {
		POPULACAO[i] = rand() % 8;
	}
	
	//Avalia��o de cada indiv�duo na popula��o
	for (int i = 0; i < TAM_POPULACAO; i++) {

	}
	//Selecionar os pais para gerar novos indiv�duos

	//Aplicar os operadores de recombina��o e muta��o a estes pais de forma a gerar os indiv�duos da nova gera��o.
	
	//Apague os velhos membros da popula��o.
	
	//Avalie todos os novos Indiv�duos e insira-os na popula��o.

	//Se o tempo acabou ou o melhor Indiv�duo satisfaz os requerimentos e desempenho, retorne - o, caso contr�rio, volte para o passo c).


	
}