#include <stdio.h>
#include "hetmani.h"

int main() {
    int board[SIZE][SIZE] = {0};

    if (solve_n_queens(board, 0)) {
        printf("Rozwiązanie znalezione:\n");
        print_board(board);
    } else {
        printf("Brak rozwiązania.\n");
    }

    return 0;
}