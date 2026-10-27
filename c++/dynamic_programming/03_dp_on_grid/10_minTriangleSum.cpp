#include <iostream>
#include <vector>
using namespace std;

// ===================================================================================
// recursive global state version
/*
starting is 0,0
we can end on any element in the last row
we can go [i+1][j] and [i+1][j+1]
looking for a min_sum
The answer will not exceed 109
*/
void helper_rec(int i, int j, int curr_sum, int &min_sum, vector<vector<int>> &triangle) {
    int n = triangle.size();
    if(i >= n) {
        min_sum = min(min_sum, curr_sum);
        return;
    }
    if(j >= triangle[i].size()) return;
    
    helper_rec(i+1, j,   curr_sum + triangle[i][j], min_sum, triangle);
    helper_rec(i+1, j+1, curr_sum + triangle[i][j], min_sum, triangle);
}
int _minTriangleSum1(vector<vector<int>>& triangle) {
    int min_sum = 1e9;
    helper_rec(0, 0, 0, min_sum, triangle);
    return min_sum;
}
// ===================================================================================
// recursion dp version, no memo
/*
express problem as [i][j]
dp[i][j] = m[i][j] + min(bot, bot_right)
*/ 
int helper_no_memo(int i, int j, vector<vector<int>> &triangle) {

    if(i == triangle.size() - 1) {
        return triangle[i][j];        
    }
    // if(i >= triangle.size()) {
    //     return 0;        
    // }

    int bot = triangle[i][j] + helper_no_memo(i+1, j, triangle);        
    int bot_right = triangle[i][j] + helper_no_memo(i+1, j+1, triangle);
    
    return min(bot, bot_right);
}
int _minTriangleSum2(vector<vector<int>>& triangle) {
    return helper_no_memo(0, 0, triangle);
}
// ===================================================================================
// recursion dp version, no memo
int helper_memo(int i, int j, vector<vector<int>> &triangle, vector<vector<int>> &dp) {

    if(i == triangle.size() - 1) {
        return triangle[i][j];
    }    

    if(dp[i][j] != -1) return dp[i][j];

    int bot = triangle[i][j] + helper_memo(i+1, j, triangle, dp);
    int bot_right = triangle[i][j] + helper_memo(i+1, j+1, triangle, dp);
    
    return dp[i][j] = min(bot, bot_right);
}
int _minTriangleSum3(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> dp;
    int m = 1;
    for(int i=0; i<n; i++) {
        dp.push_back(vector<int>(i+1, -1));        
    }
    return helper_memo(0, 0, triangle, dp);
}
// ===================================================================================
/*
  1
  4, 7
  4, 10, 50
-50, 5,   6, -100


make dp vec
  1
  5, 8
  9, 15, 58
-50, 5,   6, -100

top-down
    can add up and upper-left
    take the minimum
    but them well have to check the minimun in the last row

bottom-up
dp-last = matrix-last

from 2nd-last, dp[i][j] = m[i][j] + min(dp[i+1][j], dp[i+1][j-1])
*/
int _minTriangleSum4(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> dp;
    for(int i=0; i<n; i++) {
        dp.push_back(vector<int>(i+1, -1));
    }

    dp[n-1] = triangle[n-1];

    for(int i=n-2; i>=0; i--) {
        for(int j=0; j<triangle[i].size(); j++) {
            dp[i][j] = triangle[i][j] + min(dp[i+1][j], dp[i+1][j+1]);
        }
    }
    return dp[0][0];
}
// ===================================================================================
// lets reduce the space to only 2 vectors
int _minTriangleSum5(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> prev = triangle[n-1];    

    for(int i=n-2; i>=0; i--) {
        vector<int> curr(i+1);
        for(int j=0; j<triangle[i].size(); j++) {
            curr[j] = triangle[i][j] + min(prev[j], prev[j+1]);
        }
        prev = curr;
    }
    return prev[0];
}


int main2() {
    // [[1], [1, 2], [1, 2, 4]]
    // [[1], [4, 7], [4,10, 50], [-50, 5, 6, -100]]

    vector<vector<int>> triangle = {{1}, {1, 2},{1, 2, 4}};
    cout << _minTriangleSum1(triangle) << endl;
    cout << _minTriangleSum2(triangle) << endl;
    cout << _minTriangleSum3(triangle) << endl;
    cout << _minTriangleSum4(triangle) << endl;
    cout << _minTriangleSum5(triangle) << endl;    

    triangle = {{1},{4, 7},{4,10,50  }, {-50, 5,6, -100 }};
    cout << _minTriangleSum1(triangle) << endl;
    cout << _minTriangleSum2(triangle) << endl;
    cout << _minTriangleSum3(triangle) << endl;
    cout << _minTriangleSum4(triangle) << endl;
    cout << _minTriangleSum5(triangle) << endl;
    return 0;
}

