#ifndef LISTA_H
#define LISTA_H

#include "rejestry.h"

typedef struct Node {
    rekord *data;
    struct Node *next;
} Node;

typedef struct DNode {
    rekord *data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

Node *append(Node *head, rekord *r);
Node *insertAfter(Node *head, Node *afterNode, rekord *r);
Node *deleteNode(Node *head, Node *target);
void freeList(Node *head);
void saveToFile(Node *head);
Node *loadFromFile(Node *head);
void printFirst(Node *head);
Node *printNext(Node *current);
void editRecord(rekord *r);

#endif