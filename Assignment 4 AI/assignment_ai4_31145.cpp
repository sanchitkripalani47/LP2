// Branch and Bound approach to solve N-queen problem
#include <iostream>
#include<cstring>
using namespace std;

class Board {
    int n;
    bool **board;
    int **slashCode;
    int **backslashCode;
    bool *rowLookup;
    bool *slashCodeLookup;
    bool *backslashCodeLookup; 

public:
    Board(int n) {
        this->n = n;

        // This creates a dynamic array of pointers
        board = new bool* [n];

        // Create a row for every pointer
        for (int i=0; i<n; i++){
            board[i] = new bool[n];

            // Set all elements as false
            memset(board[i], false, n*sizeof(bool));
        }

        // Initialize the lookup tables
        rowLookup = new bool[n];
        for (int i=0; i<n; i++) rowLookup[i] = false;

        slashCodeLookup = new bool[2*n - 1];
        for (int i=0; i<n; i++) slashCodeLookup[i] = false;

        backslashCodeLookup = new bool[2*n - 1];
        for (int i=0; i<n; i++) backslashCodeLookup[i] = false;

        slashCode = new int*[n];
        backslashCode = new int*[n];

        // initialize helper matrices
        for (int r = 0; r < n; r++){
            slashCode[r] = new int[n];
            backslashCode[r] = new int[n];

            for (int c = 0; c < n; c++) {
                // memset(slashCode[r], r+c, n*sizeof(int)),
                slashCode[r][c] = r+c;
                backslashCode[r][c] = r - c + n -1;
                // memset(backslashCode[r], r - c + 7, n*sizeof(int));
            }
        }


        cout << "\nThe board size has been set to " << n << endl;
    }

    void printBoard() {
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                if (board[i][j]) {
                    cout << "Q ";
                }
                else {
                    cout << "_ ";
                }
            }
            cout << endl;
        }
    }

    // Function to check if the i,j th position is safe
    bool checkSafe(int i, int j){
        if (slashCodeLookup[slashCode[i][j]] ||
            backslashCodeLookup[backslashCode[i][j]] ||
            rowLookup[i])
        return false;

        return true;
    }

    bool soln(int j){
        if (j >= n) return true; 

        for (int row=0; row<n; row++){
            if (checkSafe(row, j)) {
                board[row][j] = true;
                rowLookup[row] = true;
                slashCodeLookup[slashCode[row][j]] = true;
                backslashCodeLookup[backslashCode[row][j]] = true;
                if (soln(j+1)) return true;

                board[row][j] = false;
                rowLookup[row] = false;
                slashCodeLookup[slashCode[row][j]] = false;
                backslashCodeLookup[backslashCode[row][j]] = false;
            }
        }
        return false;
    }

    void setN(int n){
        this->n = n;

        board = new bool* [n];

        // Create a row for every pointer
        for (int i=0; i<n; i++){
            board[i] = new bool[n];

            // Set all elements as false
            memset(board[i], false, n*sizeof(bool));
        }

        // Initialize the lookup tables
        rowLookup = new bool[n];
        for (int i=0; i<n; i++) rowLookup[i] = false;

        slashCodeLookup = new bool[2*n - 1];
        for (int i=0; i<n; i++) slashCodeLookup[i] = false;

        backslashCodeLookup = new bool[2*n - 1];
        for (int i=0; i<n; i++) backslashCodeLookup[i] = false;

        slashCode = new int*[n];
        backslashCode = new int*[n];

        // initialize helper matrices
        for (int r = 0; r < n; r++){
            slashCode[r] = new int[n];
            backslashCode[r] = new int[n];

            for (int c = 0; c < n; c++) {
                // memset(slashCode[r], r+c, n*sizeof(int)),
                slashCode[r][c] = r+c;
                backslashCode[r][c] = r - c + (n -1);
                // memset(backslashCode[r], r - c + 7, n*sizeof(int));
            }
        }
        
        cout << "\nThe new board size has been set to " << n << endl;
    }


};

int main() {
    int choice;
    bool flag = true;

    int n;
    cout << "\nEnter the size of board: ";
    cin >> n; 
    Board b1(n);

    while(flag){
        cout << "\nMENU:"
             << "\n1) Get the solution: " 
             << "\n2) Change the board size: " 
             << "\n3) Exit: " << endl;

        cout << "\nEnter your choice: ";
        cin  >> choice;
        switch (choice)
        {
        case 1:
        {
            bool ans = b1.soln(0);
            if (ans) {
                b1.printBoard();
            }
            else {
                cout << "\nNo solution found!!!" << endl;
            }
            break;
        }
        case 2:
        {
            int n;
            cout << "\nEnter the new board size: ";
            cin >> n;
            b1.setN(n);
            break;
        }
        case 3:
        {
            cout << "\nGoodbye!!!" << endl;
            flag=false; 
            break;
        }
        
        default:
            break;
        }
    }

    
    return 0;
}