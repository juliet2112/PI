#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Node *append(Node *head, rekord *r) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = malloc(sizeof(rekord));
    *(newNode->data) = *r;
    newNode->next = NULL;

    if (!head) return newNode;

    Node *temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

Node *insertAfter(Node *head, Node *afterNode, rekord *r) {
    if (!afterNode) return append(head, r);

    Node *newNode = malloc(sizeof(Node));
    newNode->data = malloc(sizeof(rekord));
    *(newNode->data) = *r;
    newNode->next = afterNode->next;
    afterNode->next = newNode;

    return head;
}

Node *deleteNode(Node *head, Node *target) {
    if (!head || !target) return head;
    if (head == target) {
        Node *temp = head->next;
        free(target->data);
        free(target);
        return temp;
    }

    Node *prev = head;
    while (prev->next && prev->next != target) prev = prev->next;
    if (prev->next) {
        prev->next = target->next;
        free(target->data);
        free(target);
    }
    return head;
}

void freeList(Node *head) {
    while (head) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

void saveToFile(Node *head) {
    FILE *file = fopen(FILE_NAME, "wb");
    if (!file) return;

    Node *temp = head;
    while (temp) {
        fwrite(temp->data, sizeof(rekord), 1, file);
        temp = temp->next;
    }
    fclose(file);
}

Node *loadFromFile(Node *head) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) return head;

    rekord r;
    while (fread(&r, sizeof(rekord), 1, file)) {
        head = append(head, &r);
    }
    fclose(file);
    return head;
}

void printFirst(Node *head) {
    if (head && head->data) showRecord(head->data);
}

Node *printNext(Node *current) {
    if (current && current->next) {
        showRecord(current->next->data);
        return current->next;
    }
    printf("Brak kolejnego elementu.\n");
    return current;
}

void editRecord(rekord *r) {
    printf("Obecna cena: %.2f PLN\n", r->price);
    printf("Nowa cena: ");
    scanf("%f", &r->price);
}