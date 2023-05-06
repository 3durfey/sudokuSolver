#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <set>
using namespace std;

class Sudoku
{
private:
    int sudoku[9][9];
    int origional[9][9];
    vector<int *> emptyPositions;
    int numberToFill;

public:
    Sudoku(int sudoku[9][9], int numberToFill)
    {
        for (int x = 0; x < 9; x++)
        {
            for (int y = 0; y < 9; y++)
            {
                this->sudoku[x][y] = sudoku[x][y];
                this->origional[x][y] = sudoku[x][y];
                if (sudoku[x][y] == 0)
                {
                    int *arrayPosition = new int[2];
                    arrayPosition[0] = x;
                    arrayPosition[1] = y;
                    this->emptyPositions.push_back(&arrayPosition[0]);
                }
            }
        }
        this->numberToFill = numberToFill;
    }
    void printAndSolve()
    {
        if (this->solve())
        {
            printSemiCompleted();
            cout << "completed sudoku: " << endl;
            cout << "--------------------------------------" << endl;
            for (int row = 0; row < 9; row++)
            {
                for (int column = 0; column < 9; column++)
                {
                    if (sudoku[row][column] == 0)
                        cout << " |"
                             << "  ";
                    else
                        cout << " | " << sudoku[row][column];
                }
                cout << " |" << endl;
                cout << "--------------------------------------" << endl;
            }
        }
        else
            cout << "Unsolvable" << endl;
    }
    bool checkValidity(int column, int row, int num)
    {
        // check each row for value return false if found
        for (int x = 0; x < 9; x++)
            if (sudoku[x][column] == num)
                return false;
        // check each column for value return false if found
        for (int y = 0; y < 9; y++)
            if (sudoku[row][y] == num)
                return false;
        // check box for value return false if found
        for (int x = 0; x < 3; x++)
            for (int y = 0; y < 3; y++)
                if (sudoku[x + (row - row % 3)][y + (column - column % 3)] == num)
                    return false;
        return true;
    }
    bool findEmptyLocation(int *row, int *column)
    {
        for (int x = 0; x < 9; x++)
            for (int y = 0; y < 9; y++)
                if (sudoku[x][y] == 0)
                {
                    *row = x;
                    *column = y;
                    return true;
                }
        return false;
    }

    bool solve()
    {
        int row, column;
        if (!findEmptyLocation(&row, &column))
            return true;
        for (int num = 1; num <= 9; num++)
        {
            if (checkValidity(column, row, num))
            {
                sudoku[row][column] = num;
                if (solve())
                    return true;
                sudoku[row][column] = 0;
            }
        }
        return false;
    }
    void printSemiCompleted()
    {
        srand(time(NULL));
        set<int> setOfNums;
        while (setOfNums.size() < numberToFill)
        {
            int size = (emptyPositions.size() - 1);
            int random = rand() % size;
            setOfNums.insert(random);
        }
        auto it = setOfNums.begin();
        for (int x = 0; x < numberToFill; x++, it++)
        {
            origional[*(emptyPositions[*it])][*(emptyPositions[*it] + 1)] = sudoku[*(emptyPositions[*it])][*(emptyPositions[*it] + 1)];
        }
        cout << "semi completed sudoku: " << endl;
        cout << "--------------------------------------" << endl;
        for (int row = 0; row < 9; row++)
        {
            for (int column = 0; column < 9; column++)
            {
                if (origional[row][column] == 0)
                    cout << " |"
                         << "  ";
                else
                    cout << " | " << origional[row][column];
            }
            cout << " |" << endl;
            cout << "--------------------------------------" << endl;
        }
    }
};

int main()
{

    int inputSudoku[9][9] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                             {5, 2, 0, 0, 0, 0, 0, 0, 0},
                             {0, 8, 7, 0, 0, 0, 0, 3, 1},
                             {0, 0, 3, 0, 1, 0, 0, 8, 0},
                             {9, 0, 0, 8, 6, 3, 0, 0, 5},
                             {0, 5, 0, 0, 9, 0, 6, 0, 0},
                             {1, 3, 0, 0, 0, 0, 2, 5, 0},
                             {0, 0, 0, 0, 0, 0, 0, 7, 4},
                             {0, 0, 5, 2, 0, 6, 3, 0, 0}};

    Sudoku sudokuObject(inputSudoku, 42);
    sudokuObject.printAndSolve();

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