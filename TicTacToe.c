#include <stdio.h>

#define LENGTH 4
#define WIDTH 4
#define DEPTH 4
#define NUM_PLAYERS 2
#define COUNT_WINNING_SEQUENCE 3
#define MAX_MOVES 64

char startGameChoice();

char continueGameChoice();

void printExitMessage();

void gameSequencePrompt();

void initializeBoard(char board[LENGTH][WIDTH][DEPTH]);

void printBoard(char board[LENGTH][WIDTH][DEPTH]);

void clearBuffer();

int isEmpty(char board[LENGTH][WIDTH][DEPTH],
            int length, int width, int depth);

void drawMove(char board[LENGTH][WIDTH][DEPTH],
              int playerTurn, int length, int width, int depth);

int checkColumns(char board[LENGTH][WIDTH][DEPTH]);

int checkRows(char board[LENGTH][WIDTH][DEPTH]);

int checkDiagonal(char board[LENGTH][WIDTH][DEPTH]);

int checkCubeDiagonal(char board[LENGTH][WIDTH][DEPTH]);

int checkDepthRows(char board[LENGTH][WIDTH][DEPTH]);

int checkHorizontalDiagonal(char board[LENGTH][WIDTH][DEPTH]);

int checkVerticalDiagonal(char board[LENGTH][WIDTH][DEPTH]);

void playGame(char board[LENGTH][WIDTH][DEPTH]);

enum players {
    X, O
};

enum sellStatus {
    TAKEN, EMPTY
};

enum gameResults {
    XWIN, OWIN, TIE
};

int main() {
    // board and choice declaration
    char playGameChoice;
    char board[LENGTH][WIDTH][DEPTH];
    // get start choice from user
    playGameChoice = startGameChoice();
    while (playGameChoice == 'y') {
        initializeBoard(board);
        playGame(board);
        playGameChoice = continueGameChoice();
    }
    printExitMessage();
    return 0;
}

/***********************************************************************
* function name: startGameChoice
* The Input: no input
* The output: no output
* The Function operation: gets the starting game choice from user
***********************************************************************/
char startGameChoice() {
    char choice;
    printf("Would you like to start? (y/n)\n");
    choice = getchar();
    getchar();
    return choice;
}

/***********************************************************************
* function name: continueGameChoice
* The Input: no input
* The output: no output
* The Function operation: gets the continue game choice from user
***********************************************************************/
char continueGameChoice() {
    char choice;
    printf("Would you like to continue? (y/n)\n");
    choice = getchar();
    getchar();
    return choice;

}

/***********************************************************************
* function name: printExitMessage
* The Input: no input
* The output: no output
* The Function operation: prints the exit message to user
***********************************************************************/
void printExitMessage() {
    printf("YEET");
}

/***********************************************************************
* function name: gameSequencePrompt
* The Input: no input
* The output: no output
* The Function operation: prints the sequence request
***********************************************************************/
void gameSequencePrompt() {
    printf("Please enter your game sequence.\n");
}

/***********************************************************************
* function name: initializeBoard
* The Input: char[][][] board
* The output: no output
* The Function operation: initializes board, puts '*' in every cell
***********************************************************************/
void initializeBoard(char board[LENGTH][WIDTH][DEPTH]) {
    for (int i = 0; i < LENGTH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            for (int k = 0; k < DEPTH; ++k) {
                board[i][j][k] = '*';
            }
        }
    }
}

