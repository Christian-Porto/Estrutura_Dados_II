// Christian Borges Porto - CC6N

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore AVL
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Função para obter a altura de um nó
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Função para calcular o máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // Altura do novo nó é 1 (nó folha)
    return node;
}

// Função para fazer uma rotação à direita
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realizando a rotação
    x->right = y;
    y->left = T2;

    // Atualizando as alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // Nova raiz
}

// Função para fazer uma rotação à esquerda
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realizando a rotação
    y->left = x;
    x->right = T2;

    // Atualizando as alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // Nova raiz
}

// Função para obter o fator de balanceamento de um nó
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Função para inserir um nó na árvore AVL
Node* insertNode(Node* node, int data) {
    // Inserção normal de árvore binária de busca
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else // Não permite duplicatas
        return node;

    // Atualizando a altura do ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Verificando o fator de balanceamento
    int balance = getBalance(node);

    // Caso 1: Rotação à direita (desbalanceamento para a esquerda)
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Caso 2: Rotação à esquerda (desbalanceamento para a direita)
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Caso 3: Rotação à esquerda-direita
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso 4: Rotação à direita-esquerda
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Nenhuma rotação necessária
}

// Função para encontrar o nó com o menor valor em uma árvore
Node* minValueNode(Node* node) {
    Node* current = node;

    // Nó mais à esquerda
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Função para excluir um nó da árvore AVL
Node* deleteNode(Node* root, int data) {
    // Exclusão normal de árvore binária de busca
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Nó com apenas um filho ou nenhum
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            // Caso sem filhos
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // Um filho
                *root = *temp;

            free(temp);
        } else {
            // Nó com dois filhos: obter o sucessor em ordem
            Node* temp = minValueNode(root->right);

            // Copiar o valor do sucessor
            root->data = temp->data;

            // Excluir o sucessor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // Se a árvore tinha apenas um nó
    if (root == NULL)
        return root;

    // Atualizando a altura
    root->height = 1 + max(height(root->left), height(root->right));

    // Verificando o fator de balanceamento
    int balance = getBalance(root);

    // Caso 1: Rotação à direita
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Caso 2: Rotação à esquerda
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Caso 3: Rotação à esquerda-direita
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Caso 4: Rotação à direita-esquerda
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Função para pesquisar um elemento na árvore AVL
Node* searchNode(Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return searchNode(root->left, data);
    
    return searchNode(root->right, data);
}

// Função para imprimir a árvore AVL em ordem
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node* root = NULL;

    // Inserindo elementos na árvore AVL
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    printf("Árvore AVL em pre-ordem: ");
    preOrder(root);
    printf("\n");

    // Pesquisando um elemento
    int searchVal = 30;
    Node* foundNode = searchNode(root, searchVal);
    if (foundNode != NULL)
        printf("Elemento %d encontrado na árvore.\n", searchVal);
    else
        printf("Elemento %d não encontrado na árvore.\n", searchVal);

    // Excluindo um elemento
    root = deleteNode(root, 20);
    printf("Árvore AVL após a exclusão do valor 20: ");
    preOrder(root);
    printf("\n");

    return 0;
}
