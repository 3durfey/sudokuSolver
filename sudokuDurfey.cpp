#include <iostream>
#include <queue>
#include <map>
using namespace std;
void printSudoku();

int sudokuContainer[9][9] = {
    {0, 0, 0, 1, 0, 0, 8, 5, 0},
    {5, 3, 6, 2, 8, 7, 9, 4, 1},
    {0, 7, 1, 9, 0, 0, 0, 0, 0},
    {0, 2, 7, 0, 1, 0, 4, 6, 5},
    {0, 5, 4, 0, 2, 0, 0, 9, 8},
    {6, 0, 0, 0, 4, 5, 1, 2, 3},
    {2, 6, 0, 4, 7, 0, 3, 8, 0},
    {0, 8, 0, 6, 3, 2, 5, 1, 4},
    {0, 1, 3, 5, 9, 0, 0, 0, 0},
};
/* {9, 4, 2, 1, 6, 3, 8, 5, 7},
   {5, 3, 6, 2, 8, 7, 9, 4, 1},
   {8, 7, 1, 9, 5, 4, 2, 3, 6},
   {3, 2, 7, 8, 1, 9, 4, 6, 5},
   {1, 5, 4, 3, 2, 6, 7, 9, 8},
   {6, 9, 8, 7, 4, 5, 1, 2, 3},
   {2, 6, 5, 4, 7, 1, 3, 8, 9},
   {7, 8, 9, 6, 3, 2, 5, 1, 4},
   {4, 1, 3, 5, 9, 8, 6, 7, 2},
*/
/*
   942163857536287941871954236327819465154326798698745123265471389789632514413598672


*/
// function checks sudoku container for validity, returning false if not valid
bool validityCheck()
{
    map<int, bool> map;
    // for loop for starting each box
    for (int x = 0; x < 9; x++)
    {
        for (int y = 1; y <= 9; y++)
        {
            map[y] = false;
        }
        int columnStart;
        int columnEnd;
        int rowStart;
        int rowEnd;
        if (x == 0 || x == 3 || x == 6)
        {
            columnStart = 0;
            columnEnd = 3;
        }
        else if (x == 1 || x == 4 || x == 7)
        {
            columnStart = 3;
            columnEnd = 6;
        }
        else
        {
            columnStart = 6;
            columnEnd = 9;
        }
        if (x < 3)
        {
            rowStart = 0;
            rowEnd = 3;
        }
        else if (x >= 3 && x < 6)
        {
            rowStart = 3;
            rowEnd = 6;
        }
        else
        {
            rowStart = 6;
            rowEnd = 9;
        }

        for (int row = rowStart; row < rowEnd; row++)
        {
            for (int column = columnStart; column < columnEnd; column++)
            {
                if (sudokuContainer[row][column] != 0)
                {
                    if (map[sudokuContainer[row][column]] == true)
                    {
                        return false;
                    }
                    else
                    {
                        map[sudokuContainer[row][column]] = true;
                    }
                }
            }
        }
    }

    // check each row
    for (int row = 0; row < 9; row++)
    {
        for (int y = 1; y <= 9; y++)
        {
            map[y] = false;
        }
        for (int column = 0; column < 9; column++)
        {
            if (sudokuContainer[row][column] != 0)
            {
                if (map[sudokuContainer[row][column]] == true)
                {
                    return false;
                }
                else
                {
                    map[sudokuContainer[row][column]] = true;
                }
            }
        }
    }
    // check each column
    for (int row = 0; row < 9; row++)
    {
        for (int y = 1; y <= 9; y++)
        {
            map[y] = false;
        }
        for (int column = 0; column < 9; column++)
        {
            if (sudokuContainer[column][row] != 0)
            {
                if (map[sudokuContainer[column][row]] == true)
                {
                    return false;
                }
                else
                {
                    map[sudokuContainer[column][row]] = true;
                }
            }
        }
    }
    return true;
}
// function that attempts to fill out sudoku using recursion and backtracking. returns true if solved or false if not possible
bool solveSudoku()
{
    for (int row = 0; row < 9; row++)
    {
        for (int column = 0; column < 9; column++)
        {
            if (sudokuContainer[row][column] == 0)
            {
                for (int x = 1; x < 10; x++)
                {
                    sudokuContainer[row][column] = x;
                    cout << " row: " << row << " column: " << column << " value: " << x << endl;
                    if (validityCheck())
                    {
                        printSudoku();
                        int result = solveSudoku();
                        if (!result)
                        {
                            x = 0;
                        }
                        else
                        {
                            cout << "valid" << endl;
                            return true;
                        }
                    }
                    else if (x == 9)
                    {
                        cout << "9 ended no match" << endl;
                        sudokuContainer[column][row] = 0;
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void printSudoku()
{
    for (int row = 0; row < 9; row++)
    {
        for (int column = 0; column < 9; column++)
        {
            cout << sudokuContainer[row][column];
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    queue<int> q;
    int temp;
    cout << "Before solved: " << endl;
    printSudoku();
    solveSudoku();
    cout << "Solved Sudoku: " << endl;

    printSudoku();
    // functions for getting input from user for specific sudoku, bypassed since it would be a long process to input every input. Functions take user input and put into queue, then into two dimensional array.
    /*
    for (int x = 1; x <= 81; x++)
    {
        cout << "Enter number for space " << x << " (or 0 if empty): ";
        cin >> temp;
        q.push(temp);
    }
    while (!q.empty())
    {
        for (int x = 0; x < 9; x++)
        {
            for (int y = 0; y < 9; y++)
            {
                sudokuContainer[x][y] = q.front();
                q.pop();
            }
        }
    }
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            cout << sudokuContainer[x][y];
        }
        cout << endl;
    }
    */
}