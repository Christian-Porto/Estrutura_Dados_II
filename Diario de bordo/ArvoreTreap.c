// Christian Borges Porto - CC6N

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Estrutura para um nó da Treap
typedef struct Node {
    int key;          // Chave usada para propriedade de árvore de busca
    int priority;     // Prioridade usada para propriedade de heap
    struct Node* left;
    struct Node* right;
} Node;

// Função para criar um novo nó com uma chave e prioridade aleatória
Node* newNode(int key) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = key;
    temp->priority = rand() % 100;  // Definir prioridade aleatória
    temp->left = temp->right = NULL;
    return temp;
}

// Rotação à direita
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Executar rotação
    x->right = y;
    y->left = T2;

    // Retornar nova raiz
    return x;
}

// Rotação à esquerda
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Executar rotação
    y->left = x;
    x->right = T2;

    // Retornar nova raiz
    return y;
}

// Função para inserir uma chave na Treap e manter as propriedades
Node* insert(Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    // Inserir chave na subárvore correta de acordo com a propriedade da árvore de busca
    if (key < root->key) {
        root->left = insert(root->left, key);

        // Verificar a propriedade da heap (prioridade) e realizar rotação à direita se necessário
        if (root->left != NULL && root->left->priority > root->priority)
            root = rotateRight(root);
    } else {
        root->right = insert(root->right, key);

        // Verificar a propriedade da heap (prioridade) e realizar rotação à esquerda se necessário
        if (root->right != NULL && root->right->priority > root->priority)
            root = rotateLeft(root);
    }

    return root;
}

int main() { }
