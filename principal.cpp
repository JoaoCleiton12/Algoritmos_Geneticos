#define N_POPULACAO 100
#define N_DESCENDENTES_DESCARTE 50
#define N_GERACOES_EVOLUIR 10
#define TAXA_MUTACAO 0.1

#include "operacoes.h"

int main() {
	executar(N_POPULACAO,N_DESCENDENTES_DESCARTE, N_GERACOES_EVOLUIR,TAXA_MUTACAO);
}