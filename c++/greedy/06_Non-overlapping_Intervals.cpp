#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void print(vector<vector<int>>& intervals){
    for(const auto& interval : intervals){
        cout << interval[0] << " " << interval[1] << endl;
    }
    cout << "\n";
}

int MaximumNonOverlappingIntervals(vector<vector<int>>& Intervals) {

    // print(Intervals);
    sort(Intervals.begin(), Intervals.end(), [](const vector<int>& a, const vector<int>& b){
        if(a[1] == b[1]){
            return a[0] < b[0];
        }
        return a[1] < b[1];
    });
    print(Intervals);

    int prev_end = -1;
    int remove_i = 0;
    for(const auto& i : Intervals) {
        int start   = i[0];
        int end     = i[1];

        // is start greater than previous end?
        // remove this interval
        if(start < prev_end){
            remove_i++;
        }
        else{
            // valid interval
            prev_end = end;
        }

    }
    return remove_i;
}



int main() {
    vector<vector<int>> intervals = { {1, 2}, {2, 3}, {3, 4}, {1, 3} };    
    cout << MaximumNonOverlappingIntervals(intervals) << endl;

    intervals = { {1, 3}, {1, 4}, {3, 5}, {3, 4}, {4, 5} };
    cout << MaximumNonOverlappingIntervals(intervals) << endl;
    return 0;
}