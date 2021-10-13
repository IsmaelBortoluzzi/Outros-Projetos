#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct bebida {

   int code;
   char name[30];
   int volume;
   float price;
   int qtStock;
   int isAlcoholic; // 0 - nope, 1 - yep
   struct bebida *left, *right;

};
typedef struct bebida Bebida;
 
typedef struct {

   Bebida *root;

} BST;

Bebida *createNode(Bebida *newNode) {
    
    newNode = (Bebida*) malloc(sizeof(Bebida));
    
    printf("\nDigite o Codigo da Bebida: ");
    scanf("%d", &newNode->code);
    getchar();
    
    printf("Digite o nome da Bebida: ");
    fgets(newNode->name, 30, stdin);
    strtok(newNode->name, "\n");

    printf("Digite o volume da Bebida: ");
    scanf("%d", &newNode->volume);

    printf("Digite o preco da Bebida: R$");
    scanf("%f", &newNode->price);    

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &newNode->qtStock);

    printf("E alcoolica? s/n ");
    char condition; 
    getchar();
    scanf("%c", &condition);

    if (toupper(condition) == 'S') newNode->isAlcoholic = 1;
    else newNode->isAlcoholic = 0;

    newNode->left = newNode->right = NULL;

    return newNode;
}

Bebida *addBebida(Bebida *root, Bebida *bebida) {

    if(root==NULL) return bebida;

    if(root->code == bebida->code) {
        printf("Esta Bebida Ja Existe!\n");
        return root;
    }

    if(bebida->code > root->code) {

        root->right = addBebida(root->right, bebida);
    }
    else if (bebida->code < root->code) {

        root->left = addBebida(root->left, bebida);
    }
    return root;
}

void insert(BST *tree) {
    Bebida *newNode = NULL;

    newNode = createNode(newNode);
    tree->root = addBebida(tree->root, newNode);
}

void buscarBebida(Bebida *root, int key) {

    if (!root) {
        printf("Esta Bebida Nao Existe");
        return;
    }
    if(key > root->code) {

        buscarBebida(root->right, key);
    }
    else if (key < root->code) {

        buscarBebida(root->left, key);
    }
    else {
        printf("Codigo: %d, %s, %dml, R$%.2f, %d unidades, %d\n", root->code, root->name, root->volume, root->price, root->qtStock, root->isAlcoholic);
        return;
    }

}

Bebida* swap(Bebida* bebida, Bebida* sucessor) {

    bebida->code = sucessor->code;
    strcpy(bebida->name, sucessor->name);
    bebida->volume = sucessor->volume;
    bebida->price = sucessor->price;
    bebida->qtStock = sucessor->qtStock;
    bebida->isAlcoholic = sucessor->isAlcoholic;
    
    return bebida;
} 

