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