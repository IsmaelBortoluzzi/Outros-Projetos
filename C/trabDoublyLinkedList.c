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
    struct aluno *next, *prev;
    
};
typedef struct aluno Aluno;


void incluirAluno(Aluno **head, Aluno **tail, char matricula[11]) {

    Aluno *aux=(*head), *aluno;

    aluno = (Aluno*) malloc(sizeof(Aluno));
    scanf("%s", aluno->matricula);
    scanf("%s", aluno->nome);
    scanf("%d/%d/%d", &aluno->dataNascimento.dia, &aluno->dataNascimento.mes, &aluno->dataNascimento.ano);
    scanf("%f", &aluno->mediaNotas);
    aluno->next = NULL;
    aluno->prev = NULL;

    if (!(*head)) { 
        (*head) = aluno;
        (*tail) = aluno;
        return;
    }

    while(strcmp(aux->matricula, matricula) && aux->next!=NULL) {
        aux = aux->next;
    }
    
    if (!strcmp((*tail)->matricula, matricula)) { 
        aluno->prev = *tail;
        (*tail)->next = aluno;
        *tail = aluno;
        return;
    }
    if(aux->next==NULL) {

        aluno->next = *head;
        (*head)->prev = aluno;
        (*head) = aluno;
        return;
    }

    aluno->next = aux->next;
    aluno->prev = aux;
    aux->next->prev = aluno;
    aux->next = aluno;
    
}

void dellOne(Aluno **head, Aluno **tail, char matricula[11]) {

	if (!((*head) && (*tail))) {
		printf("Lista Vazia!\n");
	}

	Aluno* aux;
	aux = *head;

	while(aux!=NULL) {	
		if (!strcmp(aux->matricula, matricula)) {

			if(!strcmp((*head)->matricula, matricula)) {
                
                if((*head)->next != NULL) {
                    (*head) = (*head)->next;
                    if (aux!=NULL) free(aux);
                    (*head)->prev = NULL;
                    aux = (*head);
                    continue;
                }
                else {
                    if (aux!=NULL) free(aux);
                    return;
                }
			}
			else if(!strcmp((*tail)->matricula, matricula)) {

				(*tail) = (*tail)->prev;
				if (aux!=NULL) free(aux);
				(*tail)->next = NULL;
				aux = (*tail);
			}
			else {
				Aluno* retainer = aux->prev;
				
				aux->prev->next = aux->next;
				aux->next->prev = aux->prev;
				if (aux!=NULL) free(aux);
				aux = retainer;
			}

		}	
		aux=aux->next;
	}

}

void printAlunos(Aluno *head) {

    if(!head){
        printf("Lista Vazia!\n");
        return;
    }

    Aluno *aux;
    aux = head;

    while(aux != NULL) {
        printf("%s, ", aux->matricula);
        printf("%s, ", aux->nome);
        printf("%d/%d/%d, ", aux->dataNascimento.dia, aux->dataNascimento.mes, aux->dataNascimento.ano);
        printf("%.2f\n", aux->mediaNotas);
        aux = aux->next;
    }
    
}

void printAlunosInversamente(Aluno *tail) {

    if(!tail){
        printf("Lista Vazia!\n");
        return;
    }

    Aluno *aux = tail;

    while(aux != NULL) {
        printf("%s, ", aux->matricula);
        printf("%s, ", aux->nome);
        printf("%d/%d/%d, ", aux->dataNascimento.dia, aux->dataNascimento.mes, aux->dataNascimento.ano);
        printf("%.2f\n", aux->mediaNotas);
        aux = aux->prev;
    }
    
}

void dellAll(Aluno **head, Aluno **prev) {

    if (!(*head)) {
		return;
	}

	Aluno *aux = *head;
	while(aux->next != NULL) {
		aux=aux->next;
		if (aux->prev != NULL){
			 free(aux->prev);
			 printf("*");
		}
	}
	if (aux!=NULL){
		 free(aux);
		 printf("*\n");
	}
	*head = NULL;
	*prev = NULL;
}

int main(void) {

    Aluno *head=NULL, *tail=NULL;
    int option = 1;

    while(option) {
        char matricula[11];
        scanf("%d", &option);

        switch (option) {

            case 1:
                scanf("%s", matricula);

                incluirAluno(&head, &tail, matricula);
                break;

            case 2:
                scanf("%s", matricula);

                dellOne(&head, &tail, matricula);     
                break;

            case 3:

                printAlunos(head);
                break;
            
            case 4:
    
                printAlunosInversamente(tail);
                break;
                
        }
    
    }

    dellAll(&head, &tail);
    printf("\n");

    return 0;
}
