#include <iostream>
#include <vector>
using namespace std;

/*

Search in a 2D matrix
    Given a 2-D array mat where the elements of each row are sorted in 
    non-decreasing order, and the first element of a row is greater than 
    the last element of the previous row (if it exists), and an integer 
    target, determine if the target exists in the given mat or not.


    Example 1

        Input: mat = [ [1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12] ], target 
        = 8
        Output: True

        Explanation: The target = 8 exists in the 'mat' at index (1, 3).

    Example 2

        Input: mat = [ [1, 2, 4], [6, 7, 8], [9, 10, 34] ], target = 78
        Output: False

        Explanation: The target = 78 does not exist in the 'mat'. Therefore 
        in the output, we see 'false'.
*/

/*

use sorted property to elimate rows and cols

start from right and mid row
r = n/2, c=n-1

we can reduce the value by going left or going up
we can increase by going right to going down

we can use 3 cells to decide where to go
        ..top..
    firt..curr..last
        ..bot..


if tar > curr && < last 
    go right

if tar < curr && > first
    go left


if tar > curr && > last
    go bot

if tar < curr && < first
    go top    

*/

/*
better approach
if we flatten the matrix, it is a sorted array

last(row i) < first(row i+1)

3*4 mat has 3*4 elems
search is in [0..(m*n)-1]

low=0
high = (rows*cols)-1

2*3 mat
    012  [0][0]
    345  [1][0] = 1*r + c

    4 is at (1*2)+1 = 3

    reverse 3
        3/2 = 1
        3%3 = 0
        [1][0]



while (low<=high) 
    mid = 

    r = mid / cols 
    c = mid % cols

*/

/*

Observation:
    last(row i) < first(row i+1)

Therefore:
    Matrix behaves like a single sorted array.

Search Space:
    [0, rows*cols - 1]

For mid:
    row = mid / cols
    col = mid % cols

Compare:
    mat[row][col]

*/

bool searchMatrix(vector<vector<int>> &mat, int target) {

}

int main() {
    return 0;
}