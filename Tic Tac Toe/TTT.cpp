#include <iostream>
#include <vector>

using namespace std;

// Print board
void printBoard(const vector<vector<char>>& board) {
    cout << "  1 2 3" << endl; // Column numbers starting from 1
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << " "; // Row numbers starting from 1
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << '|'; // Column separators
        }
        cout << endl;
        if (i < 2) cout << "  -----" << endl; // Row separators
    }
    cout << endl;
}

// check win
bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// check draw
bool checkDraw(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

// Main game 
int main() 
{
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char currentPlayer = 'X';
    int row, col;
    bool gameOver = false;

    while (!gameOver) {
        printBoard(board);
        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        cin >> row >> col;

        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        board[row - 1][col - 1] = currentPlayer;

        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            cout << "Player " << currentPlayer << " wins!" << endl;
            gameOver = true;
        } else if (checkDraw(board)) {
            printBoard(board);
            cout << "The game is a draw!" << endl;
            gameOver = true;
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    return 0;
}
