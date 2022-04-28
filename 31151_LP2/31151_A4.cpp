//Implement a solution for a constraint satisfaction problem using branch and bound and backtracking for n-queens problem or a graph coloring problem
#include<bits/stdc++.h>
using namespace std;
# define n 8

void printboard(int board[n][n]){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<board[i][j]<<"   ";
        }
        cout<<"\n";
    }
}
bool safe(int row,int col,int slashcode[n][n],int backslashcode[n][n],bool rowlookup[],bool slashcodelookup[],bool backslashcodelookup[]){
    if(slashcodelookup[slashcode[row][col]]||backslashcodelookup[backslashcode[row][col]]||rowlookup[row])
        return(false);
    return(true);
}
bool solveNQueensUtil(int board[n][n], int col,int slashCode[n][n], int backslashCode[n][n],bool rowLookup[n],bool slashCodeLookup[],bool backslashCodeLookup[] )
{
	
	if (col >= n)
		return true;


	for (int i = 0; i < n; i++)
	{
		
		if ( safe(i, col, slashCode,backslashCode, rowLookup,slashCodeLookup, backslashCodeLookup) )
		{
			board[i][col] = 1;
			rowLookup[i] = true;
			slashCodeLookup[slashCode[i][col]] = true;
			backslashCodeLookup[backslashCode[i][col]] = true;

			if (solveNQueensUtil(board, col + 1,slashCode, backslashCode,rowLookup, slashCodeLookup, backslashCodeLookup))
				return true;

		
			board[i][col] = 0;
			rowLookup[i] = false;
			slashCodeLookup[slashCode[i][col]] = false;
			backslashCodeLookup[backslashCode[i][col]] = false;
		}
	}	
	return false;
}
bool solveNQueens()
{
	int board[n][n];
	memset(board, 0, sizeof board);

	int slashCode[n][n];
	int backslashCode[n][n];

	
	bool rowLookup[n] = {false};

	bool slashCodeLookup[2*n - 1] = {false};
	bool backslashCodeLookup[2*n - 1] = {false};


	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++) {
		slashCode[r][c] = r + c,
			backslashCode[r][c] = r - c + 7;
		}

	if (solveNQueensUtil(board, 0,slashCode, backslashCode,rowLookup, slashCodeLookup, backslashCodeLookup) ==false )
	{
		cout << "Solution does not exist";
		return false;
	}

	// solution found
	printboard(board);
	return true;
}
int main(){
	solveNQueens();
	return 0;
}
/*
#include <iostream>
# include <string.h>
using namespace std;
#define N 8


void printSolution(int board[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << " "<< board[i][j];
		cout << "\n";
	}
}


bool isSafe(int row, int col, int slashCode[N][N],int backslashCode[N][N], bool rowLookup[],
	bool slashCodeLookup[], bool backslashCodeLookup[] )
{
    // C++ program to solve N Queen Problem using Branch and Bound 
	if (slashCodeLookup[slashCode[row][col]] ||backslashCodeLookup[backslashCode[row][col]] ||rowLookup[row])
	    return false;
	return true;
}


bool solveNQueensUtil(int board[N][N], int col,int slashCode[N][N], int backslashCode[N][N],bool rowLookup[N],
					    bool slashCodeLookup[],bool backslashCodeLookup[] )
{
	
	if (col >= N)
		return true;


	for (int i = 0; i < N; i++)
	{
		
		if ( isSafe(i, col, slashCode,backslashCode, rowLookup,slashCodeLookup, backslashCodeLookup) )
		{
			board[i][col] = 1;
			rowLookup[i] = true;
			slashCodeLookup[slashCode[i][col]] = true;
			backslashCodeLookup[backslashCode[i][col]] = true;

			if (solveNQueensUtil(board, col + 1,slashCode, backslashCode,rowLookup, slashCodeLookup, backslashCodeLookup))
				return true;

		
			board[i][col] = 0;
			rowLookup[i] = false;
			slashCodeLookup[slashCode[i][col]] = false;
			backslashCodeLookup[backslashCode[i][col]] = false;
		}
	}

	
	return false;
}

bool solveNQueens()
{
	int board[N][N];
	memset(board, 0, sizeof board);

	int slashCode[N][N];
	int backslashCode[N][N];

	
	bool rowLookup[N] = {false};

	bool slashCodeLookup[2*N - 1] = {false};
	bool backslashCodeLookup[2*N - 1] = {false};


	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++) {
		slashCode[r][c] = r + c,
			backslashCode[r][c] = r - c + 7;
		}

	if (solveNQueensUtil(board, 0,
						slashCode, backslashCode,
	rowLookup, slashCodeLookup, backslashCodeLookup) ==
												false )
	{
		cout << "Solution does not exist";
		return false;
	}

	// solution found
	printSolution(board);
	return true;
}


int main()
{
	solveNQueens();

	return 0;
}
*/
