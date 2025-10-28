#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];

void resetBoard();
void printBoard();
int checkWinner();
int isFull();
void playerMove(char mark);
void aiMoveEasy(char mark);
void aiMoveHard(char mark);
int evaluate();
int minimax(int depth, int isMax);
void twoPlayerMode();
void aiMode();

int main() {
    int choice, playAgain;
    do {
        printf("\n====================================\n");
        printf("       TIC TAC TOE GAME IN C        \n");
        printf("====================================\n\n");
        printf("Choose Mode:\n");
        printf("1. Player vs Player\n");
        printf("2. Player vs AI\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            twoPlayerMode();
        else if (choice == 2)
            aiMode();
        else
            printf("Invalid choice.\n");

        printf("\nDo you want to play again? (1 = Yes, 0 = No): ");
        scanf("%d", &playAgain);

    } while (playAgain == 1);

    printf("\nThanks for playing! Goodbye!\n");
    return 0;
}

void resetBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard() {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

int checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return 1;
    return 0;
}

int isFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void playerMove(char mark) {
    int row, col;
    while (1) {
        printf("Enter row and column (1-3 each): ");
        scanf("%d %d", &row, &col);
        row--; col--;
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = mark;
            break;
        } else {
            printf("Invalid move! Try again.\n");
        }
    }
}

void aiMoveEasy(char mark) {
    int row, col;
    srand(time(0));
    while (1) {
        row = rand() % 3;
        col = rand() % 3;
        if (board[row][col] == ' ') {
            board[row][col] = mark;
            printf("AI placed %c at (%d, %d)\n", mark, row + 1, col + 1);
            break;
        }
    }
}

int evaluate() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == 'O') return +10;
            else if (board[i][0] == 'X') return -10;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == 'O') return +10;
            else if (board[0][i] == 'X') return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'O') return +10;
        else if (board[0][0] == 'X') return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'O') return +10;
        else if (board[0][2] == 'X') return -10;
    }
    return 0;
}

int minimax(int depth, int isMax) {
    int score = evaluate();
    if (score == 10 || score == -10)
        return score;
    if (isFull())
        return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int val = minimax(depth + 1, 0);
                    if (val > best) best = val;
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int val = minimax(depth + 1, 1);
                    if (val < best) best = val;
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void aiMoveHard(char mark) {
    int bestVal = -1000, bestRow = -1, bestCol = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = mark;
                int moveVal = minimax(0, 0);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[bestRow][bestCol] = mark;
    printf("AI placed %c at (%d, %d)\n", mark, bestRow + 1, bestCol + 1);
}

void twoPlayerMode() {
    char player1 = 'X', player2 = 'O';
    resetBoard();
    int turn = 0;
    printf("\nYou chose Player vs Player mode!\n");
    while (1) {
        printBoard();
        if (turn % 2 == 0) {
            printf("Player 1 (X):\n");
            playerMove(player1);
        } else {
            printf("Player 2 (O):\n");
            playerMove(player2);
        }
        if (checkWinner()) {
            printBoard();
            if (turn % 2 == 0)
                printf("Player 1 (X) wins!\n");
            else
                printf("Player 2 (O) wins!\n");
            break;
        }
        if (isFull()) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }
        turn++;
    }
}

void aiMode() {
    char player = 'X', ai = 'O';
    int level;
    resetBoard();
    int turn = 0;
    printf("\nYou chose Player vs AI mode!\n");
    printf("Select AI difficulty:\n1. Easy\n2. Hard\nEnter choice: ");
    scanf("%d", &level);

    while (1) {
        printBoard();
        if (turn % 2 == 0) {
            printf("Your Turn (X):\n");
            playerMove(player);
        } else {
            if (level == 1)
                aiMoveEasy(ai);
            else
                aiMoveHard(ai);
        }
        if (checkWinner()) {
            printBoard();
            if (turn % 2 == 0)
                printf("You win!\n");
            else
                printf("AI wins!\n");
            break;
        }
        if (isFull()) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }
        turn++;
    }
}
