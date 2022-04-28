// Name: Sanchit Kripalani
// Batch: M1
// Roll no: 31145

// Problem Statement: Implement A* algorithm for any game search problem

#include <iostream>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <stack>
#include <set>
using namespace std;

// Define the size of grid
#define ROW 9
#define COL 10

// This will represent 1 cell in the 2D grid
class Cell
{
public:
    // These will be the row and column indices of the parent
    int parent_i, parent_j;

    // f = g + h
    // g = Cost to reach from start to a given square.
    // h = Estimated cost to reach the end point from a given square
    double f, g, h;
};

// Function to check the status of a cell (Blocked/Unblocked)
bool isNotBlocked(int grid[][COL], int row, int col)
{
    if (grid[row][col] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to check whether we've reached the destination
bool reachedDest(int row, int col, pair<int, int> dest)
{
    // cout << row << col << endl;
    if (row == dest.first && col == dest.second)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to calculate heuristic cost
double heuCost(int row, int col, pair<int, int> dest)
{
    // cout << (double)sqrt((pow(row - dest.first, 2) + pow(col - dest.second, 2))) << endl;
    return (double)sqrt((pow(row - dest.first, 2) + pow(col - dest.second, 2)));
}

// Function to check whether the current position in grid is valid
bool isValid(int row, int col)
{
    return ((row >= 0) && (row < ROW) && (col >= 0) && (col < COL));
}

// Function to trace path from source to destination
void trace(Cell cells[][COL], pair<int, int> dest)
{
    cout << "\nThe Path is: ";

    int row = dest.first;
    int col = dest.second;

    stack<pair<int, int>> Path;

    while (!(cells[row][col].parent_i == row && cells[row][col].parent_j == col))
    {
        Path.push(make_pair(row, col));
        int temp_row = cells[row][col].parent_i;
        int temp_col = cells[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push(make_pair(row, col));
    while (!Path.empty())
    {
        pair<int, int> p = Path.top();
        Path.pop();
        cout << "-> " << "(" << p.first << "," << p.second << ") ";
    }
}

// Search Algorithm
void aStarSearch(int grid[][COL], pair<int, int> src, pair<int, int> dest)
{
    // If the source is out of range
    if (isValid(src.first, src.second) == false)
    {
        cout << "\nSource is invalid!!!" << endl;
        return;
    }

    // If the destination is out of range
    if (isValid(dest.first, dest.second) == false)
    {
        cout << "\nDestination is invalid!!!" << endl;
        return;
    }

    // Either the source or the destination is blocked
    if (isNotBlocked(grid, src.first, src.second) == false ||
        isNotBlocked(grid, dest.first, dest.second) == false)
    {
        cout << "\nSource or Destination is blocked!!!" << endl;
        return;
    }

    // If the destination cell is the same as source cell
    if (reachedDest(src.first, src.second, dest))
    {
        cout << "\nWe have reached the destination!!!" << endl;
        return;
    }

    // Create a closed list with initial value false
    // to indicate no cell has been covered yet.
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    // 2D array to hold the details of cells
    Cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    // Create an open list containing f and (i, j)
    set<pair<double, pair<int, int>>> openList;

    // Inserting starting cell in open list with f=0
    openList.insert(make_pair(0.0, make_pair(i, j)));

    // bool if destination is reached. Initially, dest is not found (False).
    bool foundDest = false;

    while (!openList.empty())
    {
        pair<double, pair<int, int>> p = *openList.begin();

        // Remove the current vertex from the open list
        openList.erase(openList.begin());

        // Add the current vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        // Their are 8 possible directions in which we can move.
        // These will be named in the form of physical directions.

        //----------- 1st Successor (North) ------------

        // Check if cell index is valid
        if (isValid(i - 1, j))
        {
            // If the destination cell is the same as the
            // current successor
            if (reachedDest(i - 1, j, dest))
            {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                cout << "The destination cell is found\n";
                trace(cellDetails, dest);
                foundDest = true;
                return;
            }
            // Check if destination is in closed list or is blocked
            else if (closedList[i - 1][j] == false && isNotBlocked(grid, i - 1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = heuCost(i - 1, j, dest);
                fNew = gNew + hNew;

                // Check if desination is in open list
                // We will update the openList if it is not present/the new cost is lesser than eariler
                if (cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j)));

                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Check if cell index is valid
        if (isValid(i + 1, j))
        {
            // If the destination cell is the same as the
            // current successor
            if (reachedDest(i + 1, j, dest))
            {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                cout << "The destination cell is found\n";
                trace(cellDetails, dest);
                foundDest = true;
                return;
            }
            // Check if destination is in closed list or is blocked
            else if (closedList[i + 1][j] == false && isNotBlocked(grid, i + 1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = heuCost(i + 1, j, dest);
                fNew = gNew + hNew;

                // Check if desination is in open list
                // We will update the openList if it is not present/the new cost is lesser than eariler
                if (cellDetails[i + 1][j].f == FLT_MAX || cellDetails[i + 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j + 1))
        {
            // If the destination cell is the same as the
            // current successor
            if (reachedDest(i, j + 1, dest))
            {
                // Set the Parent of the destination cell
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                cout << "The destination cell is found\n";
                trace(cellDetails, dest);
                foundDest = true;
                return;
            }

            // Check if destination is in closed list or is blocked
            else if (closedList[i][j + 1] == false && isNotBlocked(grid, i, j + 1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = heuCost(i, j + 1, dest);
                fNew = gNew + hNew;

                // Check if desination is in open list
                // We will update the openList if it is not present/the new cost is lesser than eariler
                if (cellDetails[i][j + 1].f == FLT_MAX || cellDetails[i][j + 1].f > fNew)
                {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j + 1)));

                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j - 1))
        {
            // If the destination cell is the same as the
            // current successor
            if (reachedDest(i, j - 1, dest))
            {
                // Set the Parent of the destination cell
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                cout << "The destination cell is found\n";
                trace(cellDetails, dest);
                foundDest = true;
                return;
            }

            // Check if destination is in closed list or is blocked
            else if (closedList[i][j - 1] == false && isNotBlocked(grid, i, j - 1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = heuCost(i, j - 1, dest);
                fNew = gNew + hNew;

                // Check if desination is in open list
                // We will update the openList if it is not present/the new cost is lesser than eariler
                if (cellDetails[i][j - 1].f == FLT_MAX || cellDetails[i][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i, j - 1)));

                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

        //----------- 5th Successor (North-East)------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j + 1))
        {
            // If the destination cell is the same as the
            // current successor
            if (reachedDest(i - 1, j + 1, dest))
            {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j + 1].parent_i = i;
                cellDetails[i - 1][j + 1].parent_j = j;
                cout << "The destination cell is found\n";
                trace(cellDetails, dest);
                foundDest = true;
                return;
            }

            // Check if destination is in closed list or is blocked
            else if (closedList[i - 1][j + 1] == false && isNotBlocked(grid, i - 1, j + 1))
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = heuCost(i - 1, j + 1, dest);
                fNew = gNew + hNew;

                // Check if desination is in open list
                // We will update the openList if it is not present/the new cost is lesser than eariler
                if (cellDetails[i - 1][j + 1].f == FLT_MAX || cellDetails[i - 1][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j + 1)));

                    // Update the details of this cell
                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- 6th Successor (North-West)------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j - 1))
        {
            // If the destination cell is the same as the
            // current successor
            if (reachedDest(i - 1, j - 1, dest))
            {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j - 1].parent_i = i;
                cellDetails[i - 1][j - 1].parent_j = j;
                cout << "The destination cell is found\n";
                trace(cellDetails, dest);
                foundDest = true;
                return;
            }

            // Check if destination is in closed list or is blocked
            else if (closedList[i - 1][j - 1] == false && isNotBlocked(grid, i - 1, j - 1))
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = heuCost(i - 1, j - 1, dest);
                fNew = gNew + hNew;

                // Check if desination is in open list
                // We will update the openList if it is not present/the new cost is lesser than eariler
                if (cellDetails[i - 1][j - 1].f == FLT_MAX || cellDetails[i - 1][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));

                    // Update the details of this cell
                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                }
            }
        }

        //----------- 7th Successor (South-East)------------

        // Only process this cell if this is a valid one
        if (isValid(i + 1, j + 1))
        {
            // If the destination cell is the same as the
            // current successor
            if (reachedDest(i + 1, j + 1, dest))
            {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j + 1].parent_i = i;
                cellDetails[i + 1][j + 1].parent_j = j;
                cout << "The destination cell is found\n";
                trace(cellDetails, dest);
                foundDest = true;
                return;
            }

            // Check if destination is in closed list or is blocked
            else if (closedList[i + 1][j + 1] == false && isNotBlocked(grid, i + 1, j + 1))
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = heuCost(i + 1, j + 1, dest);
                fNew = gNew + hNew;

                // Check if desination is in open list
                // We will update the openList if it is not present/the new cost is lesser than eariler
                if (cellDetails[i + 1][j + 1].f == FLT_MAX || cellDetails[i + 1][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j + 1)));

                    // Update the details of this cell
                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- 8th Successor (South-West)------------

        // Only process this cell if this is a valid one
        if (isValid(i + 1, j - 1))
        {
            // If the destination cell is the same as the
            // current successor
            if (reachedDest(i + 1, j - 1, dest))
            {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j - 1].parent_i = i;
                cellDetails[i + 1][j - 1].parent_j = j;
                cout << "The destination cell is found\n";
                trace(cellDetails, dest);
                foundDest = true;
                return;
            }

            // Check if destination is in closed list or is blocked
            else if (closedList[i + 1][j - 1] == false && isNotBlocked(grid, i + 1, j - 1))
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = heuCost(i + 1, j - 1, dest);
                fNew = gNew + hNew;

                // Check if desination is in open list
                // We will update the openList if it is not present/the new cost is lesser than eariler
                if (cellDetails[i + 1][j - 1].f == FLT_MAX || cellDetails[i + 1][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j - 1)));

                    // Update the details of this cell
                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                }
            }
        }
    }

    // If destination has not been reached due to blockage/ irregularities
    if (foundDest == false)
        cout << "Failed to find the Destination Cell\n";

    return;
}

int main()
{
    int grid[ROW][COL] = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };

    // Source is the left-most bottom-most corner
    pair<int, int> src = make_pair(8, 0);

    // Destination is the left-most top-most corner
    pair<int, int> dest = make_pair(0, 0);

    aStarSearch(grid, src, dest);

    return 0;
}

/* 
Input:
    int grid[ROW][COL] = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
                        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
                        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
                        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };

Output:

The destination cell is found     

The Path is: -> (8,0) -> (7,0) -> (6,0) -> (5,0) -> (4,1) -> (3,2) -> (2,1) -> (1,0) -> (0,0) 

*/