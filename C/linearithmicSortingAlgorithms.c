#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef void (*funcao)();

void swap (int* array, int index1, int index2) {

    int aux = array[index1];
    array[index1] = array[index2];
    array[index2] = aux;
}

// Merge Sort Functions

void merge(int vector[], int left, int half, int right) {
    int i, j, k = left;
    int lenL = half - left + 1;
    int lenR = right - half;
 
    int* L = malloc(sizeof(int) * lenL);
    int* R = malloc(sizeof(int) * lenR);
 
    for (i = 0; i < lenL; i++)
        L[i] = vector[left + i];
    for (j = 0; j < lenR; j++)
        R[j] = vector[half + 1 + j];
 
    for(i = 0, j = 0; i < lenL && j < lenR; k++){
 
        if (L[i] <= R[j]) {
            vector[k] = L[i];
            i++;
        }
        else {
            vector[k] = R[j];
            j++;
        }
  
    }
 
    while (i < lenL) {
        vector[k] = L[i];
        i++;
        k++;
    }
 
    while (j < lenR) {
        vector[k] = R[j];
        j++;
        k++;
    }

    free(L); free(R);
}

void mergeSort(int *array, int start, int end) {
	
	if(start >= end) return;

	int half = (start + end) / 2;
	mergeSort(array, start, half);
	mergeSort(array, half+1, end);
	merge(array, start, half, end);
}

// Quick Sort Functions

int partition(int *array, int start, int end) {

    int pivot = end;
    int k = start; // k will be the next pivot

    for (int i = start; i<pivot; i++) {

        if (array[i] <= array[pivot]) { 
            swap(array, i, k);
            k++;
        }
        
    }
    if (array[k] > array[pivot]) swap(array, pivot, k);

    return k;
}

void quickSort(int* array, int start, int end) {

    if (start >= end) return;

    int pivot = partition(array, start, end);

    quickSort(array, start, pivot-1);
    quickSort(array, pivot+1, end);
}

void heapify(int* array, int size, int subTreeRoot) {

    int maior = subTreeRoot;
    int leftChild = 2*subTreeRoot + 1;
    int rightChild = 2*subTreeRoot + 2;

    if (leftChild < size && array[leftChild] > array[maior]) {
        maior = leftChild;
    }
    if (rightChild < size && array[rightChild] > array[maior]) {
        maior = rightChild;
    }

    if (maior != subTreeRoot) {
        swap(array, subTreeRoot, maior);
        heapify(array, size, maior);
    }
}

void heapSort(int* array, int size) {

    for (int i = size/2 - 1; i > -1; i--)
        heapify(array, size, i);

    for (int i = size-1; i > 0; i--) {
        swap(array, 0, i);
        heapify(array, i, 0);
    }
}

void fillVectorSorted(int *array1, int *array2, int *array3, int size) {
    
    for(int i = 0; i<size;i++) array3[i] = array2[i] = array1[i] = i;
}

void fillVectorRandom(int *array1, int *array2, int *array3, int size) {
    
    for(int i = 0; i<size; i++) {
        array3[i] = array2[i] = array1[i] = rand()%1000;
    }
}

void fillVectorBackwards(int *array1, int *array2, int *array3, int size) {
    int aux = 0;
    while (size--) {
        array3[size] = array2[size] = array1[size] = aux++;
    }
}

double diffTempo(funcao f, int* array, int size) {
    
    double difMS;
    clock_t start, end;
    
    if (f == heapSort) {
        
        start = clock();
        f(array, size);
        end = clock();
    }
    else {

        start = clock();
        f(array, 0, size-1);
        end = clock();
    }
    
    difMS = ((double)end-start)*1000/CLOCKS_PER_SEC;
    return difMS;
}

void printInteger(int *array, int size) {

	for(int i = 0; i<size; i++) printf("%d ", array[i]);

	printf("\n");
}

void diffArray(int *array1, int* array2, int size) {
    for(int i = 0; i<size; i++) {
        if (array1[i] != array2[i]) {
            printf("Os vetores n batem\n");
            break;
        }
    }
    printf("Os vetores batem\n");

}

int main(void) {

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

    funcao funcao;

    if (tipoOrdenacaoInicial == 1) {

        fillVectorSorted(vectorA, vectorB, vectorC, size);

    } else if (tipoOrdenacaoInicial == 2) {
        
        fillVectorRandom(vectorA, vectorB, vectorC, size);    
        
    } else {

        fillVectorBackwards(vectorA, vectorB, vectorC, size);
    
    }
        
    funcao = mergeSort;
    double tempoVectA = diffTempo(funcao, vectorA, size);

    funcao = quickSort;
    double tempoVectB = diffTempo(funcao, vectorB, size);

    funcao = heapSort;
    double tempoVectC = diffTempo(funcao, vectorC, size);
    
    printf("\nMerge: \n\tTempo do algoritmo para ordenar o vetor: %.0lf ms", tempoVectA);
    printf("\nQuick: \n\tTempo do algoritmo para ordenar o vetor: %.0lf ms", tempoVectB);
    printf("\nHeap: \n\tTempo do algoritmo para ordenar o vetor: %.0lf ms\n", tempoVectC);

    return 0;
}