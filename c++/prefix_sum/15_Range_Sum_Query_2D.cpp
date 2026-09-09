/*
Range Sum Query 2D - Immutable
    [https://leetcode.com/problems/range-sum-query-2d-immutable/description/]

Given a 2D matrix matrix, handle multiple queries of the following 
type:

Calculate the sum of the elements of matrix inside the rectangle 
defined by its upper left corner (row1, col1) and lower right corner 
(row2, col2).
Implement the NumMatrix class:

NumMatrix(int[][] matrix) Initializes the object with the integer 
matrix matrix.
int sumRegion(int row1, int col1, int row2, int col2) Returns the sum 
of the elements of matrix inside the rectangle defined by its upper 
left corner (row1, col1) and lower right corner (row2, col2).
You must design an algorithm where sumRegion works on O(1) time 
complexity.
*/
#include <iostream>
#include <vector>
using namespace std;

/*
sum(l,r) = prefix[r] - prefix[l-1]

    we want prefix[n+1]
        then sum(l,r) = prefix[r+1] - prefix[l]

    for matrix of r,c
        we want a matrix of [r+1][c]

    sum(r1,c1,r2,c2)

        for r=r1 r<=r2 r++
            sum += prefix[r][c2] - prefix[r][c1-1]
*/ 

/*
    for r c mat we make a r+1,c+1 mat        
        1 2 3
        4 5 6
        7 8 9
    
    becomes
        0 0 0 0
        0 1 2 3
        0 4 5 6
        0 7 8 9

    then we prefix above and left
    at prefix[2][2]
        we want 1+2+4+5 = 12

    0 0 0 0    0  0  0  0
    0 1 2 3    0  1  3  6
    0 4 5 6    0  5 12 21
    0 7 8 9    0 12 27 45

    at [2][2]
        we see above is 3 (1 + 2)
        and left is 5 (1 + 4)
        1 has been duplicated
        and current is 5
            so the res is 3+5+5-1 = 12
*/


/*
query

        c0  c1  c2
     ┌─────────────
r0   │  1   2   3
r1   │  4   5   6
r2   │  7   8   9

          c0  c1  c2  c3
       ┌─────────────────
r0     │  0   0   0   0
r1     │  0   1   3   6
r2     │  0   5  12  21
r3     │  0  12  27  45



(row1,col1) = (1,1)
(row2,col2) = (2,2)
    5 + 6 +8 + 9 = 28

start with the big rectangle
    prefix[3][3] = 45

Remove everything ABOVE our target
    remove row 1 2 3 == 6
    prefix[0][3] == 6
        45 - 6

Remove everything LEFT of our target
    remove 
        1
        4
        7
    remove prefix[2][0] == 12
        45 - 6 - 12
    overlap of 1 was removed twice

    45 - 6 - 12 + 1 = 28

big rectangle − top − left + overlap.

*/

class NumMatrix {
private:    
    vector<vector<int>> prefix;
public:
    NumMatrix(vector<vector<int>>& matrix) {

        int r = matrix.size();
        int c = matrix[0].size();

        prefix.resize(r+1, vector<int>(c+1, 0));

        for(int i=0; i<r; i++) {
            for(int j=0; j<c; j++) {
                prefix[i+1][j+1] =  prefix[i][j+1] +    // above
                                    prefix[i+1][j] +    // left
                                    matrix[i][j] -      // current
                                    prefix[i][j];       // overlap
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return prefix[row2 + 1][col2 + 1] // large rectangle
                - prefix[row1][col2 + 1]  // remove row above
                - prefix[row2+1][col1]    // remove col left
                + prefix[row1][col1];     // add overlap
    }
};

int main() {
    vector<vector<int>> matrix = {{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}};
    NumMatrix numMatrix = NumMatrix(matrix);
    cout << numMatrix.sumRegion(2, 1, 4, 3) << endl; // return 8 (i.e sum of the red rectangle)
    cout << numMatrix.sumRegion(1, 1, 2, 2) << endl; // return 11 (i.e sum of the green rectangle)
    cout << numMatrix.sumRegion(1, 2, 2, 4) << endl; // return 12 (i.e sum of the blue rectangle)
    return 0;
}