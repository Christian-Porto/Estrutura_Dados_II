// Christian Borges Porto - CC6N

#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } NodeColor;

typedef struct RBNode {
    int data;
    NodeColor color;
    struct RBNode *left, *right, *parent;
} RBNode;

RBNode* createNode(int data) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED; // Novos nós são sempre vermelhos inicialmente
    node->left = node->right = node->parent = NULL;
    return node;
}
