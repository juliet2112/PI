#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

typedef struct {
    char *data;
    int head;
    int tail;
    int size;
    int count;
} Queue;

void init_queue(Queue *q, int size) {
    q->data = malloc(size * sizeof(char));
    q->head = 0;
    q->tail = 0;
    q->size = size;
    q->count = 0;
}

void free_queue(Queue *q) {
    free(q->data);
}

void push(Queue *q, char c) {
    q->data[q->tail] = c;
    q->tail = (q->tail + 1) % q->size;
    if (q->count < q->size) {
        q->count++;
    } else {
        q->head = (q->head + 1) % q->size;  
    }
}

char pop(Queue *q) {
    char c = q->data[q->head];
    q->head = (q->head + 1) % q->size;
    q->count--;
    return c;
}

void set_raw_mode(struct termios *original) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, original);
    raw = *original;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void restore_terminal_mode(struct termios *original) {
    tcsetattr(STDIN_FILENO, TCSANOW, original);
}

int main() {
    int delay;
    printf("Podaj opóźnienie (długość kolejki): ");
    scanf("%d", &delay);
    getchar(); // usuń enter

    Queue q;
    init_queue(&q, delay);

    struct termios original;
    set_raw_mode(&original);

    printf("Podawaj znaki ('.' kończy):\n");

    while (1) {
        char ch = getchar();

        if (ch == '.') {
            break;
        }

        putchar(ch);           
        fflush(stdout);

        if (q.count == delay) {
            char out = pop(&q);   
            putchar(out);
            fflush(stdout);
        }

        push(&q, ch);         
    }

    restore_terminal_mode(&original);
    free_queue(&q);
    return 0;
}

