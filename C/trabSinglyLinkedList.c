#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data {

    int dia;
    int mes;
    int ano;

};
typedef struct data Data;

struct aluno {

    char matricula[10];
    char nome[40];
    Data dataNascimento;
    float mediaNotas;
    struct aluno *next;
    
};
typedef struct aluno Aluno;


Aluno* incluirAluno(Aluno *first) {

    Aluno *aux=first, *aluno;

    aluno = (Aluno*) malloc(sizeof(Aluno));
    scanf("%s", aluno->matricula);
    scanf("%s", aluno->nome);
    scanf("%d/%d/%d", &aluno->dataNascimento.dia, &aluno->dataNascimento.mes, &aluno->dataNascimento.ano);
    scanf("%f", &aluno->mediaNotas);
    aluno->next = NULL;

    if (!first) { 
        first = aluno;
        return first;
    }

    while(aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = aluno; 

    return first;
}

void printAlunos(Aluno *first) {

    if(!first){
        printf("Lista Vazia!\n");
        return;
    }

    Aluno *aux;
    aux = first;

    while(aux != NULL) {
        printf("%s, ", aux->matricula);
        printf("%s, ", aux->nome);
        printf("%d/%d/%d, ", aux->dataNascimento.dia, aux->dataNascimento.mes, aux->dataNascimento.ano);
        printf("%.2f\n", aux->mediaNotas);
        aux = aux->next;
    }
    
}

Aluno *excluirAluno(Aluno *first) {
    
    char matric[10];
    scanf("%s", matric);

    if(!first){
        printf("Lista Vazia!\n");
        return first;
    }
    
    Aluno *aux, *previous;
    aux = first;
    previous = first;

    while(aux != NULL) { 
        
        if(!strcmp(aux->matricula, matric)) {

            if(aux == first) { 

                first = first->next;

            } else{

                previous->next = aux->next;
                
            }
            if (aux != NULL) free(aux);
            aux = previous->next;
        } 
        else {
            
            previous = aux;
            aux = aux->next;
        }
    
    }
    return first;

}

void freeMemory(Aluno *first) {

    Aluno *aux=first->next, *previous=first;
    while(aux != NULL) {
        free(previous);
        previous=aux;
        aux=aux->next;
        printf("-");
    }
    if(previous!=NULL){
        free(previous);
        printf("-");
    }

}

void printAlunosInversamente(Aluno *first) {
    
    if (first == NULL) {
        return;
    }

    printAlunosInversamente(first->next);

    printf("%s, ", first->matricula);
    printf("%s, ", first->nome);
    printf("%d/%d/%d, ", first->dataNascimento.dia, first->dataNascimento.mes, first->dataNascimento.ano);
    printf("%.2f\n", first->mediaNotas);

}

int contarAlunos(Aluno *first) {
    Aluno *aux=first;
    int contagem = 0;

    while (aux != NULL) {
        
        contagem++;
        aux = aux->next;
    }
    return contagem;
}

int main(void) {

    Aluno *first=NULL;
    int option = 1;

    while(option) {

        scanf("%d", &option);

        switch (option) {

            case 1:
                
                first = incluirAluno(first);
                break;

            case 2:

                first = excluirAluno(first);     
                break;

            case 3:

                printAlunos(first);
                break;
            
            case 4:

                if(!first) {
                    printf("Lista Vazia!\n");
                }
                else {
                    printAlunosInversamente(first);
                }
                break;
                
            case 5:

                printf("%d\n", contarAlunos(first));
                break;
        }
    
    }

    freeMemory(first);
    printf("\n\n");

    return 0;
}