#include <iostream>
#include <map>
#include <vector>

using namespace std;

void func(int a, int b)
{
    a = 1;
    b = 2;
}

// Driver Code
int main()
{
    int arr[81];
    int a[9][9] = {{1, 2, 3, 4, 5, 6, 7, 8, 9},
                   {10, 11, 12, 13, 14, 15, 16, 17, 18},
                   {19, 20, 21, 22, 23, 24, 25, 26, 27},
                   {28, 29, 30, 31, 32, 33, 34, 35, 36},
                   {37, 38, 39, 40, 41, 42, 43, 44, 45},
                   {46, 47, 48, 49, 50, 51, 52, 53, 54},
                   {55, 56, 57, 58, 59, 60, 61, 62, 63},
                   {64, 65, 66, 67, 68, 69, 70, 71, 72},
                   {73, 74, 75, 76, 77, 78, 79, 80, 81}};
    int x = 80;
    int count = 0;
    // cout << ((x - (x % 9)) / 9) - 1 << endl;
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            // cout << a[x][y] << " count value: " << count << endl;
            arr[count] = a[x][y];
            count++;
        }
    }

    vector<int *> vec;
    int y = 30;
    for (int x = 0; x < 10; x++)
    {
        int *array = new int[2];
        array[0] = x;
        array[1] = y;
        y++;
        vec.push_back(&array[0]);
    }

    cout << *(vec[7]) << endl;
    cout << *(vec[7] + 1) << endl;
}
// cout << "X value: " << x << " ";
// cout << a[(x - (x % 9)) / 9][x % 9 - 1] << endl;
//  This is code is contributed by rathbhupendra