#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> insertNewInterval(vector<vector<int>>& Intervals, vector<int>& newInterval){
    // 3 stages
    // completely before
    // overlapping intervals
    // completely after
    int i = 0;
    int n = Intervals.size();
    vector<vector<int>> ans;

    // completely before
    while(i<n && Intervals[i][1] < newInterval[0]){
        ans.push_back(Intervals[i]);
        i++;
    }

    // overlapping intervals
    while(i<n && Intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], Intervals[i][0]);
        newInterval[1] = max(newInterval[1], Intervals[i][1]);
        i++;
    }
    // this takes care of both cases where there is no overlap
    //      either all elements were inserted already, or yet to be
    ans.push_back(newInterval); 

    // completely after
    while(i<n){
        ans.push_back(Intervals[i]);
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
    printIntervals(insertNewInterval(Intervals, newInterval));


    // vector<int> v = {1,5,5,5,5,5,2,3};

    // for(vector<int>::iterator it = v.begin(); it!= v.end(); ){
    //     if(*it == 5) {
    //         it = v.erase(it);
    //     }
    //     else{
    //         it++;
    //     }
    // }

    // for(auto x : v) cout << x << " ";

    return 0;
}