/***********************************************************************
* function name: printBoard
* The Input: char[][][] board
* The output: no output
* The Function operation: print the board to user
***********************************************************************/
void printBoard(char board[LENGTH][WIDTH][DEPTH]) {
    for (int i = 0; i < LENGTH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            for (int k = 0; k < DEPTH; ++k) {
                printf("(%d %d %d) ", i, j, k);
            }
            for (int k = 0; k < DEPTH; ++k) {
                printf("%c ", board[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

/***********************************************************************
* function name: clearBuffer
* The Input: no input
* The output: no output
* The Function operation: clears buffer until the \n
***********************************************************************/
void clearBuffer() {
    while (getchar() != '\n');
}

/***********************************************************************
* function name: isEmpty
* The Input: board and indexes
* The output: int that indicates cell status
* The Function operation: returns is the cell is taken or empty
***********************************************************************/
int isEmpty(char board[LENGTH][WIDTH][DEPTH],
            int length, int width, int depth) {
    if (board[length][width][depth] != '*')
        return TAKEN;
    else
        return EMPTY;

}

/***********************************************************************
* function name: drawMove
* The Input: board, indexes, turn
* The output: no output
* The Function operation: draws a X/O on board according to players turn
***********************************************************************/
void drawMove(char board[LENGTH][WIDTH][DEPTH],
              int playerTurn, int length, int width, int depth) {
    if (playerTurn == X)
        board[length][width][depth] = 'X';
    else if (playerTurn == O)
        board[length][width][depth] = 'O';
}

/***********************************************************************
* function name: checkRows
* The Input: board
* The output: int the winner/tie
* The Function operation: check if in board there is a winning in rows sequence
* and return the result
***********************************************************************/
int checkRows(char board[LENGTH][WIDTH][DEPTH]) {
    // variable declaration, initialization.
    int counterX = 0, counterO = 0;
    for (int i = 0; i < LENGTH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            for (int k = 0; k < DEPTH - 1; ++k) {
                if (board[i][j][k] == 'X') {
                    if (board[i][j][k] == board[i][j][k + 1])
                        counterX++;
                } else if (board[i][j][k] == 'O') {
                    if (board[i][j][k] == board[i][j][k + 1])
                        counterO++;
                }
            }
            // check after row if there was a winning sequence
            if (counterX == COUNT_WINNING_SEQUENCE)
                return XWIN;
            else if (counterO == COUNT_WINNING_SEQUENCE)
                return OWIN;
            else {
                // in case of no winner reset the counter before next iteration
                counterO = 0;
                counterX = 0;
            }
        }
    }
    // end of for loop

    return TIE;
}

/***********************************************************************
* function name: checkColumns
* The Input: board
* The output: int the winner/tie
* The Function operation: check if in board there is a winning sequence in
* columns and return the result
***********************************************************************/
int checkColumns(char board[LENGTH][WIDTH][DEPTH]) {
    // variable declaration, initialization.
    int counterX = 0, counterO = 0;
    for (int i = 0; i < LENGTH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            for (int k = 0; k < DEPTH - 1; ++k) {
                if (board[i][k][j] == 'X') {
                    if (board[i][k][j] == board[i][k + 1][j])
                        counterX++;
                } else if (board[i][k][j] == 'O') {
                    if (board[i][k][j] == board[i][k + 1][j])
                        counterO++;
                }
            }
            // check after column if there was a winning sequence
            if (counterX == COUNT_WINNING_SEQUENCE)
                return XWIN;
            else if (counterO == COUNT_WINNING_SEQUENCE)
                return OWIN;
            else {
                // in case of no winner reset the counter before next iteration
                counterO = 0;
                counterX = 0;
            }
        }
    }
    // end of for loop

    return TIE;
}

/***********************************************************************
* function name: checkDiagonal
* The Input: board
* The output: int the winner/tie
* The Function operation: check if in board there is a winning in diagonal
* sequence and return the result
***********************************************************************/
int checkDiagonal(char board[LENGTH][WIDTH][DEPTH]) {
    // variable declaration, initialization.
    int counterX = 0, counterO = 0;
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH - 1; ++j) {
            if (board[i][j][j] == 'X') {
                if (board[i][j][j] == board[i][j + 1][j + 1])
                    counterX++;
            } else if (board[i][j][j] == 'O') {
                if (board[i][j][j] == board[i][j + 1][j + 1])
                    counterO++;
            }

        }
        // check after diagonal if there was a winning sequence
        if (counterX == COUNT_WINNING_SEQUENCE)
            return XWIN;
        else if (counterO == COUNT_WINNING_SEQUENCE)
            return OWIN;
        else {
            // in case of no winner reset the counter before next iteration
            counterX = 0;
            counterO = 0;
        }
    }
    // end of for loop

    // check the second diagonal of every board
    for (int i = 0; i < LENGTH; ++i) {
        for (int j = WIDTH - 1, k = 0; j > 0; --j, k++) {
            if (board[i][k][j] == 'X') {
                if (board[i][k][j] == board[i][k + 1][j - 1])
                    counterX++;
            } else if (board[i][k][j] == 'O') {
                if (board[i][k][j] == board[i][k + 1][j - 1])
                    counterO++;
            }

        }
        // check after diagonal if there was a winning sequence
        if (counterX == COUNT_WINNING_SEQUENCE)
            return XWIN;
        else if (counterO == COUNT_WINNING_SEQUENCE)
            return OWIN;
        else {
            // in case of no winner reset the counter before next iteration
            counterX = 0;
            counterO = 0;
        }
    }
    // end of for loop

    return TIE;
}

/***********************************************************************
* function name: checkCubeDiagonal
* The Input: board
* The output: int the winner/tie
* The Function operation: check if in board there is a winning in cube diagonal
* sequence and return the result
***********************************************************************/
int checkCubeDiagonal(char board[LENGTH][WIDTH][DEPTH]) {
    // variable declaration, initialization.
    int counterX = 0, counterO = 0;
    for (int i = 0; i < LENGTH - 1; ++i) {
        if (board[i][i][i] == 'X') {
            if (board[i][i][i] == board[i + 1][i + 1][i + 1])
                counterX++;
        } else if (board[i][i][i] == 'O') {
            if (board[i][i][i] == board[i + 1][i + 1][i + 1])
                counterO++;
        }
    }
    // check after cube diagonal if there was a winning sequence
    if (counterX == COUNT_WINNING_SEQUENCE)
        return XWIN;
    else if (counterO == COUNT_WINNING_SEQUENCE)
        return OWIN;
    else {
        // in case of no winner reset the counter before next diagonal check
        counterX = 0;
        counterO = 0;
    }

    for (int i = LENGTH - 1, j = 0; i > 0; --i, ++j) {
        if (board[j][j][i] == 'X') {
            if (board[j][j][i] == board[j + 1][j + 1][i - 1])
                counterX++;
        } else if (board[j][j][i] == 'O') {
            if (board[j][j][i] == board[j + 1][j + 1][i - 1])
                counterO++;
        }
    }
    // check after cube diagonal if there was a winning sequence
    if (counterX == COUNT_WINNING_SEQUENCE)
        return XWIN;
    else if (counterO == COUNT_WINNING_SEQUENCE)
        return OWIN;
    else {
        // in case of no winner reset the counter before next diagonal check
        counterX = 0;
        counterO = 0;
    }

    for (int i = LENGTH - 1, j = 0; i > 0; --i, ++j) {
        if (board[i][j][j] == 'X') {
            if (board[i][j][j] == board[i - 1][j + 1][j + 1])
                counterX++;
        } else if (board[i][j][j] == 'O') {
            if (board[i][j][j] == board[i - 1][j + 1][j + 1])
                counterO++;
        }

    }
    // check after cube diagonal if there was a winning sequence
    if (counterX == COUNT_WINNING_SEQUENCE)
        return XWIN;
    else if (counterO == COUNT_WINNING_SEQUENCE)
        return OWIN;
    else {
        // in case of no winner reset the counter before next diagonal check
        counterX = 0;
        counterO = 0;
    }

    for (int i = LENGTH - 1, j = 0; i > 0; --i, ++j) {
        if (board[i][j][i] == 'X') {
            if (board[i][j][i] == board[i - 1][j + 1][i - 1])
                counterX++;
        } else if (board[i][j][i] == 'O') {
            if (board[i][j][i] == board[i - 1][j + 1][i - 1])
                counterO++;
        }

    }
    // check after cube diagonal if there was a winning sequence
    if (counterX == COUNT_WINNING_SEQUENCE)
        return XWIN;
    else if (counterO == COUNT_WINNING_SEQUENCE)
        return OWIN;
    else
        // there wasn't a winner on any cube diagonal
        return TIE;
}

/***********************************************************************
* function name: checkDepthRows
* The Input: board
* The output: int the winner/tie
* The Function operation: check if in board there is a winning in depth rows
* sequence and return the result
***********************************************************************/
int checkDepthRows(char board[LENGTH][WIDTH][DEPTH]) {
    // variable declaration, initialization.
    int counterX = 0, counterO = 0;
    for (int i = 0; i < LENGTH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            for (int k = 0; k < DEPTH - 1; ++k) {
                if (board[k][j][i] == 'X') {
                    if (board[k][j][i] == board[k + 1][j][i])
                        counterX++;
                } else if (board[k][j][i] == 'O') {
                    if (board[k][j][i] == board[k + 1][j][i])
                        counterO++;
                }
            }
            // check after depth row if there was a winning sequence
            if (counterX == COUNT_WINNING_SEQUENCE)
                return XWIN;
            else if (counterO == COUNT_WINNING_SEQUENCE)
                return OWIN;
            else {
                // in case of no winner reset the counter before next iteration
                counterX = 0;
                counterO = 0;
            }
        }
    }
    // end of for loop

    return TIE;
}

