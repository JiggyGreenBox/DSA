/*

finish merge k sorted lists first

[https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/description/]
Kth Smallest Element in a Sorted Matrix

Given an n x n matrix where each of the rows and columns is sorted in 
ascending order, return the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the 
kth distinct element.

You must find a solution with a memory complexity better than O(n2).

Example 1:

    Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
    Output: 13
    Explanation: The elements in the matrix are 
    [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13

Example 2:

    Input: matrix = [[-5]], k = 1
    Output: -5
*/

/*

Kth Smallest Element in a Sorted Matrix
    if all rows were unsorted push into heap and take kth after popping k times
    but rows are sorted

Unsorted matrix
7 2 9
4 8 1
6 5 3

push all into min heap
or keep max-heap of size k

but now sorted
    1  5  9
    10 11 13
    12 13 15

    if k = 2
    1,10,12
        pop 1
    5,10,12
        answer is 5


--------------------------------------

Kth Smallest in Sorted Matrix

Treat each row as a sorted list.

Heap contains the smallest unprocessed
element from each row.

        ↓

Pop global minimum.

        ↓

If it came from row r, col c:

    push matrix[r][c + 1]

        ↓

Repeat K times.

        ↓

The Kth popped element is the answer.
*/




#include <vector>
#include <queue>
using namespace std;

int kthSmallest(vector<vector<int>>& matrix, int k) {

    int n = matrix.size();

    struct Node {
        int val;
        int row;
        int col;
    };

    auto cmp = [](const Node& a, const Node& b) {
        return a.val > b.val;
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);

    // First element of every row
    for (int r = 0; r < n; r++) {
        pq.push({matrix[r][0], r, 0});
    }

    // Pop k times
    while (k--) {

        Node curr = pq.top();
        pq.pop();

        if (k == 0)
            return curr.val;

        int nextCol = curr.col + 1;

        if (nextCol < n) {
            pq.push({
                matrix[curr.row][nextCol],
                curr.row,
                nextCol
            });
        }
    }

    return -1;
}












/*
Kth Smallest Element in a Sorted Matrix

rows are sorted and columns are sorted
we had a problem where we can search from lop right to find an element
*/

  
