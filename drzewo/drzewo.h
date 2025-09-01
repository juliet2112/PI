#ifndef DRZEWO_H
#define DRZEWO_H

#define WORD_LEN 100

typedef struct Node {
    int key;
    char text[WORD_LEN];
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

Node* create(int key, char* word);
Node* insert(Node *root, int key, char *word);
Node* min(Node *root);
Node* max(Node *root);
Node* find(Node *root, int x);
Node* next(Node *node);
Node* prev(Node *node);
void show(Node *root);
void freeTree(Node *root);
void printTree(Node *root, int depth);
void rotateRight(Node **rootRef, Node *node);
void rotacjaLewa(Node **rootRef, Node *node);
int tworzListe(Node **rootRef);
void tworzDrzewo(Node **rootRef, int size);
void balans(Node **rootRef);

#endif
