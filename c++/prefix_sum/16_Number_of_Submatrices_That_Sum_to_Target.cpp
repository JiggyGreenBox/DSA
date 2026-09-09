/*
Number of Submatrices That Sum to Target
[https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/description/]

Given a matrix and a target, return the number of non-empty 
submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with 
x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are 
different if they have some coordinate that is different: for 
example, if x1 != x1'.

Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.
Example 2:

Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, 
plus the 2x2 submatrix.
Example 3:

Input: matrix = [[904]], target = 0
Output: 0
*/

/*
we dont need random queries
we need a running sum type
so we dont need n+1 arrays

we keep a running total and store results

so for each row
    colsum

    for each ele in cols
        colsum[i] += sum

        if sum - target in map
            count += map[search]
        store sum-target in map
*/

/*
we want to compress results into a 1d array then run the standard algos
so initially top = 0
    bot = 0 (1st row only)
    bot = 1 (1+2 row)
    bot = 2 (all rows compressed)

top = 1
    bot = 1 (only 2nd row)
    bot = 2 (2+3 row)

top = 2
    bot 2 only last row

this is essentially trying all combinations

time complexity

    for (top) {                 // O(R)
        for (bottom) {          // O(R)
            for (col) {         // O(C)
                colSum[col] += matrix[bottom][col];
            }

            for (col) {         // O(C)
                // prefix + hashmap
            }
        }
    }

    R^2 * C time
    C space


*/

#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;


int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    int r = matrix.size();
    int c = matrix[0].size();

    int count = 0;

    for (int top = 0; top < r; top++) {

        vector<int> colSum(c, 0);

        for (int bottom = top; bottom < r; bottom++) {

            // Flatten rows top..bottom into 1D
            for (int j = 0; j < c; j++)
                colSum[j] += matrix[bottom][j];

            // LC 560 on colSum
            unordered_map<int, int> mpp;
            mpp[0] = 1;

            int prefix = 0;

            for (int j = 0; j < c; j++) {
                prefix += colSum[j];

                int search = prefix - target;

                if (mpp.count(search))
                    count += mpp[search];

                mpp[prefix]++;
            }
        }
    }

    return count;
}

int main() {
    vector<vector<int>> matrix = {{0,1,0},{1,1,1},{0,1,0}};
    int target = 0;

    cout << numSubmatrixSumTarget(matrix, target) << endl;

    return 0;
}