Bebida* excluirBebida(Bebida *root, int key) {

    if (!root) {
        printf("Esta Bebida Nao Existe");
        return root;
    }

    if(key < root->code) {

        root->left = excluirBebida(root->left, key);
        return root;
    } 
    else if (key > root->code) {

        root->right = excluirBebida(root->right, key);
        return root;
    }
    
    //se não for maior nem menor, quer dizer que é igual

    if (!(root->left)) {

        Bebida *aux = root->right;
        free(root);
        return aux;
    } 
    else if(!(root->right)) {

        Bebida *aux = root->left;
        free(root);
        return aux;
    }
    else {  // Significa que o node tem um left e um right

        // Iremos achar o menor node da right subtree para poder fazer 
        //o swap com o node a ser excluido. Depois damos um free(menor)
        Bebida *paiSucessor = root; 

        Bebida *sucessor = root->right;
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

void inOrder(Bebida *root) {

    if (!root) return;

    inOrder(root->left);
    printf("Codigo: %d, %s, %dml, R$%.2f, %d unidades, %d\n", root->code, root->name, root->volume, root->price, root->qtStock, root->isAlcoholic);
    inOrder(root->right);
}

void preOrder(Bebida *root) {

    if (!root) return;

    printf("Codigo: %d, %s, %dml, R$%.2f, %d unidades, %d\n", root->code, root->name, root->volume, root->price, root->qtStock, root->isAlcoholic);
    preOrder(root->left);
    preOrder(root->right);
}

void delTree(Bebida *root) {

    if (!root) return;

    delTree(root->left);
    delTree(root->right);
    free(root);
    printf("-");
}

void comprarOuVenderBebida(Bebida *root, int key, int quant, char cv) {

    // cv = comprar ou vender

    if (!root) {
        printf("Bebida Nao Encontrada!\n");
        return;
    }
    if (key > root->code) {

        comprarOuVenderBebida(root->right, key, quant, cv);
    }
    else if (key < root->code) {

        comprarOuVenderBebida(root->left, key, quant, cv);
    }
    else {

        if (cv == 'c') {
            root->qtStock += quant;
            return;
        }

        else if (cv == 'v') {

            if (quant > root->qtStock) {
                printf("Existem apenas %d deste item no estoque!\n", root->qtStock);
                return;
            }
            root->qtStock -= quant;
        }
    }
}

void countNodes(Bebida *root, int *contagem) {

    if (!root) return;

    (*contagem)++;
    countNodes(root->left, contagem);
    countNodes(root->right, contagem);
}

void saveTreeInVector(Bebida* root, Bebida **vector, int *index) {

    if (!root) return;

    saveTreeInVector(root->left, vector, index);
    vector[(*index)] = root; (*index)++; 
    saveTreeInVector(root->right, vector, index);

}

Bebida *rebuildTree(Bebida **vector, int leftIndex, int rightIndex) {

    if(leftIndex > rightIndex) return NULL;

    int mid = (leftIndex + rightIndex) / 2;

    vector[mid]->left = rebuildTree(vector, leftIndex, mid-1);
    vector[mid]->right = rebuildTree(vector, mid+1, rightIndex);
    return vector[mid];
}  

void rebalanceTree(BST *tree) {

    int contagem = 0;
    countNodes(tree->root, &contagem);

    int tamanho = contagem*sizeof(Bebida*);
    Bebida **vector = (Bebida**) malloc(tamanho);

    contagem = 0; // reusando a var pro track do index
    saveTreeInVector(tree->root, vector, &contagem);

    tree->root = rebuildTree(vector, 0, (int) (tamanho/sizeof(Bebida*))-1);
    free(vector);
}

int main(void) {

    BST tree; tree.root = NULL;

    int option = -1, numInserts = 0;
    while(option) {

        puts("\nDigite 1 para cadastrar uma Bebida;");
        puts("Digite 2 para listar as Bebidas;");
        puts("Digite 3 para procurar por uma Bebida;");
        puts("Digite 4 para excluir uma Bebida;");
        puts("Digite 5 para comprar uma Bebida;");
        puts("Digite 6 para vender uma Bebida;");
        puts("Digite 0 para sair do sistema;");
        scanf("%d", &option);
        printf("\n");
        int cdg, quantidade, idade;

        switch (option) {

            case 1:
            
                insert(&tree);
                numInserts++;
                if(!(numInserts % 10)) rebalanceTree(&tree);
                break;
            
            case 2:
                
                inOrder(tree.root); break;
            
            case 3:
                
                printf("Digite o codigo da bebida que deseja procurar: ");
                scanf("%d",  &cdg);
                buscarBebida(tree.root, cdg);
                break;
            
            case 4:
                
                printf("Digite o codigo da bebida que deseja excluir: ");
                scanf("%d",  &cdg);
                tree.root = excluirBebida(tree.root, cdg);
                numInserts--;
                break;

            case 5:

                printf("Digite o codigo da bebida que deseja comprar: ");
                scanf("%d",  &cdg);
                printf("Digite a quantidade de bebida que deseja comprar: ");
                scanf("%d",  &quantidade);
                comprarOuVenderBebida(tree.root, cdg, quantidade, 'c');
                break;
            
            case 6:

                printf("Qual a idade? ");
                scanf("%d", &idade);
                if(idade < 18) {
                    puts("Sem gole por enquanto"); 
                    break;
                }
                
                printf("Digite o codigo da bebida que deseja vender: ");
                scanf("%d",  &cdg);
                printf("Digite a quantidade de bebida que deseja vender: ");
                scanf("%d",  &quantidade);
                comprarOuVenderBebida(tree.root, cdg, quantidade, 'v');
                break;
            
            case 0: break;

            default:
            
                puts("Opcao Invalida!!!");
                break;
        }
    }

    delTree(tree.root); tree.root = NULL;
    puts("\nSistema Desligando...");

    return 0;
}