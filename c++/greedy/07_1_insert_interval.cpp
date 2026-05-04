#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> insertNewInterval(vector<vector<int>>& Intervals, vector<int>& newInterval){
    vector<vector<int>> ans;
    // ans will contain merged intervals

    int new_start   = newInterval[0];
    int new_end     = newInterval[1];

    int n = Intervals.size();

    // check insert before first interval
    if(new_end < Intervals[0][0]){
        ans.push_back(newInterval);
    }
    
    int i=0;
    while(i<n) {
        vector<int> Interval = Intervals[i];

        // check if interval has no overlap
        int i_start = Interval[0];
        int i_end   = Interval[1];
        
        // current interval isnt in range
        if(i_end < new_start || i_start > new_end) {
            ans.push_back(Interval);
            i++;
        }
        else {
            int save_1 = min(i_start, new_start);
            if(new_end < i_end) {
                ans.push_back({save_1, i_end});
            }
            else{
                // new_end >= i_end
                int save_2=max(new_end, i_end);

                // need to check further intervals
                i++;
                while(i<n){
                    if(Intervals[i][0] >= save_2 || save_2<=Intervals[i][1]){
                        save_2 = Intervals[i][1];
                    }
                    i++;
                }
                ans.push_back({save_1, save_2});
            }
        }
    }    

    // check last interval
    if(new_start > Intervals[n-1][1]){
        ans.push_back(newInterval);
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