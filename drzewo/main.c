#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "drzewo.h"

enum Command {
    CNUM,
    CSHOW,
    CMIN,
    CMAX,
    CFIND,
    CNEXT,
    CPREV,
    CBALANS,
    CNONE,
    CEND
};

int isNumber(char *s) {
    for (int i = 0; s[i]; i++)
        if (!isdigit(s[i])) return 0;
    return 1;
}

enum Command parse(char *input) {
    if (isNumber(input)) return CNUM;
    if (strcmp(input, "SHOW") == 0) return CSHOW;
    if (strcmp(input, "MIN") == 0) return CMIN;
    if (strcmp(input, "MAX") == 0) return CMAX;
    if (strcmp(input, "FIND") == 0) return CFIND;
    if (strcmp(input, "NEXT") == 0) return CNEXT;
    if (strcmp(input, "PREV") == 0) return CPREV;
    if (strcmp(input, "BALANS") == 0) return CBALANS;
    if (strcmp(input, "END") == 0) return CEND;
    return CNONE;
}

int main() {
    Node *root = NULL;
    char input[WORD_LEN];

    while (1) {
        printf("\nEnter a number or command (SHOW, MIN, MAX, FIND, NEXT, PREV, BALANS, END): ");
        scanf("%s", input);
        enum Command cmd = parse(input);

        if (cmd == CEND) break;

        switch (cmd) {
            case CNUM: {
                int key = atoi(input);
                char word[WORD_LEN];
                printf("Enter word for key %d: ", key);
                scanf("%s", word);
                root = insert(root, key, word);
                break;
            }
            case CSHOW:
                printf("\nTree structure:\n");
                printTree(root, 0);
                break;

            case CMIN: {
                Node *m = min(root);
                if (m) printf("Min: %d -> %s\n", m->key, m->text);
                else printf("Tree is empty.\n");
                break;
            }

            case CMAX: {
                Node *m = max(root);
                if (m) printf("Max: %d -> %s\n", m->key, m->text);
                else printf("Tree is empty.\n");
                break;
            }

            case CFIND: {
                int key;
                printf("Enter key to find: ");
                scanf("%d", &key);
                Node *f = find(root, key);
                if (f) printf("Found: %d -> %s\n", f->key, f->text);
                else printf("Key not found.\n");
                break;
            }

            case CNEXT: {
                int key;
                printf("Enter key to find next: ");
                scanf("%d", &key);
                Node *f = find(root, key);
                if (f) {
                    Node *n = next(f);
                    if (n) printf("Next: %d -> %s\n", n->key, n->text);
                    else printf("No next node.\n");
                } else {
                    printf("Key not found.\n");
                }
                break;
            }

            case CPREV: {
                int key;
                printf("Enter key to find previous: ");
                scanf("%d", &key);
                Node *f = find(root, key);
                if (f) {
                    Node *p = prev(f);
                    if (p) printf("Prev: %d -> %s\n", p->key, p->text);
                    else printf("No previous node.\n");
                } else {
                    printf("Key not found.\n");
                }
                break;
            }

            case CBALANS:
                balans(&root);
                printf("Drzewo zbalansowane algorytmem DSW.\n");
                break;

            default:
                printf("Unknown command.\n");
        }
    }

    freeTree(root);
    return 0;
}
