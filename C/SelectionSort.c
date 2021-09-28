#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Node {

	int valor;
	struct Node *next, *prev;
    
} Node;

void dellAll(Node **head, Node **prev) {

	if(!*(head)) return;
	int i = 0;

	Node *aux = *head;
	while(aux->next != NULL) {
		aux=aux->next;
		if (aux->prev != NULL){
			free(aux->prev);
			//printf("- "); 
			printf("%d ", i++); 
		}
	}
	if (aux!=NULL){
		free(aux);
		printf("%d ", i++); 
		//printf("- ");
	}
	*head = NULL;
	*prev = NULL;
}

void insertBeggining(Node **head, Node **tail, int valor) {
	
	Node *new_node;
	new_node=(Node*) malloc(sizeof(Node));
	new_node->valor = valor;
	
	if (*head == NULL) {
		
        *head=new_node;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        *tail=new_node;
        
        return;
	}
    new_node->prev = NULL;
    new_node->next = *head;
    (*head)->prev = new_node;
    *head = new_node;

}

void insertEnd (Node **head, Node **tail, int valor){
	
	Node *new_node;
	new_node=(Node*) malloc(sizeof(Node));
	new_node->valor = valor;
   
	if(*tail == NULL) {
		
        *tail=new_node;
		(*tail)->next = NULL;
        (*tail)->prev = NULL;
        *head=new_node;

		return;
	}
    new_node->next = NULL;
    new_node->prev = *tail;
	(*tail)->next = new_node;
	*tail = new_node;

}


void insertAfter(Node **head, Node **tail, int valor) {



    //Node *aux = *head;


}

void printInteger(Node **head){

	Node* aux;
	aux = *head;

	while(aux!=NULL) {	
		printf("%d ", aux->valor);	
		aux=aux->next;
	}

}

void dellOne(Node **head, Node **tail, int valor) {

	if (!((*head) && (*tail))) {
		printf("Lista Vazia!\n");
	}

	Node* aux;
	aux = *head;

	while(aux!=NULL) {	
		if (aux->valor == valor) {

			if(aux->valor == (*head)->valor) {

				(*head) = (*head)->next;
				if (aux!=NULL) free(aux);
				(*head)->prev = NULL;
				aux = (*head);
			}
			else if(aux->valor == (*tail)->valor) {

				(*tail) = (*tail)->prev;
				if (aux!=NULL) free(aux);
				(*tail)->next = NULL;
				aux = (*tail);
			}
			else {
				Node* retainer = aux->prev;
				
				aux->prev->next = aux->next;
				aux->next->prev = aux->prev;
				if (aux!=NULL) free(aux);
				aux = retainer;
			}

		}	
		aux=aux->next;
	}

}

Node *menorValor(Node *aux) {

	Node* start = aux;
	Node* menor = start;

	while (start != NULL) {
		if (start->valor < menor->valor) menor = start;
		start = start->next;
	}

	return menor;
}


void swapHeadWithTail (Node ***head, Node ***tail) {

	Node *aux = (**head);
	Node *auxNext = aux->next, *auxPrev = aux->prev;

	aux->next = (**tail)->next;
	aux->prev = (**tail)->prev;
	(**tail)->prev->next = aux;

	(**tail)->next = auxNext;
	(**tail)->prev = auxPrev;
	(**tail)->next->prev = (**tail);

	**head = **tail;
	**tail = aux;
}

void swapHeadWithNext(Node ***head, Node **aux, Node **menor) {
		
	Node *menorNext = (*menor)->next;

	(*menor)->next = *aux;
	(*menor)->prev = NULL;
	(*aux)->next = menorNext;
	(*aux)->prev = (*menor);
	
	if (!(*aux)->next)  (*aux)->next->prev = *aux;
	//else tail = menor 
	
	**head = *menor;
}

