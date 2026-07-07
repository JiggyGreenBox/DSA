#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void print(const vector<pair<int, int>>& meetings) {
    for(const auto& p : meetings) {
        cout << p.first << " " << p.second << endl;
    }
}

int maxMeetings(vector<int>& start, vector<int>& end) {
    int n = end.size();
    vector<pair<int,int>> meetings;
    for(int i=0; i<n; i++){
        meetings.push_back({end[i], start[i]});
    }

    sort(meetings.begin(), meetings.end());
    // print(meetings);

    int prev_end = 0;
    int max_meetings = 0;
    for(const auto& p : meetings){
        int start = p.second;
        int end = p.first;

        // meeting is possible
        if(start > prev_end){
            prev_end = end;
            max_meetings++;
        }
    }
    return max_meetings;
}

int main() {
    vector<int> start = {1, 3, 0, 5, 8, 5};
    vector<int> end   = {2, 4, 6, 7, 9, 9};    

    cout << maxMeetings(start, end) << endl;

    end = {20, 25, 30};
    start = {10, 12, 20};

    cout << maxMeetings(start, end) << endl;

    return 0;
}

/*
N meetings in one room

Given one meeting room and N meetings represented by two arrays, 
start and end, where start[i] represents the start time of the ith 
meeting and end[i] represents the end time of the ith meeting, 
determine the maximum number of meetings that can be accommodated in 
the meeting room if only one meeting can be held at a time.

Example 1
    Input : Start = [1, 3, 0, 5, 8, 5] , End = [2, 4, 6, 7, 9, 9]
    Output : 4
    Explanation : The meetings that can be accommodated in meeting room 
    are (1,2) , (3,4) , (5,7) , (8,9).

Example 2
    Input : Start = [10, 12, 20] , End = [20, 25, 30]
    Output : 1
    Explanation : Given the start and end time, only one meeting can be 
    held in meeting room.

Example 3
    Input : Start = [1, 4, 6, 9] , End = [2, 5, 7, 12]
    Output: 4




*/

/*
approach
*/