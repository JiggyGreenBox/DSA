#include <iostream>
#include <vector>

using namespace std;


long long merge(vector<int> &nums, vector<int> &aux, int start, int  mid, int end) {   
    
    int inv_count = 0;

    // copy elements into aux
    for(int i=start; i<=end; ++i){
        aux[i] = nums[i];
    }    

    int i = start;
    int j = mid+1;
    int k = start; // insert pointer

    while(i<=mid && j<=end){
        if(aux[i] <= aux[j]){
            nums[k++] = aux[i++];
        }
        else{
            
            nums[k++] = aux[j++];
            // since both halves are sorted we add the entire greater list to inversions
            // L [2, 5, 8]
            // R [1, 7]
            // compare L <-> R, 2 > 1
            // now this means 2,5,8 are all greater than 1
            // the inversion list is (2,1),(5,1),(8,1)  its count of index-mid = (mid - index) + 1
            inv_count += (mid-i+1);
        }
    }

    // leftover elements
    while(i<=mid){
        nums[k++] = aux[i++];
    }

    return inv_count;
}

long long merge_sort(vector<int>& nums, vector<int>& aux, int start, int end) {
    
    long long inv_count = 0;

    if(start >= end) return 0;

    int mid = start + (end - start) / 2;

    inv_count += merge_sort(nums, aux, start, mid);
    inv_count += merge_sort(nums, aux, mid+1, end);
    inv_count += merge(nums, aux, start, mid, end);

    return inv_count;
}

long long numberOfInversions(vector<int> nums) {
    // long long int count = 0;
    // int n = nums.size();
    // // brute force
    // // n^2 solution for calculations?
    // for(int i=0; i<n; i++ ) {
    //     for(int j=i+1; j<n; j++ ) {
    //         if(nums[i] > nums[j]){
    //             ++count;
    //         }
    //     }
    // }

    // return count;

    long long count = 0;
    int n = nums.size();
    // nlog merge sort solution
    vector<int> aux(n);
    count = merge_sort(nums, aux, 0, n-1);
    for(auto x: nums){
        cout << x << " ";
    }
    cout << endl;

    return count;
}

int main() {
    vector<int> v = {2, 3, 7, 1, 3, 5};
    long long int ans = numberOfInversions(v);
    cout << ans;
    return 0;
}

/*

Count Inversions

Brute Force:
Check all pairs (i,j)
O(n²)

Merge Sort:

Invariant:
Left half sorted.
Right half sorted.

During merge:

if left[i] <= right[j]
    no inversion

if left[i] > right[j]
    all elements from left[i..mid]
    are greater than right[j]

count += (mid - i + 1)

Time: O(n log n)
Space: O(n)

*/