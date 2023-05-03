#include <iostream>
#include <queue>
#include <map>
using namespace std;

int sudokuContainer[9][9] = {
    {1, 0, 0, 0, 0, 0, 0, 4, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 7, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

string validityCheck()
{
    // check each box

    map<int, bool> map;
    for (int y = 0; y < 9; y++)
    {
        map[y] = false;
    }

    for (int row = 0; row < 3; row++)
    {

        for (int column = 0; column < 3; column++)
        {
            if (sudokuContainer[row][column] != 0)
            {
                if (map[sudokuContainer[row][column]] == true)
                {
                    return "invalid";
                }
                else
                {
                    map[sudokuContainer[row][column]] = true;
                }
            }
        }
    }

    // check each row
    for (int row = 0; row < 9; row++)
    {
        for (int y = 0; y < 9; y++)
        {
            map[y] = false;
        }
        for (int column = 0; column < 9; column++)
        {
            if (sudokuContainer[row][column] != 0)
            {
                if (map[sudokuContainer[row][column]] == true)
                {
                    return "invalid";
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
        for (int y = 0; y < 9; y++)
        {
            map[y] = false;
        }
        for (int column = 0; column < 9; column++)
        {
            if (sudokuContainer[column][row] != 0)
            {
                if (map[sudokuContainer[column][row]] == true)
                {
                    return "invalid";
                }
                else
                {
                    map[sudokuContainer[column][row]] = true;
                }
            }
        }
    }
    return "valid";
}

int main()
{
    queue<int> q;
    int temp;
    string validResult = validityCheck();
    cout << validResult << endl;
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