#include <iostream>
#include <vector>
using namespace std;

/*

Find row with maximum 1's

    Given a non-empty grid mat consisting of only 0s and 1s, where all 
    the rows are sorted in ascending order, find the index of the row 
    with the maximum number of ones.

    If two rows have the same number of ones, consider the one with a 
    smaller index. If no 1 exists in the matrix, return -1.
*/

/*
numbers are in sorted order
row with the first 1 present is our answer

nums within rows are sorted but not the rows themselves

smaller index of 1's is the answer
r1 - 1
r2 - 3
r3 - 5
    answer r1

bsearch on rows
    l=0, r=n-1
    mid = ..
    if mid == 1
        try find smaller

int first_one = INT_MAX
int row_idx
for r=0 r<rows; r++
    if(bsearch(r) < first_one)
        first_one = bsearch(r)
        row_idx = r

return r
*/

/*
Observation:
    Earlier first 1 => more 1's

Goal:
    Find row whose first 1 occurs earliest

Method:
    Lower bound of 1 in every row
    Track minimum index
*/

/*
Observation:
    Earlier 1 => more 1s.

Need:
    Find leftmost 1.

Choose top-right.

If current cell = 1:
    This row is a candidate.
    Move left to search for an earlier 1.

If current cell = 0:
    Everything left is also 0.
    This row cannot contain an earlier 1.
    Move down.

Each step removes one row or one column.

Complexity:
    O(rows + cols)
*/

int rowWithMax1s(vector<vector<int>> &mat) {

}

int main() {

    return 0;
}