// Christian Borges Porto - CC6N

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da árvore binária
typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um elemento na árvore
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }

    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }

    return raiz;
}

// Função para pesquisar um elemento na árvore
No* pesquisar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }

    if (valor < raiz->valor) {
        return pesquisar(raiz->esquerda, valor);
    } else {
        return pesquisar(raiz->direita, valor);
    }
}

// Função para encontrar o nó com o menor valor em uma árvore
No* encontrarMinimo(No* raiz) {
    No* atual = raiz;

    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }

    return atual;
}

// Função para excluir um elemento da árvore
No* excluir(No* raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = excluir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = excluir(raiz->direita, valor);
    } else {
        // Nó com um único filho ou sem filhos
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Nó com dois filhos: Obter o sucessor (menor nó na subárvore direita)
        No* temp = encontrarMinimo(raiz->direita);

        // Copiar o valor do sucessor para este nó
        raiz->valor = temp->valor;

        // Excluir o sucessor
        raiz->direita = excluir(raiz->direita, temp->valor);
    }

    return raiz;
}

// Função para imprimir a árvore em ordem (caminhamento central)
void imprimirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimirEmOrdem(raiz->direita);
    }
}

int main() {
    No* raiz = NULL;

    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("Árvore em ordem: ");
    imprimirEmOrdem(raiz);
    printf("\n");

    printf("Pesquisar 40: %s\n", pesquisar(raiz, 40) != NULL ? "Encontrado" : "Não encontrado");

    printf("Excluir 20\n");
    raiz = excluir(raiz, 20);
    printf("Árvore em ordem: ");
    imprimirEmOrdem(raiz);
    printf("\n");

    printf("Excluir 30\n");
    raiz = excluir(raiz, 30);
    printf("Árvore em ordem: ");
    imprimirEmOrdem(raiz);
    printf("\n");

    printf("Excluir 50\n");
    raiz = excluir(raiz, 50);
    printf("Árvore em ordem: ");
    imprimirEmOrdem(raiz);
    printf("\n");

    return 0;
}
