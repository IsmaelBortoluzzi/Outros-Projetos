#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct str {

    char ch[60];
    struct str *next;
};
typedef struct str Str;

typedef struct stack {

    Str *top;

} Stack;

void push(Stack *pilha, char item[60]) {

    Str *element;
    element = (Str*) malloc(sizeof(Str));

    strcpy(element->ch, item);
    element->next = pilha->top;
    pilha->top = element;

}

void pop(Stack *pilha) {

    if(!pilha->top) {
        printf("Vazio\n");
        return;
    }

    printf("%s\n", pilha->top->ch);
    
    Str *aux = pilha->top;
    pilha->top = pilha->top->next;
    if(aux!=NULL) free(aux);

}

void freeStack(Stack *pilha) {

    if(!pilha->top) {
        printf("!\n");
        return;
    }

    Str *aux = pilha->top;
    while (pilha->top) {

        printf("@");

        pilha->top = pilha->top->next;
        if(aux!=NULL) free(aux);
        aux = pilha->top;
    }
    printf("\n");

}

void initStack(Stack *pilha) {
    pilha->top = NULL;
}

int main(void) {

    Stack stack; initStack(&stack);

    while(7) {

        char option[60];
        scanf("%s", option);

        if (!strcmp(option, "B")) pop(&stack);
        
        else if (!strcmp(option, "E")) break;
        
        else push(&stack, option);

    }

    freeStack(&stack);

    return 0;
}