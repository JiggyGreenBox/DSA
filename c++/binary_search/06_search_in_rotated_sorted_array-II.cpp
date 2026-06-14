#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchInARotatedSortedArrayII(vector<int> &nums, int k)  {
        int start = 0;
        int end = nums.size()-1;

        while(start <= end){
            while(nums[start+1] == nums[start]) ++start;
            while(nums[end-1] == nums[end]) --end;
            int mid = start + (end-start)/2;

            // find sorted half
            if(nums[mid] == k) return true;
            // check if left half is ascending
            else if(nums[start] <= nums[mid]){
                if(nums[start] <= k && k < nums[mid]){
                    // keep LEFT
                    end = mid-1;
                }
                else{
                    // keep RIGHT
                    start = mid+1;
                }
            }
            // right half must be ascending
            else{
                if(nums[mid] < k && k <= nums[end]){
                    // keep RIGHT
                    start = mid+1;
                }
                else{
                    // keep LEFT
                    end = mid-1;
                }
            }
        }
        return false;
    }

    bool searchInARotatedSortedArrayII_correct(vector<int> &nums, int target){
        int l = 0;
        int r = nums.size() - 1;

        while(l <= r){
            int mid = l + (r-l)/2;

            if(nums[mid] == target) return true;

            // Ambiguous case caused by duplicates
            if (nums[l] == nums[mid] &&
                nums[mid] == nums[r]) {
                l++;
                r--;
            }
            // Left half is sorted
            else if (nums[l] <= nums[mid]) {

                if (nums[l] <= target &&
                    target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }

            // Right half is sorted
            else {

                if (nums[mid] < target &&
                    target <= nums[r]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }            
        }
        return false;
    }
};




int main() {
    // vector<int> arr = {7, 8, 1, 2, 3, 3, 3, 4, 5, 6};
    // int target = 3; 

    vector<int> arr = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int target = 1;

    // Create an instance of the Solution class
    Solution sol;

    // Function call to search for the target element
    bool result = sol.searchInARotatedSortedArrayII(arr, target);

    if (!result)
        cout << "Target is not present.\n";
    else
        cout << "Target is present in the array.\n";

    return 0;
}

/*

searchInARotatedSortedArrayII

invariant
find the sorted half
    if num in sorted half, keep
    else discard

since we have duplicates
    comparisions can be different
    3..3..3
    l..m..h
    which side do we choose?
    while n[l] == m[m] && m[m] == m[h]
        l++; h--

*/