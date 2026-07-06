#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;


int activitySelection(vector<int> &start, vector<int> &finish) {
    vector<pair<int,int>> acts;
    for(int i=0; i<start.size(); i++) {
        acts.push_back({finish[i], start[i]});
    }

    // sort by finish and then by start
    sort(acts.begin(), acts.end());

    int count = 1;

    int prev_finish = acts[0].first;

    for(int i=1; i<acts.size(); i++) {

        int curr_start  = acts[i].second;
        int curr_finish = acts[i].first;

        if(curr_start > prev_finish) {
            prev_finish = curr_finish;
            count++;
        }            
    }
    return count;
}

int activitySelection2(vector<int> &start, vector<int> &finish) {

    vector<pair<int,int>> activities;

    for(int i=0; i<start.size(); i++) {
        activities.push_back({finish[i], start[i]});
    }

    // sort by finish and then by start
    sort(activities.begin(), activities.end());

    int count = 0;
    int prev_finish = INT_MIN;

    for (auto &[curr_finish, curr_start] : activities) {

        if(curr_start > prev_finish) {
            count++;
            prev_finish = curr_finish;            
        }            
    }
    return count;
}

int main() {

    vector<int> start =  {1, 3, 0, 5, 8, 5};
    vector<int> finish =  {2, 4, 6, 7, 9, 9};

    cout << activitySelection(start, finish) << endl;

    return 0;
}

/*
Activity Selection
    [https://www.geeksforgeeks.org/problems/activity-selection-1587115620/1]

    Given a set of activities, each with a start time and a finish time, 
    represented by the arrays start[] and finish[], respectively. A 
    single person can perform only one activity at a time, meaning no two 
    activities can overlap. Your task is to determine the maximum number 
    of activities that a person can complete in a day.

    Note: Start time and finish time cannot overlap, i.e., if a person 
    finishes an activity at time x, then they cannot start another 
    activity at time x.

    Example 1:
        Input: start[] = [1, 3, 0, 5, 8, 5], finish[] = [2, 4, 6, 7, 9, 9]
        Output: 4
        Explanation: A person can perform at most four activities. The 
        maximum set of activities that can be executed is {0, 1, 3, 4}

    Example 2:
        Input: start[] = [10, 12, 20], finish[] = [20, 25, 30]
        Output: 1
        Explanation: A person can perform at most one activity.

    Example 3:
        Input: start[] = [1, 3, 2, 5], finish[] = [2, 4, 3, 6]
        Output: 3
        Explanation: A person can perform activities 0, 1 and 3.
*/

/*


start[]  = [1, 3, 0, 5, 8, 5]
finish[] = [2, 4, 6, 7, 9, 9]

with this example we can only start the next activity if
activity finish < next start
    1 3 5 8
    2 4 7 9

    if we start with 
    0 8
    6 9

    another possibility
    1 3 5
    2 4 9

max if 4

one approach is pick not pick, recursive
    pick, see if next if valid
    skip

    at end return max_count

can we sort?
make pairs
[1, 3, 0, 5, 8, 5]
[2, 4, 6, 7, 9, 9]

1,2
3,4
0,6
5,7
8,9
5,9

why did sort by end time work but not sort by start time?
are we giving priority to shorter tasks?
how do we go from dp to this solution? or is there no relation?


Sort by finish.

Take first activity.

For every remaining activity

    if start > lastFinish
        take it

O(n log n)


going from dp to greedy

    Recursion

    ↓

    DP explores every possibility

    ↓

    Notice only finish time matters

    ↓

    Prove earliest finish is never worse

    ↓

    Replace O(n²) transitions
    with one greedy choice

*/