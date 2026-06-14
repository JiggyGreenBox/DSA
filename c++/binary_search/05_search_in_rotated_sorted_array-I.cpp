#include <iostream>
#include <vector>

using namespace std;

int search_rotated_array(vector<int>& nums, int k){

    cout << "==============START=================" << endl;
    // 4, 5, 6, 7, 0, 1, 2

    int start = 0;
    int end = nums.size() - 1;
    int ans = -1;

    /*
    choose half

    if mid == target return

    1. find increasing half
    2. check if element is in the bounds
          2a. if yes, discard other half
          2b. else discard first half
    */

    while(start <= end) {
        int mid = start + (end-start)/2;       

        cout << "val: ";        
        cout << nums[start];
        cout << " | ";        
        cout << nums[mid];
        cout << " | ";
        cout << nums[end];
        cout << endl;

        cout << "idx: ";        
        cout << start;
        cout << " | ";        
        cout << mid;
        cout << " | ";
        cout << end;
        cout << endl;

        if(nums[mid] == k){
            cout << "==============DONE=================" << endl;
            return mid;
        }
        // find increasing half (no pivot)
        
        else if(nums[start] <= nums[mid]){
            if(k >= nums[start] && k < nums[mid]){
                // keep LEFT
                cout << "keep LEFT" << endl;
                end = mid - 1;
            }
            else{
                // discard LEFT
                cout << "keep RIGHT" << endl;
                start = mid + 1;
            }
        }
        else if(nums[mid] <= nums[end]){
            if(k > nums[mid] && k <= nums[end]){            
                // keep RIGHT
                cout << "keep RIGHT" << endl;
                start = mid + 1;
            }
            else{
                // discard RIGHT
                cout << "keep LEFT" << endl;
                end = mid - 1;
            }
        }
    }
    cout << "==============DONE=================" << endl;
    return ans;
}

int main(){
    vector<int> v = {4, 5, 6, 7, 0, 1, 2};
    int k = 0;

    // cout << search_rotated_array(v,k) << endl;


    v = {4, 5, 6, 7, 0, 1, 2};
    k = 3;
    // cout << search_rotated_array(v,k) << endl;

    v = {39,45,48,52,74,-82,-81,-77,-74,-70,-46,-37,-29,-28,-15,15,19,27,33};
    k = 52;
    // cout << search_rotated_array(v,k) << endl;


    v = {58,64,76,77,91,-91,-89,-75,-74,-71,-66,-53,-47,-34,-33,-28,-25,-15,-12,-7,-2,0,13,20,21,33,34,56};
    k = -71;
    // cout << search_rotated_array(v,k) << endl;


    v = {2,3,4,5,6,7,8,9,1};
    k = 9;
    cout << search_rotated_array(v,k) << endl;


    return 0;
}

/*
1. Find sorted half.
2. Check if target belongs to sorted half.
3. Keep it if yes.
4. Otherwise search the other half.
*/