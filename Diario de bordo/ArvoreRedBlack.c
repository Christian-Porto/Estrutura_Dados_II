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

void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void rightRotate(RBNode **root, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}
