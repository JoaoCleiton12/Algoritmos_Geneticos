#include "ag.h"

void merge(t_individuo vet[], int tam_vet) {

    int mid;
    int i, j, k;
    t_individuo* tmp;
    tmp = (t_individuo*) malloc(tam_vet * sizeof(t_individuo));
    
    if (tmp == NULL) {
        exit(1);
    }
    
    mid = tam_vet / 2;
    i = 0;
    j = mid;
    k = 0;
    
    while (i < mid && j < tam_vet) {
        if (vet[i].fitness <= vet[j].fitness) {
            tmp[k] = vet[i++];
        }
        else {
            tmp[k] = vet[j++];
        }
        ++k;
    }
    
    if (i == mid) {
        while (j < tam_vet) {
            tmp[k++] = vet[j++];
        }
    }
    else {
        while (i < mid) {
            tmp[k++] = vet[i++];
        }
    }
    
    for (i = 0; i < tam_vet; ++i) {
        vet[i] = tmp[i];
    }
    
    free(tmp);
}

/*
 * Ordenacao da Populacao pelo Fitness
 * O procedimento abaixo implementa o algoritmo de Ordenação MERGE SORT.
 */
void mergeSort(t_individuo vet[], int tam_vet) {
    int mid;
    if (tam_vet > 1) {
        mid = tam_vet / 2;
        mergeSort(vet, mid);
        mergeSort(vet+mid, tam_vet-mid);
        merge(vet, tam_vet);
    }
}

float obter_fitness(float x1, float x2) {
    return funcao(x1,x2);
}

void identificar_dominio(float *l_inf, float *l_sup){
    float d[2];
    dominio_funcao(d);
    *l_inf = d[0];
    *l_sup = d[1];
}

/*
 * O procedimento abaixo eh responsavel por encontrar o melhor individuo (o que possui o menor fitness) no vetor "vet".
 */
void encontra_melhor_individuo(t_individuo vet[], int tam_vet, t_individuo *melhor){
    int i;
    *melhor = vet[0];
    for(i = 1; i < tam_vet; i++){
        if (vet[i].fitness < melhor->fitness) *melhor = vet[i];
    }
}

/*
 * Procedimento para imprimir um unico individuo do tipo t_individuo
 */
void imprimir_individuo(t_individuo individuo){
    printf("x1 = %f\n",individuo.x1);
    printf("x2 = %f\n",individuo.x2);
    printf("fitness = %f\n\n",individuo.fitness);
}

/*
 * Procedimento para imprimir um vetor de t_individuo
 */
void imprimir_populacao(t_individuo populacao[], int total_individuos){
    int i;
    for(i = 0; i < total_individuos; ++i){
        //printf("(%d) x1 = %f; x2 = %f\n",i,populacao[i].x1,populacao[i].x2);
        printf("fitness: %f\n",populacao[i].fitness);
        
        //printf("fitness: %d\n\n",obter_numero_uniforme_discreto(0,4)); //4 inclusive
    }
}

/*
 * Geracao da Populacao Inicial
 * O procedimento abaixo e responsavel por gerar a populacao inicial do algoritmo genetico.
 * Os parametros de entrada deste procedimento sao:
 *  - a populacao (vetor de "t_individuo")
 *  - o tamanho da populacao ("total_individuos")
 */
void gerar_populacao_inicial(t_individuo populacao[], int total_individuos){

    float l_inf = 0.0;
    float l_sup = 0.0;
    identificar_dominio(&l_inf,&l_sup);

    int i;
    for(i = 0; i < total_individuos; ++i){
        populacao[i].x1 = obter_numero_uniforme_continuo(l_inf,l_sup);
        populacao[i].x2 = obter_numero_uniforme_continuo(l_inf,l_sup);
        populacao[i].fitness = obter_fitness(populacao[i].x1, populacao[i].x2);      
    }
    
}

/*
 * Operador de Mutacao
 * Este procedimento implementa o operador de mutação por RESET ALEATORIO
 * Os parametros de entrada deste procedimento são:
 *  - o filho (ou descendente) gerado pela recombinação de dois pais selecionados
 *  - a probabilidade (baixa) de mutacao 
 */
void op_mutacao(t_individuo *filho, float prob_mutacao){
    float u = obter_numero_uniforme();
    
    if (u <= prob_mutacao){
    
        float l_inf = 0.0;
        float l_sup = 0.0;
        identificar_dominio(&l_inf,&l_sup);

        filho->x1 = obter_numero_uniforme_continuo(l_inf,l_sup);
        filho->x2 = obter_numero_uniforme_continuo(l_inf,l_sup);
        filho->fitness = obter_fitness(filho->x1, filho->x2);      
    }
    
}

/*
 * Operador de Recombinacao
 * O procedimento abaixo e responsavel por recombinar os codigos geneticos de ambos os pais
 * para criar um novo individuo descendente (filho).
 *
 * Foi implementado o operador de recombinação Aritmética Completa.
 
 * Os parametros de entrada deste procedimento sao:
 *  - os pais selecionados no torneio ("pai" e "mae")
 *  - o novo individuo (filho ou descendente) a ser gerado pela recombinacao dos dois pais selecionados
 */
