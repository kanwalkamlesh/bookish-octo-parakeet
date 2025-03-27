#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 9  // Sudoku grid size

// Function to check if placing num at board[row][col] is valid
bool isValid(int board[N][N], int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) 
            return false;
    }
    
    // Check 3×3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == num) 
                return false;
        }
    }
    return true;
}

// Backtracking function to solve Sudoku
bool solveSudoku(int board[N][N]) {
    int row = -1, col = -1;
    bool emptyFound = false;
    
    for (int i = 0; i < N && !emptyFound; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                emptyFound = true;
                break;
            }
        }
    }

    if (!emptyFound) return true; // Sudoku solved

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board)) return true;
            board[row][col] = 0;  // Backtrack
        }
    }
    
    return false;
}

// Function to print the Sudoku board
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        if (i % 3 == 0) cout << "-------------------------\n";
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0) cout << "| ";
            cout << board[i][j] << " ";
            if (j == 8) cout << "|";
        }
        cout << endl;
    }
    cout << "-------------------------\n";
}

// Function to fill a 3×3 subgrid randomly
void fillBox(int board[N][N], int row, int col) {
    vector<int> numList = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    random_shuffle(numList.begin(), numList.end());

    int index = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[row + i][col + j] = numList[index++];
        }
    }
}

// Function to fill the diagonal 3×3 subgrids randomly
void fillDiagonal(int board[N][N]) {
    for (int i = 0; i < N; i += 3) {
        fillBox(board, i, i);
    }
}

// Function to generate a full valid Sudoku board
void generateSudoku(int board[N][N]) {
    fillDiagonal(board);
    solveSudoku(board);
}

// Function to remove numbers randomly to create a puzzle
void removeNumbers(int board[N][N], int numToRemove) {
    srand(time(0));
    int count = numToRemove;

    while (count > 0) {
        int i = rand() % 9;
        int j = rand() % 9;
        if (board[i][j] != 0) {
            board[i][j] = 0;
            count--;
        }
    }
}

// Main function
int main() {
    int sudoku[N][N] = {0};

    generateSudoku(sudoku);
    cout << "Generated Sudoku Puzzle:\n";
    printBoard(sudoku);

    removeNumbers(sudoku, 40);
    cout << "\nSudoku Puzzle after removing numbers:\n";
    printBoard(sudoku);

    cout << "\nSolving Sudoku...\n";
    if (solveSudoku(sudoku)) {
        cout << "Solved Sudoku:\n";
        printBoard(sudoku);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