/***********************************************************************
* function name: checkHorizontalDiagonal
* The Input: board
* The output: int the winner/tie
* The Function operation: check if in board there is a winning in Horizontal
* Diagonal sequence and return the result
***********************************************************************/
int checkHorizontalDiagonal(char board[LENGTH][WIDTH][DEPTH]) {
    int counterX = 0, counterO = 0;
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH - 1; ++j) {
            if (board[j][j][i] == 'X') {
                if (board[j][j][i] == board[j + 1][j + 1][i])
                    counterX++;
            } else if (board[j][j][i] == 'O') {
                if (board[j][j][i] == board[j + 1][j + 1][i])
                    counterO++;
            }

        }
        if (counterX == 3) return XWIN;
        else if (counterO == 3) return OWIN;
        else {
            counterX = 0;
            counterO = 0;
        }
    }

    for (int i = 0; i < LENGTH; i++) {
        for (int j = WIDTH - 1, k = 0; j > 0; --j, ++k) {
            if (board[j][k][i] == 'X') {
                if (board[j][k][i] == board[j - 1][k + 1][i])
                    counterX++;
            } else if (board[j][k][i] == 'O') {
                if (board[j][k][i] == board[j - 1][k + 1][i])
                    counterO++;
            }
        }
        if (counterX == 3) return XWIN;
        else if (counterO == 3) return OWIN;
        else {
            counterX = 0;
            counterO = 0;
        }
    }
    return TIE;

}

