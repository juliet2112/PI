#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "drzewo.h"

Node* create(int key, char* word) {
    Node *new = (Node*)malloc(sizeof(Node));
    if (!new) {
        perror("Memory allocation error");
        return NULL;
    }
    new->key = key;
    strncpy(new->text, word, WORD_LEN - 1);
    new->text[WORD_LEN - 1] = '\0';
    new->left = new->right = new->parent = NULL;
    return new;
}

Node* insert(Node *root, int key, char *word) {
    if (!root) return create(key, word);

    if (key < root->key) {
        Node *left = insert(root->left, key, word);
        root->left = left;
        left->parent = root;
    } else {
        Node *right = insert(root->right, key, word);
        root->right = right;
        right->parent = root;
    }
    return root;
}

Node* min(Node *root) {
    while (root && root->left)
        root = root->left;
    return root;
}

Node* max(Node *root) {
    while (root && root->right)
        root = root->right;
    return root;
}

Node* find(Node *root, int x) {
    if (!root || root->key == x) return root;
    if (x < root->key) return find(root->left, x);
    return find(root->right, x);
}

Node* next(Node *node) {
    if (node->right) return min(node->right);
    Node *p = node->parent;
    while (p && node == p->right) {
        node = p;
        p = p->parent;
    }
    return p;
}

Node* prev(Node *node) {
    if (node->left) return max(node->left);
    Node *p = node->parent;
    while (p && node == p->left) {
        node = p;
        p = p->parent;
    }
    return p;
}

void show(Node *root) {
    if (!root) return;
    show(root->left);
    printf("%d: %s\n", root->key, root->text);
    show(root->right);
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void printTree(Node *root, int depth) {
    if (root == NULL) return;

    printTree(root->right, depth + 1);

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%d %s\n", root->key, root->text);

    printTree(root->left, depth + 1);
}

void rotateRight(Node **rootRef, Node *node) {
    Node *leftChild = node->left;
    if (!leftChild) return;

    node->left = leftChild->right;
    if (leftChild->right) leftChild->right->parent = node;

    leftChild->right = node;
    leftChild->parent = node->parent;

    if (node->parent) {
        if (node->parent->left == node)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;
    } else {
        *rootRef = leftChild;
    }

    node->parent = leftChild;
}

void rotacjaLewa(Node **rootRef, Node *node) {
    Node *rightChild = node->right;
    if (!rightChild) return;

    node->right = rightChild->left;
    if (rightChild->left) rightChild->left->parent = node;

    rightChild->left = node;
    rightChild->parent = node->parent;

    if (node->parent) {
        if (node->parent->left == node)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;
    } else {
        *rootRef = rightChild;
    }

    node->parent = rightChild;
}

int tworzListe(Node **rootRef) {
    Node *tmp = *rootRef;
    Node *prev = NULL;
    int size = 0;

    while (tmp != NULL) {
        if (tmp->left != NULL) {
            rotateRight(rootRef, tmp);
            tmp = (prev == NULL) ? *rootRef : prev->right;
        } else {
            prev = tmp;
            tmp = tmp->right;
            size++;
        }
    }
    return size;
}

void tworzDrzewo(Node **rootRef, int size) {
    int m = pow(2, floor(log2(size + 1))) - 1;
    Node *tmp = *rootRef;

    for (int i = 0; i < size - m; i++) {
        if (tmp && tmp->right != NULL) {
            rotacjaLewa(rootRef, tmp);
            tmp = tmp->right;
        } else {
            break;
        }
    }

    while (m > 1) {
        m /= 2;
        tmp = *rootRef;
        for (int i = 0; i < m; i++) {
            if (tmp && tmp->right != NULL) {
                rotacjaLewa(rootRef, tmp);
                tmp = tmp->right;
            } else {
                break;
            }
        }
    }
}

void balans(Node **rootRef) {
    int size = tworzListe(rootRef);
    tworzDrzewo(rootRef, size);
}
