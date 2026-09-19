/*
Combinations
    [https://leetcode.com/problems/combinations/description/]

Given two integers n and k, return all possible combinations of k 
numbers chosen from the range [1, n].

You may return the answer in any order.

 

Example 1:

Input: n = 4, k = 2
Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
Explanation: There are 4 choose 2 = 6 total combinations.
Note that combinations are unordered, i.e., [1,2] and [2,1] are 
considered to be the same combination.
Example 2:

Input: n = 1, k = 1
Output: [[1]]
Explanation: There is 1 choose 1 = 1 total combination.

*/


#include <vector>
#include <iostream>
using namespace std;

void combine(int start, int n, int k, vector<int> &curr, vector<vector<int>> &ans) {

    if(curr.size() == k) {
        ans.push_back(curr);
        return;
    }    

    for(int i=start; i<=n; i++) { // range is [1,n] n inclusive
        curr.push_back(i);
        combine(i + 1, n, k, curr, ans);
        curr.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> ans;
    vector<int> curr;
    combine(1, n, k, curr, ans);
    return ans;
}

int main() {
    auto x = combine(4,2);    
    return 0;
}