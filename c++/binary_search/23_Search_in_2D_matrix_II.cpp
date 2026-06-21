#include <iostream>
#include <vector>
using namespace std;

/*
Search in 2D matrix - II

    Given a 2D array matrix where each row is sorted in ascending order 
    from left to right and each column is sorted in ascending order from 
    top to bottom, write an efficient algorithm to search for a specific 
    integer target in the matrix.


    Example 1
        Input: matrix = [ [ 1,  4,  7, 11, 15], 
                        [ 2,  5,  8, 12, 19], 
                        [ 3,  6,  9, 16, 22],
                        [10, 13, 14, 17, 24], 
                        [18, 21, 23, 26, 30] ], target = 5
        Output: True
        Explanation: The target 5 exists in the matrix in the index (1,1)

    Example 2
        Input: matrix= [ [ 1,  4,  7, 11, 15], 
                        [ 2,  5,  8, 12, 19], 
                        [ 3,  6,  9, 16, 22],
                        [10, 13, 14, 17, 24],
                        [18, 21, 23, 26, 30] ], target = 20
        Output: False
        Explanation: The target 20 does not exist in the matrix.
*/

/*

[ 1  3  5]
[ 2  7 30]
[11 21 99]

curr 1
targ = 21


Search in 2D matrix - II
    rows are sorted and columns are sorted
    cant use flattened array approach here

    we can use a stairway approach


    use sorted for quick elimination
    
    rows are sorted and cols are also sorted

        1  4  7  11
        2  5  8  12
        3  6  9  16

        1  5  10  20
        2  6  11  21
        4  8  14  24

            search 3, 7, 22, 13

    if we start top right
        then if curr > target
            eliminate col
            c--
        if curr < target
            eliminate row
            r++

    
    
*/

bool searchMatrix(vector<vector<int>> &matrix, int target) {
    int mr = matrix.size();
    int mc = matrix[0].size();

    int r=0, c = mc-1;

    while(r < mr && c >= 0) {
        int cell = matrix[r][c];
        if(cell == target) return true;
        else if(cell > target) {
            // discard column
            c--;
        }
        else {
            // cell < target
            // discard row
            r++;
        }
    }
    return false;
}

void print(bool res) { 
    cout << (res ? "true" : "false") << endl;    
}

int main() {
    vector<vector<int>> m = {{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}};
    int target = 5;
    print(searchMatrix(m, target));

    m = {{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}};
    target = 20;
    print(searchMatrix(m, target));
    
    
    return 0;
}