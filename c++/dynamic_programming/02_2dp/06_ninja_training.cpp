#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;


/*
========================================================================================
{10, 40, 70}
{20, 50, 80}
{30, 60, 90}

r,c

global recursion
    maintain a max_sum
*/
void backtrack(int r, int c, int curr_sum, vector<vector<int>> &matrix, int &max_sum) {

    if(r == matrix.size()) {
        max_sum = max(max_sum, curr_sum);
        return;
    }

    for(int i=0; i<3; i++) {
        if(i == c) continue;
        backtrack(r+1, i, curr_sum + matrix[r][i], matrix, max_sum);
    }
}
int ninjaTraining_backtrack(vector<vector<int>>& matrix) {
    int max_sum = 0;
    backtrack(0, -1, 0, matrix, max_sum);
    return max_sum;
}
// =======================================================================================

/*
each row of the matrix is a day
but the activity also is a factor
f[n] = max(f[n][0], f[n][1], f[n][2])

f[i][j] = a[i][j] + helper(i-1,j)

helper(int row, int col)
    if(row > 0) return 0;

    int max = INT_MIN;
    for(i=0;i<3; i++) {
        if(i==col) continue;
        max = max(max, helper(row-1, i));
    }
    return max;



{10, 40, 70}
{20, 50, 80}
{30, 60, 90}
*/
int f(int day, int last, vector<vector<int>> &matrix) {
    if(day < 0) return 0;

    int best = 0;
    for(int i=0; i<3; i++) {
        if(i == last) continue;
        best = max(best, matrix[day][i] + f(day-1, i, matrix));
    }
    return best;
}

int ninjaTraining_rec_state(vector<vector<int>>& matrix) {
    int n = matrix.size();    
    return f(n-1, 3, matrix);
}
// =======================================================================================
int fm(int day, int last, vector<vector<int>> &matrix, vector<vector<int>> &dp) {
    int best = 0;
    if(day == 0) {        
        for(int i=0; i<3; i++) {
            if(i == last) continue;
            best = max(best, matrix[0][i]);
        }
        // return best;
        return dp[day][last] = best;
    }

    if(dp[day][last] != -1) return dp[day][last];

    for(int i=0; i<3; i++) {
        if(i == last) continue;
        best = max(best, matrix[day][i] + fm(day-1, i, matrix, dp));
    }
    return dp[day][last] = best;
}
int ninjaTraining_memo(vector<vector<int>>& matrix) {
    int n = matrix.size();    
    vector<vector<int>> dp(n, vector<int>(4, -1));
    return fm(n-1, 3, matrix, dp);
}

