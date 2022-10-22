#include <iostream>
#include <cstdlib>
#include <bitset>
#include <cmath>
#define TAM_POPULACAO 4
using namespace std;




//função que transforma decimal para binario
void toBinary(unsigned int n)
{
	if (n / 2 != 0) {
		toBinary(n / 2);
	}

	std::cout << n % 2;
}
//função de aptidão
int funcaoAvaliacao(int x, int y) {
	int final;
	final = sqrt(pow(x,3)+ (2 * pow(y,4)));
	return final;

}
int main() {
	int POPULACAO[TAM_POPULACAO];

	unsigned seed = time(0);
	srand(seed);
	 
	//Inicializando a população
	for (int i = 0; i < TAM_POPULACAO; i++) {
		POPULACAO[i] = rand() % 8;
	}
	
	//Avaliação de cada indivíduo na população
	for (int i = 0; i < TAM_POPULACAO; i++) {

	}
	//Selecionar os pais para gerar novos indivíduos

	//Aplicar os operadores de recombinação e mutação a estes pais de forma a gerar os indivíduos da nova geração.
	
	//Apague os velhos membros da população.
	
	//Avalie todos os novos Indivíduos e insira-os na população.

	//Se o tempo acabou ou o melhor Indivíduo satisfaz os requerimentos e desempenho, retorne - o, caso contrário, volte para o passo c).


	
}