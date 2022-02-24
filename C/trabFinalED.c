#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	
    int day;
	int month;

} Date;

typedef struct REC {
    
    char name[50];
    int prioridade;
    Date entrega; 
    struct REC *left, *right; 

} Task;

typedef struct {

   Task *root;

} BST;


Task *createNode(Task *newNode) {
    
    newNode = (Task*) malloc(sizeof(Task));
    
    printf("Digite o nome da tarefa: "); getchar();
    fgets(newNode->name, 50, stdin);
    strtok(newNode->name, "\n");

    printf("Digite a prioridade da tarefa: "); 
    scanf("%d", &newNode->prioridade); 

    
    printf("Digite a data da tarefa (dd/mm): ");
    scanf("%d/%d", &newNode->entrega.day, &newNode->entrega.month);

    newNode->left = newNode->right = NULL;

    return newNode;
}


Task *addTask(Task *root, Task *task) {

    if (root==NULL) return task;

    if (strcmp(task->name, root->name) > 0) {

        root->right = addTask(root->right, task);
    }
    else {

        root->left = addTask(root->left, task);
    }
    return root;
}


void insert(BST *tree) {
    Task *newNode = NULL;

    newNode = createNode(newNode);
    tree->root = addTask(tree->root, newNode);
}


Task* swap(Task* task, Task* sucessor) {

    strcpy(task->name, sucessor->name);
    task->prioridade = sucessor->prioridade;
    task->entrega.day = sucessor->entrega.day;
    task->entrega.month = sucessor->entrega.month;
    
    return task;
}


Task* excluirTask(Task *root, char* key) {

    if (!root) {
        printf("Esta Tarefa Nao Existe");
        return root;
    }

    if (strcmp(key, root->name) < 0) {

        root->left = excluirTask(root->left, key);
        return root;
    } 
    else if (strcmp(key, root->name) > 0) {

        root->right = excluirTask(root->right, key);
        return root;
    }
    
    //se não for maior nem menor, quer dizer que é igual

    if (!(root->left)) {

        Task *aux = root->right;
        free(root);
        return aux;
    } 
    else if(!(root->right)) {

        Task *aux = root->left;
        free(root);
        return aux;
    }
    else {  // Significa que o node tem um left e um right

        // Iremos achar o menor node da right subtree para poder fazer 
        //o swap com o node a ser excluido. Depois damos um free(menor)
        Task *paiSucessor = root; 

        Task *sucessor = root->right;
        while (sucessor->left) {
            paiSucessor = sucessor;
            sucessor = sucessor->left;
        }

        if (paiSucessor != root) paiSucessor->left = sucessor->right;
        else paiSucessor->right = sucessor->right;

        root = swap(root, sucessor);

        free(sucessor);
        return root;
    }
}

void buscarTask(Task *root, char* key) {

    if (!root) {
        printf("Esta Tarefa Nao Existe");
        return;
    }

    if (strcmp(key, root->name) < 0) {

        buscarTask(root->left, key);

    } 
    else if (strcmp(key, root->name) > 0) {

        buscarTask(root->right, key);

    }
    else {
        printf("Tarefa: %s\nPrioridade: %d\nData: %d/%d\n", root->name, root->prioridade, root->entrega.day, root->entrega.month);
        return;
    }

}


Task *updateTask(Task *root, char* key) {
     
    if (!root) {
        printf("Esta Tarefa Nao Existe");
        return root;
    }
    if (strcmp(key, root->name) < 0) {

        root->left = updateTask(root->left, key);
        return root;
    } 
    else if (strcmp(key, root->name) > 0) {

        root->right = updateTask(root->right, key);
        return root;
    }
    else {
        Task aux;
        puts("Prioridade: ");    
        scanf("%d", &aux.prioridade);

        puts("Data (dd/mm): ");  
        scanf("%d/%d", &aux.entrega.day, &aux.entrega.month);
        getchar(); 
        
        root->prioridade = aux.prioridade;
        root->entrega.day = aux.entrega.day;
        root->entrega.month = aux.entrega.month;

        return root;
    }
}