/***********************************************************************
* function name: checkVerticalDiagonal
* The Input: board
* The output: int the winner/tie
* The Function operation: check if in board there is a winning in Vertical
* Diagonal sequence and return the result
***********************************************************************/
int checkVerticalDiagonal(char board[LENGTH][WIDTH][DEPTH]) {
    int counterX = 0, counterO = 0;
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH - 1; ++j) {
            if (board[j][i][j] == 'X') {
                if (board[j][i][j] == board[j + 1][i][j + 1])
                    counterX++;
            } else if (board[j][i][j] == 'O') {
                if (board[j][i][j] == board[j + 1][i][j + 1])
                    counterO++;
            }

        }
        if (counterX == 3) return XWIN;
        else if (counterO == 3) return OWIN;
        else {
            counterX = 0;
            counterO = 0;
        }
    }

    for (int i = 0; i < LENGTH; i++) {
        for (int j = WIDTH - 1, k = 0; j > 0; --j, ++k) {
            if (board[j][i][k] == 'X') {
                if (board[j][i][k] == board[j - 1][i][k + 1])
                    counterX++;
            } else if (board[j][i][k] == 'O') {
                if (board[j][i][k] == board[j - 1][i][k + 1])
                    counterO++;
            }

        }
        if (counterX == 3) return XWIN;
        else if (counterO == 3) return OWIN;
        else {
            counterX = 0;
            counterO = 0;
        }
    }
    return TIE;
}


