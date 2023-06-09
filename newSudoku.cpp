#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <fstream>

using namespace std;

class Sudoku
{
private:
    int sudoku[9][9];
    int origional[9][9];
    vector<int *> emptyPositions;
    int numberToFill;
    int newOrEntered;

public:
    Sudoku(int sudoku[9][9], int numberToFill, int newOrEntered)
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
        this->newOrEntered = newOrEntered;
    }
    void start()
    {
        // solve entered sudoku
        if (this->newOrEntered == 1)
        {
            if (this->solveEnteredSudoku())
            {
                fillSemiCompleted();
                printToTx(sudoku, "completed sudoku: ");
                printToTx(origional, "partially completed sudoku: ");
            }
            else
                cout << "Unsolvable" << endl;
        }
        // create new sudoku
        else
        {
            if (this->newSudoku())
            {
                fillSemiCompleted();
                printToTx(origional, "Generated sudoku: ");
            }
            else
                cout << "Unsolvable" << endl;
        }
    }
    void printToTx(int array[9][9], string title)
    {
        fstream myfile;
        myfile.open("sudoku.txt", fstream::app);
        if (myfile.is_open())
        {
            myfile << title << endl;
            myfile << "--------------------------------------" << endl;
            for (int row = 0; row < 9; row++)
            {
                for (int column = 0; column < 9; column++)
                {
                    if (array[row][column] == 0)
                        myfile << " | "
                               << " ";
                    else
                        myfile << " | " << array[row][column];
                }
                myfile << " |" << endl;
                myfile << "--------------------------------------" << endl;
            }
            myfile.close();
        }
        else
            cout << "Unable to open file";
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
    bool solveEnteredSudoku()
    {
        int row, column;
        if (!findEmptyLocation(&row, &column))
            return true;
        for (int num = 1; num <= 9; num++)
        {
            if (checkValidity(column, row, num))
            {
                sudoku[row][column] = num;
                if (solveEnteredSudoku())
                    return true;
                sudoku[row][column] = 0;
            }
        }
        return false;
    }
    bool newSudoku()
    {
        srand(time(NULL));
        int row, column;
        int y = 0;
        int arr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        while (y <= 8)
        {
            bool b = false;
            int num = rand() % 9 + 1;
            for (int x = 0; x < 10; x++)
            {
                if (arr[x] == num)
                {
                    b = true;
                }
            }
            if (b != true)
            {
                arr[y] = num;
                y++;
            }
            b = false;
        }
        if (!findEmptyLocation(&row, &column))
            return true;
        for (int x = 0; x < 10; x++)
        {
            if (checkValidity(column, row, arr[x]))
            {
                sudoku[row][column] = arr[x];
                if (newSudoku())
                    return true;
                sudoku[row][column] = 0;
            }
        }
        return false;
    }

    void fillSemiCompleted()
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
    }
};

int main()
{

    int sudokuContainer[9][9] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                                 {5, 2, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 8, 7, 0, 0, 0, 0, 3, 1},
                                 {0, 0, 3, 0, 1, 0, 0, 8, 0},
                                 {9, 0, 0, 8, 6, 3, 0, 0, 5},
                                 {0, 5, 0, 0, 9, 0, 6, 0, 0},
                                 {1, 3, 0, 0, 0, 0, 2, 5, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 7, 4},
                                 {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    int choice;
    cout << "enter 1 to enter sudoku to solve or 2 to generate new sudoku: ";
    cin >> choice;
    if (choice == 2)
    {
        for (int x = 0; x < 9; x++)
        {
            for (int y = 0; y < 9; y++)
            {
                sudokuContainer[x][y] = 0;
            }
        }
    }
    else
    {
        int temp;
        queue<int> q;
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
    }
    int value;
    cout << "Enter number of boxes you would like filled in: ";
    cin >> value;

    Sudoku sudokuObject(sudokuContainer, 60, choice);
    sudokuObject.start();
}