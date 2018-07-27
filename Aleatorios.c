#include <time.h>

int aleatorioEntre1y2() {
    srand(time(NULL));
    int numero = rand() % 2 + 1;
    return numero;
}

int aleatorioEntre1y3() {
    srand(time(NULL));
    int numero = rand() % 3 + 1;
    return numero;
}

int aleatorioEntre5y15() {
    srand(time(NULL));
    int numero = rand() % 11 + 5;
    return numero;
}

int aleatorioEntre2y5() {
    srand(time(NULL));
    int numero = rand() % 4 + 2;
    return numero;
}

int aleatorioEntre5y10() {
    srand(time(NULL));
    int numero = rand() % 6 + 5;
    return numero;
}

int aleatorioEntre10y20(){
    srand(time(NULL));
    int numero = rand() % 11 + 10;
    return numero;
}
