#include <iostream>
#include <vector>

using namespace std;

int findMin(vector<int>& arr){
    int start = 0;
    int end = arr.size()-1;
    int ans;

    while(start<=end){
        int mid = start + (end-start)/2;
        ans = arr[mid];

        // we are trying to find the pivot
        // compare start and end
        cout << arr[start];
        cout << " | ";
        cout << arr[mid];
        cout << " | ";
        cout << arr[end] << endl;

        if(arr[start] < arr[end]){
            if(arr[mid] < arr[end]){
                // left
                end = mid - 1;
            }
            else{
                // right
                start = mid + 1;
            }
        }
        else{
            if(arr[mid] < arr[start]){
                // left
                end = mid - 1;
            }
            else{
                // right
                start = mid + 1;
            }
        }
    }
    return ans;
}

int main(){
    vector<int> v = {90,-87,-78,-65,-49,-29,-28,-23,-2,7,12,14,24,40,46,55,76,77,80,83};
    cout << findMin(v) << endl;

    return 0;
}

/*
Find minimum in Rotated Sorted Array
invariant

The minimum is always inside [l, r].

Compare nums[mid] with nums[r].

nums[mid] > nums[r]
    minimum is to the right of mid

nums[mid] <= nums[r]
    minimum is at mid or to the left
*/