void op_recombinacao(t_individuo pai,t_individuo mae,t_individuo *filho){
    float alpha = 0.5;

    filho->x1 = alpha*pai.x1 + (1 - alpha)*mae.x1;
    filho->x2 = alpha*pai.x2 + (1 - alpha)*mae.x2;
    filho->fitness = obter_fitness(filho->x1, filho->x2);
}

/*
 * Operador de Selecao de Pais
 * No procedimento abaixo, candidatos a pais sao sorteados aleatoriamente, sendo que o candidato vencedor do torneio
 * sera aquele que possuir o melhor (menor) fitness.
 *
 * Os parametros de entrada deste procedimento sao:
 *  - a populacao (vetor de "t_individuo")
 *  - o tamanho da populacao ("total_individuos")
 *  - os pais a serem selecionados no torneio ("pai" e "mae"). [SELECAO POR TORNEIO]
 */
void op_selecao_de_pais(t_individuo populacao[], int total_individuos, t_individuo *pai, t_individuo *mae){
    t_individuo sorteio[3];
    
    sorteio[0] = populacao[obter_numero_uniforme_discreto(0,total_individuos-1)];
    sorteio[1] = populacao[obter_numero_uniforme_discreto(0,total_individuos-1)];
    sorteio[2] = populacao[obter_numero_uniforme_discreto(0,total_individuos-1)];
    encontra_melhor_individuo(sorteio,3,pai);
    
    sorteio[0] = populacao[obter_numero_uniforme_discreto(0,total_individuos-1)];
    sorteio[1] = populacao[obter_numero_uniforme_discreto(0,total_individuos-1)];
    sorteio[2] = populacao[obter_numero_uniforme_discreto(0,total_individuos-1)];
    encontra_melhor_individuo(sorteio,3,mae);
  
}

/*
 * Operador de Selecao de Sobreviventes
 *
 * No procedimento abaixo e implementado o mecanismo de selecao dos sobreviventes,
 *  usando a estrategia de substituicao dos "lambda" piores individuos,
 *  segundo a avaliacao do fitness.
 *
 * A quantidade de individuos a ser substituida esta representada pela variavel "descarte"
 * Os parametros de entrada deste procedimento sao:
 *  - a populacao (vetor de "t_individuo")
 *  - o tamanho da populacao ("total_individuos")
 *  - o vetor que representada novos individuos ("novos_individuos")
 *  - "descarte": a quantidade de individuos a estarem presentes no vetor "novos_individuos"
 * 
 */
void op_selecao_de_sobreviventes(t_individuo populacao[], int total_individuos, t_individuo novos_individuos[], int descarte){
    int i = 0;
    int j = total_individuos-1;
    
    for(i = 0; i < descarte; i++, j--){
        populacao[j] = novos_individuos[i];
    }
}

/*
 * Evolucao da Populacao
 * No procedimento "executar" que e realizada a Evolucao da Populacao.
 
 * Os parametros de entrada deste procedimento sao:
 *  - o tamanho da populacao (ou total de individuos "total_individuos" da populacao)
 *  - a quantidade "descarte" de individuos a serem substituidos na proxima geracao
 *  - por quantas "geracoes" a populacao inicial sera evoluida
 *  - a probabilidade (baixa) de mutacao (prob_mutacao)
 */
void executar(int total_individuos, int descarte, int geracoes, float prob_mutacao){
    srand((unsigned)time(NULL)); 
    
    /*
     * A Populacao e representada como um vetor de "t_individuo", cujo o tamanho e "total_individuos".
     */
    t_individuo populacao[total_individuos]; 
    
    gerar_populacao_inicial(populacao, total_individuos);
    
    int g = 0; //contador de geracoes
    
    printf("\n#\tx_1\t\tx_2\t\tf(x_1, x_2)\n"); //Saida de Dados
    for(g = 0; g < geracoes; g++){
    
        t_individuo novos_individuos[descarte]; //vetor de novos individuos
        
        int i;
        for(i = 0; i < descarte; i++){
        
            t_individuo pai;
            t_individuo mae;
            t_individuo filho;
            
            //printf("SELECAO DE PAIS\n");
            op_selecao_de_pais(populacao, total_individuos, &pai, &mae);
            //imprimir_individuo(pai);
            //imprimir_individuo(mae);
            
            //printf("RECOMBINACAO\n");
            op_recombinacao(pai,mae,&filho);
            //imprimir_individuo(filho);
            
            //printf("MUTACAO\n");
            op_mutacao(&filho,prob_mutacao);
            //imprimir_individuo(filho);
            
            novos_individuos[i] = filho;
        }
        
        mergeSort(populacao, total_individuos);

        op_selecao_de_sobreviventes(populacao,total_individuos,novos_individuos,descarte);
        
        mergeSort(populacao, total_individuos);
        
        // Saida de Dados
        printf("%d\t%f\t%f\t%f\n",g,populacao[0].x1,populacao[0].x2,populacao[0].fitness); //saida de dados        
        
    }

}