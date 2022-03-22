#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef unsigned long long int intzao;
typedef void (funcao)();

void swap(int *vector,int a,int b){
    int aux = vector[a];
    vector[a] = vector[b];
    vector[b] = aux;
}

void bubbleSort(int *vector, int size, intzao* contador) {

    (*contador) = 0;
    int flag;
    for (int i = size-1; i>0; i--) {
        
        flag = 0;
        for (int j = 0; j<i; j++) {
            
            if(vector[j]>vector[j+1]) {
                flag = 1;
                swap(vector,j,j+1);
            }
            (*contador)++;
        }
        
        if (flag == 0) break;
    }
}

void selectionSort(int *array, int size, intzao* contador) {
    
    (*contador) = 0;
    for(int i = 0; i<size-1; i++) {
        
        int menor = i;
        for(int j = i+1; j<size; j++) {

            if (array[j] < array[menor]) menor = j;
            (*contador)++;  
        }
        swap(array, i, menor);
    }
}

void insertionSort(int *array, int size, intzao* contador) {
    
    (*contador) = 0;
    for(int i = 1; i<size; i++) {

        int key = array[i];
        int j = i-1;

        while(j>=0 && array[j] > key) {

            array[j+1] = array[j];
            j--;
            (*contador)++;
        }
        array[j+1] = key;
        (*contador)++;
    }
}

void fillVectorSorted(int *array, int size) {
    
    for(int i = 0; i<size;i++) array[i] = i;
}

void fillVectorRandom(int *array1, int *array2, int *array3, int size) {
    
    for(int i = 0; i<size; i++) {
        array3[i] = array2[i] = array1[i] = rand()%1000;
    }
}

void fillVectorBackwards(int *array, int size) {
    int aux = 0;
    while (size--) array[size] = aux++;
}

void printInteger(int *array, int size) {

    for(int i = 0; i<size; i++) printf("%d ", array[i]);

    printf("\n\n");
}

double diffTempo(funcao *f, int* arg, int size, intzao* contador) {
    double difMS;
    clock_t start, end;
    start = clock();
    f(arg, size, contador);
    end = clock();
    difMS = ((double)end-start)*1000/CLOCKS_PER_SEC;
    return difMS;
}

int main(void) {

    intzao contador = 0;
    int tipoOrdenacaoInicial;

    srand(time(NULL));

    int size = -1;
    while(size < 0) {
        printf("Digite o tamanho dos vetores: ");
        scanf("%d", &size);
        puts("");
    }
    printf("Digite o estado inicial do vetor: (ordenado = 1, aleatorio = 2, inverso = 3) ");
    scanf("%d", &tipoOrdenacaoInicial);

    int* vectorA = (int*) malloc(sizeof(int) * size);
    int* vectorB = (int*) malloc(sizeof(int) * size);
    int* vectorC = (int*) malloc(sizeof(int) * size);

    funcao* funcao;

    if (tipoOrdenacaoInicial == 1) {

        fillVectorSorted(vectorA, size);
        fillVectorSorted(vectorB, size);
        fillVectorSorted(vectorC, size);

    } else if (tipoOrdenacaoInicial == 2) {
        
        fillVectorRandom(vectorA, vectorB, vectorC, size);    
        
    } else {

        fillVectorBackwards(vectorA, size);
        fillVectorBackwards(vectorB, size);
        fillVectorBackwards(vectorC, size);

    }
        
    funcao = bubbleSort;
    double tempoVectA = diffTempo(funcao, vectorA, size, &contador);
    intzao contadorA = contador;

    funcao = selectionSort;
    double tempoVectB = diffTempo(funcao, vectorB, size, &contador);
    intzao contadorB = contador;

    funcao = insertionSort;
    double tempoVectC = diffTempo(funcao, vectorC, size, &contador);
    intzao contadorC = contador;
    
    printf("\nBubble: \n\tTempo do algoritmo para ordenar o vetor: %.0lf ms; %lld comparacoes feitas\n", tempoVectA, contadorA);
    printf("\nSelection: \n\tTempo do algoritmo para ordenar o vetor: %.0lf ms; %lld comparacoes feitas\n", tempoVectB, contadorB);
    printf("\nInsertion: \n\tTempo do algoritmo para ordenar o vetor: %.0lf ms; %lld comparacoes feitas\n\n", tempoVectC, contadorC);

    return 0;
}