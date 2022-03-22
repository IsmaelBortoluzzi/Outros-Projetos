#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct carro {

    char nome[36];
    int ano;

} Carro;

void swap (Carro* array, int index1, int index2) {

    Carro aux = array[index1];
    array[index1] = array[index2];
    array[index2] = aux;

}

Carro newestCarByYear(Carro* array, int size) {

    Carro maior = array[0];
    for (int i = 0; i < size; i++) {

        if (array[i].ano > maior.ano) maior = array[i];
    
    }
    return maior;
}

void coutingSort(Carro* array, int size, int posicao) {

    Carro* aux = (Carro*) malloc(sizeof(Carro) * size);
    int* count = (int*) calloc(10, sizeof(int));
    int digito;

    for (int i = 0; i < size; i++) { // couting each digit appeared

        digito = (array[i].ano / posicao) % 10;
        count[digito]++;

    }
    for (int i = 1; i < 10; i++) { // cumulative sum

        count[i] = count[i] + count[i-1];

    }
    for (int i = size-1; i >= 0; i--) { // build aux sorted for current digit

        digito = (array[i].ano / posicao) % 10;
        aux[--count[digito]] = array[i];

    }
   for (int i = 0; i < size; i++) { // copy aux back to original array

        array[i] = aux[i];

    }
 
}

void radixSort(Carro* array, int size) {

    Carro maior = newestCarByYear(array, size);

    int posicao = 1;
    while (maior.ano / posicao > 0) {

        coutingSort(array, size, posicao);
        posicao *= 10;

    }

}

void printCarros(Carro* array, int size) {

    for (int i = 0; i < size; i++) {
        printf("\nAno: %d     Modelo : %s", array[i].ano, array[i].nome);
    }

}

Carro buildCarro(char* nome, int ano) {

    Carro* car = malloc(sizeof(Carro));

    car->ano = ano;
    strcpy(car->nome, nome);

    return (*car);
}

int main(void) {

    char CARROS_MODELOS[15][36] = { 
        "Kombi 1.6 MPi\0", "Bora 2.0 8v\0", "JETTA GLI 2.0 TSI\0", 
        "Golf 1.4 TSI\0", "Polo 1.4 TSI\0", "Passat 2.8 V6\0",
        "Polo 1.6\0", "CRUZE 2.0\0", "Astra 2.0 MPFI\0",
        "Kadett 2.0 MPFI\0", "Fusca 1300\0", "S10 4.3 v6\0",
        "F-250 4.2\0", "F-1000 Super 3.6\0", "Civic 2.0\0"
    };

    int CARROS_ANOS[15] = { 
        1995, 2003, 2017, 
        2000, 1991, 1989,
        2001, 2009, 1997,
        2006, 1997, 2012,
        1993, 2007, 1986
    };

    Carro carros[15];

    for (int i=0; i < 15; i++) {
        carros[i] = buildCarro(CARROS_MODELOS[i], CARROS_ANOS[i]);
    }

    printCarros(carros, 15);
    puts("\n\n");

    radixSort(carros, 15);

    printCarros(carros, 15);
    puts("\n\n");

    return 0;

}