void swapWithHead(Node ***head, Node **aux, Node **menor) {
	
	Node *auxNext = (*aux)->next, *auxPrev = (*aux)->prev;

	(*aux)->next = (*menor)->next;
	(*aux)->prev = (*menor)->prev;
	(*menor)->next->prev = *aux;
	(*menor)->prev->next = *aux;

	(*menor)->next = auxNext;
	(*menor)->prev = auxPrev;
	(*menor)->next->prev = *menor;
	(*menor)->prev = NULL;
	**head = *menor;
}

void swapWithTail(Node **aux, Node ***tail) {

	Node *auxNext = (*aux)->next, *auxPrev = (*aux)->prev;

	(*aux)->next = NULL;
	(*aux)->prev = (**tail)->prev;
	(**tail)->prev->next = *aux;

	(**tail)->next = auxNext;
	(**tail)->prev = auxPrev;
	(**tail)->next->prev = (**tail);
	(**tail)->prev->next = (**tail);

	**tail = *aux;
}

void swapWithNext(Node **aux, Node **menor) {

	Node *menorNext = (*menor)->next;

	(*menor)->next = *aux;
	(*menor)->prev = (*aux)->prev;
	(*menor)->prev->next = (*menor);

	(*aux)->next = menorNext;
	(*aux)->next->prev = *aux;
	(*aux)->prev = *menor;

}

void swapNode(Node **aux, Node **menor) {

	Node *auxNext = (*aux)->next;
	Node *auxPrev = (*aux)->prev;

	(*aux)->next = (*menor)->next;
	(*aux)->prev = (*menor)->prev;
	(*menor)->next->prev = *aux;
	(*menor)->prev->next = *aux;

	(*menor)->next = auxNext;
	(*menor)->prev = auxPrev;
	(*menor)->next->prev = *menor;
	(*menor)->prev->next = *menor;

}

void swapTailWithPrev(Node ***tail, Node **aux) {

	(**tail)->prev = (*aux)->prev;
	(**tail)->next = *aux;
	(**tail)->prev->next = (**tail);
	(*aux)->next = NULL;
	(**tail) = *aux;

}

void selectionSort(Node **head, Node **tail) {

	Node *aux = (*head);
	Node *menor = menorValor(aux);
	printf("%d\n", menor->valor);
	
	if(menor == aux){
	} 
	else if (menor == *(tail)) {

		swapHeadWithTail(&head, &tail);
	}
	else if (menor == aux->next) {
		
		swapHeadWithNext(&head, &aux, &menor);
	}
	else {
	
		swapWithHead(&head, &aux, &menor);
	}
	aux = (*head)->next;

	while (aux->next->next) {

		menor = menorValor(aux);

		if(menor == aux){
		}
		else if (menor == *(tail)) {

			swapWithTail(&aux, &tail);
			aux = menor;
		}
		else if (menor == aux->next) {
			
			swapWithNext(&aux, &menor);
			aux = menor;
		}
		else {
		
			swapNode(&aux, &menor);
			aux = menor;
		}
		
		aux = aux->next;	
	}

	if (aux->valor < aux->next->valor) return;

	swapTailWithPrev(&tail, &aux);

}

int main(void) {

	srand(time(NULL));
	Node *head=NULL, *tail=NULL;

	//insertBeggining(&head, &tail, 992);
	//insertBeggining(&head, &tail, 444);
	//insertBeggining(&head, &tail, 633);
	//insertBeggining(&head, &tail, 117);
	//insertBeggining(&head, &tail, 617);
	//insertEnd(&head, &tail, 29);
	//dellOne(&head, &tail, 5);

	for (int i = 0; i<25; i++) {
		insertEnd(&head, &tail, rand()%1000);
	}
	//insertBeggining(&head, &tail, rand()%1000);

	printInteger(&head);
	printf("\n");
	selectionSort(&head, &tail);
	printf("\n");
	printInteger(&head);
	
	printf("\n");
	dellAll(&head, &tail);
	
}
