/*
Corporate Flight Bookings
    [https://leetcode.com/problems/corporate-flight-bookings/description/]

There are n flights that are labeled from 1 to n.

You are given an array of flight bookings bookings, where bookings[i] 
= [firsti, lasti, seatsi] represents a booking for flights firsti 
through lasti (inclusive) with seatsi seats reserved for each flight 
in the range.

Return an array answer of length n, where answer[i] is the total 
number of seats reserved for flight i.

 

Example 1:

    Input: bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
    Output: [10,55,45,25,25]
    Explanation:
    Flight labels:        1   2   3   4   5
    Booking 1 reserved:  10  10
    Booking 2 reserved:      20  20
    Booking 3 reserved:      25  25  25  25
    Total seats:         10  55  45  25  25
    Hence, answer = [10,55,45,25,25]

Example 2:

    Input: bookings = [[1,2,10],[2,2,15]], n = 2
    Output: [10,25]
    Explanation:
    Flight labels:        1   2
    Booking 1 reserved:  10  10
    Booking 2 reserved:      15
    Total seats:         10  25
    Hence, answer = [10,25]
*/

#include <vector>
using namespace std;
vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> ans(n, 0);

    for(auto& b : bookings) {
        for(int i=b[0]; i<=b[1]; i++) {
            ans[i-1] += b[2];
        }
    }
    return ans;
}


// this is 1 based, so range of [1,n] becomes [0,n-1]
// [1,2,25]

// 0   1 2
// +25  -25
vector<int> corpFlightBookings2(vector<vector<int>>& bookings, int n) {
    vector<int> diff(n + 1);

    for(auto &b : bookings) {
        int l = b[0];
        int r = b[1];
        int val = b[2];

        diff[l-1] += val;
        diff[r]   -= val;
    }

    for(int i=1; i<n; i++) {
        diff[i] += diff[i-1];
    }
    
    diff.pop_back();

    return diff;
}

int main() {
    vector<vector<int>> bookings = {{1,2,10},{2,3,20},{2,5,25}};
    int n = 5;
    

    bookings = {{1,2,10},{2,3,20},{2,5,25}}; n = 5;

    bookings = {{1,2,10},{2,2,15}}; n = 2;
    auto ans = corpFlightBookings(bookings, n);
    auto ans1 = corpFlightBookings2(bookings, n);
    int x = 5;
    
    return 0;
}

/*
this solution above is the brute force

theres a difference array concept we need to learn

    A = [0, 0, 0, 0, 0]
    We want to add 10 to indices [1, 3].


    A = [0, 10, 10, 10, 0]
        we touched 3 elements

    
    index:  0   1   2   3   4
    value:  0  10  10  10   0
                ↑       ↑
              +10      -10

    diff = [0, +10, 0, 0, -10]

    How do we get the actual array from diff array
        diff:       [0, 10, 0, 0, -10]
                    ↓
        prefix:     [0, 10, 10, 10, 0]

    
    A = [0,0,0,0,0]
        [1,3] += 10
        [2,4] += 20
        [0,2] += 5

    with brute force this is
        3 + 3 + 3 = 9 elements

    [1,3] += 10
        diff[1] += 10
        diff[4] -= 10

    [2,4] += 20
        diff[2] += 20
        diff[5] -= 20
    
    [0,2] += 5
        diff[0] += 5
        diff[3] -= 5

    one prefix to get the final array

----
    for flight booking we do
    
        diff[l - 1] += seats;
        diff[r] -= seats;


    for a 0 based index
    diff[l]   += val
    diff[r-1] -= val
*/