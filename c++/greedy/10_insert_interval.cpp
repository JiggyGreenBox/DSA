#include <iostream>
#include <vector>
using namespace std;


vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {

    vector<vector<int>> ans;

    int i = 0;
    int n = intervals.size();

    // 1. BEFORE: intervals completely before newInterval
    /*
        [_,1]
        [_,2]
        [_,3]
        all safe to insert
        all are less than 4 [new_start]
    newInterval = [4,5]
    */
    while (i < n && intervals[i][1] < newInterval[0]) {
        ans.push_back(intervals[i]);
        i++;
    }

    // 2. OVERLAP: merge all overlapping intervals
    /*
        now we have merge cases
        [2,_]
        [4,_]
        [5,_]
        merge these because start <= newEnd
        [6,_] 6>5 so no merge
    newInterval = [4,5]
    */
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }

    // Write the merged interval exactly once
    ans.push_back(newInterval);

    // 3. AFTER: remaining intervals
    /*                
        [6,_] 6>5 so no merge
        [7,_] 6>5 so no merge
        [8,_] 6>5 so no merge
    newInterval = [4,5]
    since we took care of all cases, no checks required
    */
    while (i < n) {
        ans.push_back(intervals[i]);
        i++;
    }

    return ans;
}

void printIntervals(const vector<vector<int>>& Intervals){
    for(auto Interval : Intervals) {
        cout << "[ ";
        cout << Interval[0] << " " << Interval[1];
        cout << " ]\n";
    }
    cout << "\n";
}

int main() {
    vector<vector<int>> Intervals = { {1, 3} , {6, 9} };
    vector<int> newInterval = {2,5};
    // printIntervals(insertNewInterval(Intervals, newInterval));

    Intervals = { {1, 2} , {3, 5} , {6, 7} , {8,10} };
    newInterval = {4,8};
    printIntervals(insert(Intervals, newInterval));

    return 0;
}

/*
Insert Interval

Given a 2D array Intervals, where Intervals[i] = [start[i], end[i]] 
represents the start and end of the ith interval, the array 
represents non-overlapping intervals sorted in ascending order by 
start[i]. 

Given another array newInterval, where newInterval = [start, end] 
represents the start and end of another interval, merge newInterval 
into Intervals such that Intervals remain non-overlapping and sorted 
in ascending order by start[i].

Return Intervals after the insertion of newInterval.


Example 1

    Input : Intervals = [ [1, 3] , [6, 9] ] , newInterval = [2, 5]

    Output : [ [1, 5] , [6, 9] ]

    Explanation : After inserting the newInterval the Intervals array 
    becomes [ [1, 3] , [2, 5] , [6, 9] ].

    So to make them non overlapping we can merge the intervals [1, 3] and 
    [2, 5].

    So the Intervals array is [ [1, 5] , [6, 9] ].

Example 2

    Input : Intervals = [ [1, 2] , [3, 5] , [6, 7] , [8,10] ] , 
    newInterval = [4, 8]

    Output : [ [1, 2] , [3, 10] ]

    Explanation : The Intervals array after inserting newInterval is [ 
    [1, 2] , [3, 5] , [4, 8] , [6, 7] , [8, 10] ].

    We merge the required intervals to make it non overlapping.

    So final array is [ [1, 2] , [3, 10] ].

Example 3

    Input : Intervals = [ [1, 2] , [3, 5] , [6, 7] , [8,10] ] , 
    newInterval = [1, 8]

    Output:

    [ [1, 10] ]
*/

/*
Insert Interval
is this problem testing my coding skills more than my logic?

first approach:
    we are given intervals and just one newInterval
    return a new vector

    we can divide this into 3 parts:
        before - no modifications
        merge
        after  - no modifications

    for each interval
        before
        if curr_end < newInterval.start 
            ans.push_back(currInterval)

        after
        if curr_start > newInterval.end
            ans.push_back(currInterval)

        merge
            
            min = currStart, newStart
            max = currEnd, newEnd

            overwrite currentInterval


*/