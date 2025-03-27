#include <iostream>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char AI = 'O';
const int SIZE = 3;
char board[SIZE][SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

void printBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool isMovesLeft() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

int evaluate() {
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            else if (board[row][0] == PLAYER) return -10;
        }
    }
    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            else if (board[0][col] == PLAYER) return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        else if (board[0][0] == PLAYER) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        else if (board[0][2] == PLAYER) return -10;
    }
    return 0;
}

int minimax(bool isMaximizing) {
    int score = evaluate();
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft()) return 0;

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = AI;
                    best = max(best, minimax(false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    best = min(best, minimax(true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void bestMove() {
    int bestVal = -1000, row = -1, col = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = AI;
                int moveVal = minimax(false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    row = i; col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[row][col] = AI;
}

void playerMove() {
    int row, col;
    while (true) {
        cout << "Enter your move (row and column: 1-3): ";
        cin >> row >> col;
        if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row - 1][col - 1] == ' ') {
            board[row - 1][col - 1] = PLAYER;
            break;
        } else {
            cout << "Invalid move, try again!\n";
        }
    }
}

int main() {
    cout << "Tic-Tac-Toe AI (You: X, AI: O)\n";
    printBoard();
    while (isMovesLeft() && evaluate() == 0) {
        playerMove();
        printBoard();
        if (!isMovesLeft() || evaluate() != 0) break;
        bestMove();
        printBoard();
    }
    int result = evaluate();
    if (result == 10) cout << "AI Wins!\n";
    else if (result == -10) cout << "You Win!\n";
    else cout << "It's a Draw!\n";
    return 0;
}