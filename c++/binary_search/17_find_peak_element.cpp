#include <bits/stdc++.h>
using namespace std;

int findPeakElement(vector<int> &arr) {
    int n = arr.size();

    for(int i=0; i<n; i++) {
        bool left_ok = (i==0 || arr[i] > arr[i-1]);
        bool right_ok = (i==n-1 || arr[i] > arr[i+1]);
        if(left_ok && right_ok) {
            return i;
        }
    }
    return -1;
}

int findPeakElement2(vector<int> &arr) {
    int n = arr.size();
    if(n==0) return -1;
    int l = 0, r = n - 1;
    
    while(l < r) {
        int mid = l + (r-l)/2;
        // 0, n-1        

        if(arr[mid] < arr[mid+1]) {
            l = mid + 1;
        }
        else {
            r = mid; // mid is possible answer
        }
    }
    return l;
}

void print(const vector<int>& v){
    for(auto x : v){
        cout << x << " ";
    }
    cout << "\n";

    int idx=0;
    for(auto x : v){
        cout << idx++ << " ";
    }
    cout << "\n";
}

int main(){
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 5, 1};
    // v = {1};
    // v = {1,2};
    // v = {2,1};

    print(v);
    cout << findPeakElement2(v) << endl;
    return 0;
}

/*
Invariant:
    At least one peak exists in [l,r]

Observation:
    nums[mid] < nums[mid+1]
        increasing slope
        peak must be on the right

    nums[mid] > nums[mid+1]
        decreasing slope
        peak is at mid or on the left

Discard Rule:
    increasing -> l = mid + 1
    decreasing -> r = mid
*/