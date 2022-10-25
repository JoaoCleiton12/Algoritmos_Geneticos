#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "funcao.h"
#include "gerador_numeros.h"

typedef struct {
    float x1;
    float x2;
    float fitness;
} t_individuo;

void merge(t_individuo vet[], int tam_vet);

void mergeSort(t_individuo vet[], int tam_vet);
    
float obter_fitness(float x1, float x2);
    
void identificar_dominio(float *l_inf, float *l_sup);
    
void encontra_melhor_individuo(t_individuo vet[], int tam_vet, t_individuo *melhor);

void imprimir_individuo(t_individuo individuo);
   
void imprimir_populacao(t_individuo populacao[], int total_individuos);
    
void gerar_populacao_inicial(t_individuo populacao[], int total_individuos);

void op_mutacao(t_individuo *filho, float prob_mutacao);
    
void op_recombinacao(t_individuo pai,t_individuo mae,t_individuo *filho);
   
void op_selecao_de_pais(t_individuo populacao[], int total_individuos, t_individuo *pai, t_individuo *mae);
   
void op_selecao_de_sobreviventes(t_individuo populacao[], int total_individuos, t_individuo novos_individuos[], int descarte);
   
void executar(int total_individuos, int descarte, int geracoes, float prob_mutacao);