void inOrder(Task *root) {

    if (!root) return;

    inOrder(root->left);
    printf("Tarefa: %s\nPrioridade: %d\nData: %d/%d\n\n", root->name, root->prioridade, root->entrega.day, root->entrega.month);
    inOrder(root->right);
}


Task *initialLoad(Task *root, FILE *fp){

    if (!fp) return root;
    
    fseek (fp, 0, SEEK_END);
    int size = ftell(fp);

    if (size == 0) return root;
    rewind(fp);

    while(!feof(fp)){
        
        Task *newTask = malloc(sizeof(Task));
        fgets(newTask->name, 50, fp); 
        strtok(newTask->name, "\n");
        fscanf(fp, "%d", &newTask->prioridade);
        fscanf(fp, "%2d/%2d", &newTask->entrega.day, &newTask->entrega.month);
        fgetc(fp);
        root = addTask(root, newTask);

    }

    return root;
}

void saveTreeInVector(Task* root, Task **vector, int *index) {

    if (!root) return;

    saveTreeInVector(root->left, vector, index);
    vector[(*index)] = root; (*index)++; 
    saveTreeInVector(root->right, vector, index);

}

Task *rebuildTree(Task **vector, int leftIndex, int rightIndex) {

    if(leftIndex > rightIndex) return NULL;

    int mid = (leftIndex + rightIndex) / 2;

    vector[mid]->left = rebuildTree(vector, leftIndex, mid-1);
    vector[mid]->right = rebuildTree(vector, mid+1, rightIndex);
    return vector[mid];
}  

void finishExecution(BST *tree,  FILE *fp) {

    int contagem = 0;
    countNodes(tree->root, &contagem);

    int tamanho = contagem*sizeof(Task*);
    Task **vector = (Task**) malloc(tamanho);

    int index = 0;
    saveTreeInVector(tree->root, vector, &index);

    tree->root = rebuildTree(vector, 0, (int) (tamanho/sizeof(Task*))-1);

    for (index = 0; contagem < index; contagem++) {
        fprintf(fp,"%s\n", tree->root->name);
        fprintf(fp,"%d\n",tree->root->prioridade);
        fprintf(fp,"%d/%d\n",tree->root->entrega.day, tree->root->entrega.month);
    }

    free(vector);
    freeTree(tree);
}


int menu() {
    int op=0;
    puts("1 Inserir nova tarefa");
    puts("2 Deletar tarefa");
    puts("3 Atualizar tarefa");
    puts("4 Consultar tarefa");
    puts("5 Listar tarefas");
    printf("6 Finaliza\n");
    printf("\n: ");
    scanf("%d", &op);
    return op;
}


int main(int argc, char const *argv[]) {
    int op = 0;
    BST bst; 
    bst.root = NULL;
    FILE *fp = fopen(argv[1], "r");
    bst.root = initialLoad(bst.root, fp);


    while (op!=6) {

        op=menu();
        
        if (op==1) {
            insert(&bst); printf("\n");
        }
        else if (op==2) { 
            char key[50]; 
            puts("Tarefa a excluir: "); getchar();
            fgets(key, 50, stdin); strtok(key, "\n");
            bst.root = excluirTask(bst.root, key);  printf("\n");
        }
        else if (op==3) {
            char key[50];
            puts("Tarefa a modificar: "); getchar();
            fgets(key, 50, stdin); strtok(key, "\n");
            bst.root = updateTask(bst.root, key);  printf("\n");
        }
        else if (op==4) {
            char key[50];
            puts("Tarefa a procurar: "); getchar();
            fgets(key, 50, stdin); strtok(key, "\n");
            buscarTask(bst.root, key);  printf("\n");
        }
        else if (op==5) {
            inOrder(bst.root);  printf("\n");
        }

    }

    fclose(fp);
    fp = fopen(argv[1],"w");
    rewind(fp);

    finishExecution(bst.root,fp);
    fclose(fp);

    return 0;
}