// =======================================================================================
/*
how to think about tabulation
dp[n][3]

for(0,1,2)
    dp[0][i] = m[0][i]

for(day -> 1..n-1)
    for(last -> 0,1,2)
        dp[day][last] = max(dp[day-1][last+1%3], dp[day-1][last+1%3]) + m[day][last]

return max({dp[n-1][0], dp[n-1][1], dp[n-1][2]})
*/
int ninjaTraining_tab(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> dp(n, vector<int>(3, 0));

    dp[0][0] = matrix[0][0];
    dp[0][1] = matrix[0][1];
    dp[0][2] = matrix[0][2];

    for(int i=1; i<n; i++) {
        dp[i][0] = matrix[i][0] + max(dp[i-1][1], dp[i-1][2]);
        dp[i][1] = matrix[i][1] + max(dp[i-1][0], dp[i-1][2]);
        dp[i][2] = matrix[i][2] + max(dp[i-1][0], dp[i-1][1]);
    }
    return max({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
}

int ninjaTraining_tab2(vector<vector<int>>& matrix) {
    int n = matrix.size();    

    int prev0 = matrix[0][0];
    int prev1 = matrix[0][1];
    int prev2 = matrix[0][2];

    for(int i=1; i<n; i++) {
        int curr0 = matrix[i][0] + max(prev1, prev2);
        int curr1 = matrix[i][1] + max(prev0, prev2);
        int curr2 = matrix[i][2] + max(prev0, prev1);

        prev0 = curr0;
        prev1 = curr1;
        prev2 = curr2;
    }
    return max({prev0, prev1, prev2});
}


int main() {
    vector<vector<int>> matrix = {{10, 40, 70}, {20, 50, 80}, {30, 60, 90}};
    cout << ninjaTraining_backtrack(matrix) << endl;
    cout << ninjaTraining_rec_state(matrix) << endl;
    cout << ninjaTraining_memo(matrix) << endl;
    cout << ninjaTraining_tab(matrix) << endl;
    cout << ninjaTraining_tab2(matrix) << endl;
    
    

    matrix = {{70, 40, 10}, {180, 20, 5}, {200, 60, 30}};
    cout << ninjaTraining_backtrack(matrix) << endl;
    cout << ninjaTraining_rec_state(matrix) << endl;
    cout << ninjaTraining_memo(matrix) << endl;
    cout << ninjaTraining_tab(matrix) << endl;
    cout << ninjaTraining_tab2(matrix) << endl;
}

int ninjaTraining_cannonical_tabulation(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> dp(n, vector<int>(4, 0));

    // Base case (day = 0)
    dp[0][0] = max(matrix[0][1], matrix[0][2]); // cant use 0
    dp[0][1] = max(matrix[0][0], matrix[0][2]); // cant use 1
    dp[0][2] = max(matrix[0][0], matrix[0][1]); // cant use 2
    dp[0][3] = max({matrix[0][0], matrix[0][1], matrix[0][2]}); // max of all

    // Fill table
    for(int day = 1; day < n; day++) {
        for(int last = 0; last < 4; last++) { // [0,1,2,3] (3 has no restriction)
            int best = 0;

            for(int act = 0; act < 3; act++) { // 0,1,2 no 3 here
                if(act == last) continue; // skip the restriction
                best = max(best, matrix[day][act] + dp[day-1][act]);
            }

            dp[day][last] = best; // since choices are [0,1,2,3].. only 3 will do a max on all acts
            // the other do a max on 2 activities
        }
    }

    return dp[n-1][3];
}


/*
total states 4*n
    3 checks
4n time
4n space  
    n stack space
*/
int memo(int day, int last, vector<vector<int>> &matrix, vector<vector<int>> &dp) {
    if(day < 0)
        return 0;

    if(dp[day][last] != -1)
        return dp[day][last];

    // iterate over matrix
    int max_points = 0;
    for(int i=0; i<3; i++) {

        if(i == last)
            continue;

        int points = matrix[day][i] + memo(day-1, i, matrix, dp);
        max_points = max(max_points, points);
    }

    return dp[day][last] = max_points;
}

int ninjaTraining_memo(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> dp(n, vector(4, -1)); // [0,1,2,3], 3 is no restriction
    return memo(matrix.size()-1, 3, matrix, dp);
}

#include <vector>
#include <algorithm>
using namespace std;

// Time: O(n * 4 * 3) = O(n)
// Space: O(n * 4) = O(n)

int ninjaTraining_tab(vector<vector<int>>& points) {
    int n = points.size();
    if (n == 0) return 0;

    // dp[day][last]:
    // Maximum points through 'day',
    // where activity 'last' cannot be selected on that day.
    // last = 3 means no activity is forbidden.

    vector<vector<int>> dp(n, vector<int>(4, 0));

    // Base case: day 0
    for (int last = 0; last < 4; last++) {
        for (int task = 0; task < 3; task++) {
            if (task == last)
                continue;

            dp[0][last] = max(dp[0][last], points[0][task]);
        }
    }

    // Build the table from day 1 to day n-1
    for (int day = 1; day < n; day++) {
        for (int last = 0; last < 4; last++) {
            for (int task = 0; task < 3; task++) {
                if (task == last)
                    continue;

                int total = points[day][task]
                          + dp[day - 1][task];

                dp[day][last] = max(dp[day][last], total);
            }
        }
    }

    return dp[n - 1][3];
}

#include <vector>
#include <algorithm>
using namespace std;

// Time: O(n * 4 * 3) = O(n)
// Auxiliary space: O(4) = O(1)

int ninjaTraining(vector<vector<int>>& points) {
    int n = points.size();
    if (n == 0) return 0;

    // prev[last] = maximum points through the previous day,
    // where 'last' is the task forbidden on that day.
    vector<int> prev(4, 0);

    // Base case: day 0
    for (int last = 0; last < 4; last++) {
        for (int task = 0; task < 3; task++) {

            if (task == last) 
                continue;

            prev[last] = max(prev[last], points[0][task]);
        }
    }

    // Process remaining days
    for (int day = 1; day < n; day++) {
        vector<int> curr(4, 0);

        for (int last = 0; last < 4; last++) {
            for (int task = 0; task < 3; task++) {
                
                if (task == last) 
                    continue;

                int total = points[day][task] + prev[task];
                curr[last] = max(curr[last], total);
            }
        }

        prev = curr;
    }

    return prev[3];
}