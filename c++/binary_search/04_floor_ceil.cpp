#include <iostream>
#include <vector>

using namespace std;

// a modification of upper and lower bound
int get_floor(vector<int> nums, int x) {
    int ans = -1;
    int start = 0;
    int end = nums.size();

    while(start < end) {
        int mid = start + (end-start) / 2;
        cout << mid << endl;
        cout << "nums[mid]: " << nums[mid]<< endl;

        if(nums[mid] <= x){
            // ans in in start..mid
            start = mid+1;
            cout << "new start: " << start << endl;
            ans = nums[mid]; // possible ans
            cout << "ans: " << ans << endl;
        }
        else{
            // mid was too large
            // discard upper half
            end = mid;
        }
    }
    return ans;
}

// a modification of upper and lower bound
int get_ceil(vector<int> nums, int x) {
    int ans = -1;
    int start = 0;
    int end = nums.size();

    while(start < end) {
        int mid = start + (end-start) / 2;
        cout << mid << endl;
        cout << "nums[mid]: " << nums[mid]<< endl;

        if(nums[mid] >= x){
            // mid is possible solution
            end = mid;
            cout << "new start: " << start << endl;
            ans = nums[mid]; // possible ans
            cout << "ans: " << ans << endl;
        }
        else{
            // mid < x
            // we dont need start..mid
            // discard lower half
            start = mid+1;
        }
    }
    return ans;
}


vector<int> getFloorAndCeil_brute(vector<int> nums, int x) {
    int floor = -1, ceil = -1;
    for(int num: nums){
        if(num <= x) floor = num;
        if(num >=x && ceil==-1) ceil = num;

        // if (num >= x && (ceil == -1 || num < ceil)) ceil = num;
        // editorial solution isnt clear to me
        // why is num < ceil checked, it will never happen in a sorted array
        // after checking, that condition is used for unsorted arrays as well

        // UNSORTED
        // if (num <= x && (floor == -1 || num > floor)) {
        //     floor = num;   // pick the largest ≤ x
        // }
        // if (num >= x && (ceil == -1 || num < ceil)) {
        //     ceil = num;    // pick the smallest ≥ x
        // }
    }
    return {floor, ceil};
}

vector<int> getFloorAndCeil(vector<int> nums, int x) {
    int floor = get_floor(nums, x);
    int ceil = get_ceil(nums, x);
    return {floor, ceil};
}

int main() {
    vector<int> v = {3, 4, 4, 7, 8, 10};
    int x = 8;
    vector<int> ans = getFloorAndCeil(v,x);

    for(auto i : ans) cout << i << endl;

    vector<int> ans2 = getFloorAndCeil_brute(v,x);

    for(auto i : ans2) cout << i << endl;
}
