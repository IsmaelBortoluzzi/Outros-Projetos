#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct str {

    char ch;
    struct str *next;
};
typedef struct str Str;

typedef struct queue {

    Str *top;
    Str *last;

} Queue;

void insertElement(Queue *queue, char item) {

    Str *element;
    element = (Str*) malloc(sizeof(Str));

    element->ch = item;
    element->next = NULL;

    if(!queue->top) {
        queue->top = element;
        queue->last = element;
        return;
    }
    
    queue->last->next = element;
    queue->last = element;

}

void printQueue(Queue *queue) {

    Str *aux = queue->top;
    while(aux) {
        printf("%c ", aux->ch);
        aux = aux->next;
    }

}

void freeQueue(Queue *queue) {

    Str *aux = queue->top;
    
    while(queue->top) {

        printf("%c\n", queue->top->ch);

        queue->top = queue->top->next;
        if(aux!=NULL) free(aux);
        aux = queue->top;
    }
    queue->top = NULL;
    queue->last = NULL;
}

int main(void) {

    Queue queue; queue.top = NULL; queue.last = NULL;

    for(int i = 65; i<91; i++) {

        insertElement(&queue, i);

    }
    printQueue(&queue);
    printf("\n");
    freeQueue(&queue);

    return 0;
}