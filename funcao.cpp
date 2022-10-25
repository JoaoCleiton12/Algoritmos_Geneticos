#include "funcao.h"

float funcao(float x1,float x2) {
    return sqrt(pow(x1,3)+ (2 * pow(x2,4)));
}

void identificar_dominio(float *l_inf, float *l_sup){
    *l_inf = 0;
    *l_sup = 7;
}
