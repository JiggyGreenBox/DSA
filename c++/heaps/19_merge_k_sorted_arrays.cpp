#include <vector>
#include <iostream>
#include <queue>
using namespace std;

/*
Merge k Sorted Arrays
[https://www.geeksforgeeks.org/problems/merge-k-sorted-arrays/1]

You are given a 2D matrix mat[][] of size n x m. Each row in the 
matrix is sorted in non-decreasing order. Your task is to merge all 
the rows and return a single sorted array that contains all the 
elements of the matrix.

Examples :

    Input: mat[][] = [[1, 3, 5, 7],
                    [2, 4, 6, 8], 
                    [0, 9, 10, 11]]
    Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
    Explanation: Merging all elements from the 3 sorted arrays and 
    sorting them results in: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11].

    Input: mat[][] = [[1, 2, 3, 4], 
                    [2, 2, 3, 4],
                    [5, 5, 6, 6],
                    [7, 8, 9, 9]]
    Output: [1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 9] 
    Explanation: Merging all elements from the 4 sorted arrays and 
    sorting them results in:[1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 
    9]
*/

struct Node {
    int val;
    int row;
    int col;    
};

vector<int> mergeArrays(vector<vector<int>> &mat) {

    vector<int> ans;
    
    auto cmp = [](const Node &a, const Node &b) {
        return a.val > b.val;
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);

    for(int r = 0; r < mat.size(); r++) {

        if(mat[r].size() > 0) {            
            pq.push({mat[r][0], r, 0});
        }
    }

    while (!pq.empty())
    {
        auto node = pq.top();
        pq.pop();
        ans.push_back(node.val);

        if(node.col + 1 < mat[node.row].size()) {

            int r = node.row;
            int c = node.col + 1;

            pq.push({mat[r][c], r, c});
        }
    }    

    return ans;
}