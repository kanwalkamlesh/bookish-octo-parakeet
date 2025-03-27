#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

#define N 9  // Sudoku grid size

// Function to check if placing num at board[row][col] is valid
bool isValid(int board[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) 
            return false;
    }
    
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
            cout << (board[i][j] ? to_string(board[i][j]) : " ") << " ";
            if (j == 8) cout << "|";
        }
        cout << endl;
    }
    cout << "-------------------------\n";
}

// Function to randomly fill a few numbers in the Sudoku grid
void fillRandomNumbers(int board[N][N], int count) {
    srand(time(0));
    int placed = 0;

    while (placed < count) {
        int row = rand() % 9;
        int col = rand() % 9;
        int num = (rand() % 9) + 1;

        if (board[row][col] == 0 && isValid(board, row, col, num)) {
            board[row][col] = num;
            placed++;
        }
    }
}

// Function to generate a Sudoku puzzle
void generateSudoku(int board[N][N], int numClues) {
    fillRandomNumbers(board, numClues);  // Fill with user-defined or random clues
}

// Main function
int main() {
    int sudoku[N][N] = {0};  // Start with an empty grid
    int choice, numClues;

    cout << "Choose an option:\n";
    cout << "1. Enter the number of clues manually\n";
    cout << "2. Generate a Sudoku puzzle automatically\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the number of clues (min: 17, max: 40): ";
        cin >> numClues;
        if (numClues < 17) numClues = 17;
        if (numClues > 40) numClues = 40;
    } else {
        srand(time(0));
        numClues = rand() % 24 + 17; // Random number of clues between 17 and 40
    }

    // Generate the Sudoku puzzle
    generateSudoku(sudoku, numClues);
    cout << "\nGenerated Sudoku Puzzle:\n";
    printBoard(sudoku);

    // Solve and print the solution
    cout << "\nSolving Sudoku...\n";
    if (solveSudoku(sudoku)) {
        cout << "Solved Sudoku:\n";
        printBoard(sudoku);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
