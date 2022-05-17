#include<iostream>
#define N 4
using namespace std;

// Print the board
void printSolution(int board[N][N]){
    cout << "\nThe final solution is: " << endl;

    for (int i=0; i<N; i++){
        for (int j=0;j<N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool isSafe(int board[N][N], int row, int col){

    int i, j;
    // check if present in the current row
    for (j=0; j<col; j++){
        if (board[row][j]) return false;
    }

    // upper left diagonal
    for (i=row,j=col; i>=0 && j>=0; i--, j--){
        if (board[i][j]) return false;
    }

    // lower left diagonal
    for (i=row,j=col; i<N && j>=0; i++, j--){
        if (board[i][j]) return false;
    }

    return true;
}

bool sol(int board[N][N], int col) {
    if (col >= N) return true;

    for (int i=0; i<N; i++){
        if (isSafe(board, i, col)) {
            board[i][col] = 1;

            if (sol(board, col+1)){
                return true;
            } 

            board[i][col] = 0; 
        }
    }

    return false;
}

bool NQ() {
    int board[N][N] = {{0,0,0,0},
                       {0,0,0,0},
                       {0,0,0,0},
                       {0,0,0,0}};

    if (!sol(board, 0)){  
        cout << "\nNo solution possible!!!";
        return false;
    } 

    printSolution(board);
    return true;
}


int main() {
    NQ();
    return 0;
}