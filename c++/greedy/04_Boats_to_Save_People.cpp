#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
Boats to Save People
    [https://leetcode.com/problems/boats-to-save-people/description/]

    You are given an array people where people[i] is the weight of the 
    ith person, and an infinite number of boats where each boat can carry 
    a maximum weight of limit. Each boat carries at most two people at 
    the same time, provided the sum of the weight of those people is at 
    most limit.

    Return the minimum number of boats to carry every given person.

    Example 1:
        Input: people = [1,2], limit = 3
        Output: 1
        Explanation: 1 boat (1, 2)
        
    Example 2:
        Input: people = [3,2,2,1], limit = 3
        Output: 3
        Explanation: 3 boats (1, 2), (2) and (3)

    Example 3:
        Input: people = [3,5,3,4], limit = 5
        Output: 4
        Explanation: 4 boats (3), (3), (4), (5)


observation
    we can use a pick and skip approach
    this will eventually put combinations together
    1,2, limit=3
    2^n

    memoization
    dp[i] = num of boats so far

    but if we sort we can group smaller people together
    so we can reach limit sooner
    1,1,2,2,4, limit=4
    (1,1,2) (2) (4)

    what if this case arises?
    1,4,1,4 limit=5
    if we sort
    (1,1)(4)(4)
    if we dont
    (1,4) (1,4)?

    so sorting and linear scan from the left doesnt work

    but we can do 2 pointer
    1,4,1,4
    1,1,4,4
    L     R
    L+R <= limit

    if L + R <= limit
        L++
        R--
        boat++
    else
        R--

*/



int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    int boats = 0;

    int l = 0, r = people.size()-1;

    while(l<=r) {
        // both fit
        if(people[l] + people[r] <= limit) {
            l++;
            // r--;
            // boats++;
        }
        // only the R, problem has stated no one is above limit
        // else {
            // r--;
            // boats++;
        // }
        r--;
        boats++;
    }

    return boats;
}
int main() {
    vector<int> people = {3,5,3,4};
    int limit = 5;
    cout << numRescueBoats(people, limit) << endl;

    people = {1,4,1,4};
    limit = 5;
    cout << numRescueBoats(people, limit) << endl;
    return 0;
}
/*
Observation:

Always process the heaviest remaining person.

If the lightest cannot fit with them,
nobody can.

Otherwise pair them with the lightest.
*/