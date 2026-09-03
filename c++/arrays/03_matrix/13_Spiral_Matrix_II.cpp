/*
Spiral Matrix II
    [https://leetcode.com/problems/spiral-matrix-ii/description/]


    Given a positive integer n, generate an n x n matrix filled with 
    elements from 1 to n2 in spiral order.

Example 1:
    Input: n = 3
    Output: [[1,2,3],[8,9,4],[7,6,5]]

Example 2:

Input: n = 1
Output: [[1]]
*/
#include <vector>
using namespace std;

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> ans(n, vector<int>(n));

    int top = 0;
    int bot = n-1;
    int left = 0;
    int right = n-1;

    int count = 1;

    while (top <= bot && left <= right) {

        for(int i=left; i<=right; i++) {
            ans[top][i] = count++;
        }
        top++;

        for(int i=top; i<=bot; i++) {
            ans[i][right] = count++;
        }
        right--;

        if(top <= bot) {
            for(int i=right; i>=left; i--) {
                ans[bot][i] = count++;
            }
        }
        bot--;
        

        if(left <= right) {
            for(int i=bot; i>=top; i--) {
                ans[i][left] = count++;
            }
        }
        left++;        
    }
    return ans;
}



int main() {
    int n = 3;
    vector<vector<int>> ans = generateMatrix(n);    
    int x = 5;
    return 0;
}