// =====================================================
#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <algorithm>
using namespace std;


/*
triangle

each row has +1 element than the last

we can move bot or bot-R

find minimum sum


rec(int row, int idx)

    // we may look for an idx that doesnt exist
    // due to the triangle shape
    if(idx > row)
        return 0;

    if(row < 0 || idx < 0)
        return 0;

    int top = rec(row-1,idx)
    int top-left = rec(row-1, idx-1)

    return num[row][idx] + min(top, top-left)
*/

int rec(int row, int i, vector<vector<int>> &triangle) {

    // invalid row
    if(i<0 || i > row)
        return INT_MAX;

    if(row == 0)
        return triangle[0][0];
        

    int top = rec(row-1, i, triangle);
    int top_left = rec(row-1, i-1, triangle);

    int best = min(top, top_left);
    if(best == INT_MAX)
        return INT_MAX;

    return triangle[row][i] + best;
}


// 2 choices at each row
// n2^n time
// stack space n space
int minTriangleSum(vector<vector<int>>& triangle) {    
    int n = triangle.size();
    if(n == 0)
        return 0;

    int min_sum = INT_MAX;
    for(int i=0; i<triangle[n-1].size(); i++) {
        min_sum = min(min_sum, rec(n-1, i, triangle));
    }
    return min_sum;
}

int memo(int row, int i, vector<vector<int>> &triangle, vector<vector<int>> &dp) {

    // invalid row
    if(i < 0 || i > row)
        return INT_MAX;

    if(row == 0)
        return triangle[0][0];

    if(dp[row][i] != -1)
        return dp[row][i];
        

    int top = rec(row-1, i, triangle);
    int top_left = rec(row-1, i-1, triangle);

    int best = min(top, top_left);
    if(best == INT_MAX)
        return INT_MAX;

    return dp[row][i] = triangle[row][i] + best;
}

// n(n+1)/2 states
// n^2 time
// n^2 space
// n recursion stack space
int minTriangleSum2(vector<vector<int>>& triangle) {
    int n = triangle.size();
    if(n == 0)
        return 0;

    vector<vector<int>> dp(n);
    for(int i=0; i<n; i++) {
        dp[i].assign(i+1, -1);
    }


    int min_sum = INT_MAX;
    for(int i=0; i<triangle[n-1].size(); i++) {
        min_sum = min(min_sum, memo(n-1, i, triangle, dp));
    }
    return min_sum;
}


// tabulation
int minTriangleSum3(vector<vector<int>>& triangle) {
    int n = triangle.size();
    if(n == 0)
        return 0;

    vector<vector<int>> dp(n);
    dp[0].assign(1, triangle[0][0]);
    
    for(int i=1; i<n; i++) {
        dp[i].resize(i+1);

        for(int j=0; j<=i; j++) {
            int top = (i==j) ? INT_MAX : dp[i-1][j];
            int top_left = (j>0) ? dp[i-1][j-1] : INT_MAX;

            int best = min(top, top_left);
            dp[i][j] = triangle[i][j] + best;
        }        
    }

    return *min_element(dp[n-1].begin(), dp[n-1].end());
}

// tabulation
int minTriangleSum4(vector<vector<int>>& triangle) {
    int n = triangle.size();
    if(n == 0)
        return 0;

    vector<int> prev(1, triangle[0][0]);    
    
    for(int i=1; i<n; i++) {
        vector<int> curr(i+1);        

        for(int j=0; j<=i; j++) {
            int top = (i==j) ? INT_MAX : prev[j];
            int top_left = (j>0) ? prev[j-1] : INT_MAX;

            int best = min(top, top_left);
            curr[j] = triangle[i][j] + best;
        }
        prev = curr;
    }

    return *min_element(prev.begin(), prev.end());
}



int main() {

    vector<vector<int>> triangle = {{1}, {1, 2}, {1, 2, 4}};
    auto x = minTriangleSum(triangle);
    x = minTriangleSum2(triangle);
    x = minTriangleSum3(triangle);
    x = minTriangleSum4(triangle);

    triangle = {{1}, {4, 7}, {4,10, 50}, {-50, 5, 6, -100}};
    x = minTriangleSum(triangle);
    x = minTriangleSum2(triangle);
    x = minTriangleSum3(triangle);
    x = minTriangleSum4(triangle);
    return 0;
}