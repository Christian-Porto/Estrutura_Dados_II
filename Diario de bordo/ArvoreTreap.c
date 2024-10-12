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

// Função para deletar uma chave da Treap
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    // Procurar a chave a ser removida
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Se a chave for encontrada
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            // Se o nó tiver ambos os filhos, realizar rotações
            if (root->left->priority > root->right->priority) {
                root = rotateRight(root);
                root->right = deleteNode(root->right, key);
            } else {
                root = rotateLeft(root);
                root->left = deleteNode(root->left, key);
            }
        }
    }
    return root;
}

// Função para impressão em ordem da Treap (in-order traversal)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("Key: %d | Priority: %d\n", root->key, root->priority);
        inorder(root->right);
    }
}

// Função principal
int main() {
    Node* root = NULL;

    // Inserção de nós na Treap
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Treap após inserções:\n");
    inorder(root);

    // Remover nós
    root = deleteNode(root, 20);
    root = deleteNode(root, 30);

    printf("\nTreap após remoções:\n");
    inorder(root);

    return 0;
}
