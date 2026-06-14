#include <iostream>
#include <vector>

using namespace std;


int wrong_lower_bound(vector<int>& nums, int val) {
    cout << "--------------------------"<< endl;
    int start = 0;
    int end = nums.size()-1;

    while(start < end){
        int mid = start + (end-start)/2;

        cout << "start: " << start << " | end: " << end << endl;
        cout << "\tmid: " << mid << " | " << nums[mid] << endl;

        // we want lower elements and first occurance        
        if(nums[mid] >= val){ // discard
            // end = mid -1 ;
            end = mid; // mid could be an answer
        }
        else{ //< keep
            start = mid + 1;
        }
    }
    cout << "--------------------------"<< endl;
    return start;
    
}

int lower_bound(vector<int>& nums, int val) {
    cout << "--------------------------"<< endl;
    int start = 0;
    int end = nums.size();

    while(start < end){
        int mid = start + (end-start)/2;

        cout << "start: " << start << " | end: " << end << endl;
        cout << "\tmid: " << mid << " | " << nums[mid] << endl;

        // we want lower elements and first occurance        
        if(nums[mid] >= val){ // discard
            // end = mid -1 ;
            end = mid; // mid could be an answer
        }
        else{ //< keep
            start = mid + 1;
        }
    }
    cout << "--------------------------"<< endl;
    return start;
}

// find element or next greater element
// discard < x
int lowerBound(vector<int> &nums, int x) {
    int n = nums.size();
    int low = 0, high = n;

    while(low < high) {
        int mid = low + (high-low) / 2;

        if(nums[mid] < x) {
            low = mid + 1;
        }
        else {
            high = mid; // we want >=, so mid 
        }
    }
    return low;
}

int main(){
    vector<int> v = {10, 20, 30, 30, 40, 50};
    int val = 30;
    cout << lower_bound(v, val) << endl;


    v = {1, 2, 3, 4, 5, 6};
    val = 7;
    cout << wrong_lower_bound(v, val) << endl; // 5, but it should be 6!
    // in STL we check like this
    /*
    int idx = lower_bound(v.begin(), v.end(), target) - v.begin();
    if (idx != v.size() && v[idx] == target)
        cout << "Found at index " << idx;
    else
        cout << "Not found, can be inserted at index " << idx;*/

    // notice != v.size()

    // also note since mid is now inclusive we can have start<=high
    return 0;
}