/***********************************************************************
* function name: playGame
* The Input: board[][][]
* The output: no output
* The Function operation: plays the game does all the checks and prints the
* board and the game result
***********************************************************************/
void playGame(char board[LENGTH][WIDTH][DEPTH]) {
    // variable declaration, initialization.
    int rowMove, columnMove, tubeMove, turnCounter = 0;
    int rowsWinner, columnsWinner, diagonalWinner, cubeDiagonalWinner,
            depthRowsWinner, horizontalDiagonalWinner, verticalDiagonalWinner;
    char nextChar;
    // prints game prompt to user
    gameSequencePrompt();
    do {
        // gets a single move from buffer
        scanf("%d %d %d", &rowMove, &columnMove, &tubeMove);
        // checks is input invalid
        if ((rowMove >= LENGTH || rowMove < 0) ||
            (columnMove >= WIDTH || columnMove < 0) ||
            (tubeMove >= DEPTH || tubeMove < 0)) {
            printf("Input incorrect.\n");
            clearBuffer();
            return;
        } else if (!isEmpty(board, rowMove,
                            columnMove, tubeMove)) {
            printf("Input incorrect.\n");
            clearBuffer();
            return;
        } else
            // the input is valid - draw move by players turn
            drawMove(board, (turnCounter % NUM_PLAYERS),
                     rowMove, columnMove, tubeMove);

        // check for winning sequence in rows
        rowsWinner = checkRows(board);
        // check for winning sequence columns
        columnsWinner = checkColumns(board);
        // check for winning sequence diagonal
        diagonalWinner = checkDiagonal(board);
        // check for winning sequence cube diagonal
        cubeDiagonalWinner = checkCubeDiagonal(board);
        // check for winning sequence in depth rows
        depthRowsWinner = checkDepthRows(board);
        // check for winning sequence in horizontal diagonal
        horizontalDiagonalWinner = checkHorizontalDiagonal(board);
        // check for winning sequence in vertical diagonal
        verticalDiagonalWinner = checkVerticalDiagonal(board);

        nextChar = getchar();
        // check if there was a win of X after all the checks
        if (rowsWinner == XWIN || columnsWinner == XWIN ||
            diagonalWinner == XWIN || cubeDiagonalWinner == XWIN ||
            depthRowsWinner == XWIN || horizontalDiagonalWinner == XWIN ||
            verticalDiagonalWinner == XWIN) {
            printf("X is the winner.\n");
            if (nextChar != '\n')
                clearBuffer();
            break;
        }
            // check if there was a win of O after all the checks
        else if (rowsWinner == OWIN || columnsWinner == OWIN ||
                 diagonalWinner == OWIN || cubeDiagonalWinner == OWIN ||
                 depthRowsWinner == OWIN || horizontalDiagonalWinner == OWIN ||
                 verticalDiagonalWinner == OWIN) {
            printf("O is the winner.\n");
            if (nextChar != '\n')
                clearBuffer();
            break;
        }
        turnCounter++;
    } while (nextChar != '\n' && turnCounter < MAX_MOVES);
    // if all the options are tie - the result of game is tie
    if (rowsWinner == TIE && columnsWinner == TIE && diagonalWinner == TIE &&
        cubeDiagonalWinner == TIE && depthRowsWinner == TIE &&
        horizontalDiagonalWinner == TIE &&
        verticalDiagonalWinner == TIE) {
        printf("Tie.\n");
        clearBuffer();
    }
    // print the board
    printBoard(board);
}
