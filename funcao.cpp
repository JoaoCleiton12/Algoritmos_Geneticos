#include "funcao.h"

float funcao(float x1,float x2) {
    return sqrt(pow(x1,3)+ (2 * pow(x2,4)));
}

void dominio_funcao(float d[]) {
    d[0] = 0;
    d[1] = 7;
}