#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

char playerSymbol = 'X';  // Default player symbol
char AISymbol = 'O';      // Default AI symbol

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----------\n");
    }
    printf("\n");
}

bool isMoveValid(int row, int col) {
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
}

char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0]; // Check rows
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i]; // Check columns
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0]; // Check main diagonal
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2]; // Check anti-diagonal
    return ' ';
}

void convertInput(char input[], int *row, int *col) {
    *col = input[0] - 'A'; // 'A' -> column 0, 'B' -> column 1, 'C' -> column 2
    *row = input[1] - '1'; // '1' -> row 0, '2' -> row 1, '3' -> row 2
}

void playerMove() {
    char input[3];
    int row, col;
    while (true) {
        printf("Enter your move (A1, B2, C3, etc.): ");
        scanf("%2s", input);

        // Validate the input
        if (input[0] < 'A' || input[0] > 'C' || input[1] < '1' || input[1] > '3') {
            printf("Invalid input. Please enter a valid move (A1, B2, C3, etc.).\n");
            continue;
        }

        convertInput(input, &row, &col);
        if (isMoveValid(row, col)) {
            printf("\nCHAR BOARD GETS ACCESSED\n");
            printf("%c ADDED TO [%d][%d]\n\n", playerSymbol, row, col);
            board[row][col] = playerSymbol;
            break;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}

void AIMove() {
    int row, col;
    while (true) {
        row = rand() % 3;
        col = rand() % 3;
        if (isMoveValid(row, col)) {
            printf("AI TURN:\n\n");
            printf("%c ADDED TO [%d][%d]\n\n", AISymbol, row, col);
            board[row][col] = AISymbol;
            break;
        }
    }
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return false; // If any empty space exists, board is not full
        }
    }
    return true;
}

void selectSymbol() {
    char choice;
    while (true) {
        printf("Do you want to play as X or O? (Enter X or O): ");
        scanf(" %c", &choice); // ' ' to consume the leftover newline character
        if (choice == 'X' || choice == 'x') {
            playerSymbol = 'X';
            AISymbol = 'O';
            break;
        } else if (choice == 'O' || choice == 'o') {
            playerSymbol = 'O';
            AISymbol = 'X';
            break;
        } else {
            printf("Invalid choice. Please choose 'X' or 'O'.\n");
        }
    }
}

int main() {
    srand(time(NULL));
    char winner = ' ';

    // Ask the player to select their symbol
    selectSymbol();

    while (true) {
        printBoard();
        playerMove();
        winner = checkWinner();
        if (winner != ' ') {
            printBoard();
            printf("Player %c wins!\n", winner);
            break;
        }
        if (isBoardFull()) {
            printBoard();
            printf("The game is a tie!\n");
            break;
        }

        printBoard();
        AIMove();
        winner = checkWinner();
        if (winner != ' ') {
            printBoard();
            printf("Player %c wins!\n", winner);
            break;
        }
        if (isBoardFull()) {
            printBoard();
            printf("The game is a tie!\n");
            break;
        }
    }

    return 0;
}
