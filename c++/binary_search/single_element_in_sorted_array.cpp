#include <iostream>
#include <vector>

using namespace std;

int singleNonDuplicate(vector<int> &nums) {
        // XOR
        // while loop
        // both are O(n)
        // but binary search will be log n
        // if every number appears twice then the array will be even
        // but since one number appears once the array is odd
        // so check mid, if the mid+1 is the same as mid then the number will be ahead
        // else its behind

        int start = 0;
        int end = nums.size() - 1;
        int ans = -1;

        while(start <= end) {

            int mid = start + (end-start)/2;
            cout << nums[start];
            cout << " | ";
            cout << nums[mid];
            cout << " | ";
            cout << nums[end] << endl;

            
            cout << start;
            cout << " | ";
            cout << mid;
            cout << " | ";
            cout << end << endl;
            cout << end << endl;
            ans = nums[mid];

            // ans is in the right half
            if(mid%2 == 0 && nums[mid] == nums[mid+1] || mid%2==1 && nums[mid] == nums[mid-1]){

            // if(nums[mid] == nums[mid+1]){
                
                start = mid + 1;
            }
            else if(nums[mid] != nums[mid-1] && nums[mid] != nums[mid+1]){
                return nums[mid];
                
            }
            else{
                end = mid - 1;
            }
        }

        return ans;
    }



int singleNonDuplicate2(vector<int> &nums) {
    int low = 0, high = nums.size() - 1;

    while(low < high) {
        int mid = low + (high-low)/2;

        cout << "low: " << low
             << " mid: " << mid
             << " high: " << high
             << endl;

        // make mid even for +1 check
        // [0,1] [2,3] [4,5]Z
        if(mid%2==1) {
            cout << "reducing odd mid: " << mid
                 << " to even mid: " << mid-1             
                 << endl;
            mid--; // if 2 elements, mid will always be 0
        }

        cout << "checking mid: " << mid
             << " and mid+1: " << mid+1             
             << endl;

        // [0,1] [2,3] [4,5]
        if(nums[mid] == nums[mid+1]){
            cout << "low = low +2: " << low;
            low = mid + 2;

            cout << "+2 = " << low
                 << endl;
        }
        // [0], [1,2]
        else{
            high = mid; // mid can be the answer
            cout << "high = mid: " << high << endl;
        }
    }
    return nums[low]; // handles single element, if 2 elements since sorted, return [0]
}

int main(){
    vector<int> v = {1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6};
    // cout << singleNonDuplicate(v) << endl;

    // v = {1, 1, 3, 5, 5};
    v = {1};
    v = {0,1};
    v = {0,1,1};
    // three elements 
    //      mid becomes [0,1,2] = 1
    //      we change mid to 0
    //      either [0,1] valid pair then low=mid+2
    //      or high = mid, which is kind of removing 2 elements, as we did mid--
    // v = {1,1,2};
    cout << singleNonDuplicate2(v) << endl;

    return 0;
}

// odd
// 122 3 344
// 112 2 334

// if mid is even and mid+1 is same choose right

// if mid is odd and mid-1 is same choose right


// else if mid+1 and mid-1 return
// else choose left


// 4, 5, 5, 6, 6
// 4, 4, 5, 5, 6
// 4, 4, 5, 6, 6

// even