#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int longest_subarray_with_sum_K_brute(vector<int>& nums, int k) {
    // brute force
    // n^2 get sum
    // if == k, max the count
    int max_length = 0;
    int n = nums.size();
    for(int i=0; i<n; i++){
        int sum = 0;
        for(int j=i; j<n; j++) {
            sum += nums[j];
            cout << "sum: " << sum << endl;
            if(sum == k){
                int length = j-i+1;
                cout << "length: " << length << endl;
                max_length = max(max_length, length);
            }
        }
    }
    return max_length;
}

int longest_subarray_with_sum_K(vector<int>& nums, int k) {

    int n = nums.size();

    int max_length = 0;

    // there may be multiple solutions
    // where sum of some elements equal to k
    // this is solved with a prefix array
    // [1, (1+2), (1+2+3)...]
    // then the sum between L,R = prefix[R] - prefix[L-1] for L>0 OR sum(L,R) = prefix[R] for L=0
        // to make a universal function, lets handle L=0 case, 
        // that means prefix[L-1] = 0 for L=0 will allow the sum formula to work
        // at L=0 L-1= -1, with sum=0
        // map[0] = -1

    // our solution is satisfied when sum(L,R) = K
    // calculate length and return max length for each subarray(continuous)

    // prefix[R] - prefix[L-1] = k
    // prefix[R] = k - prefix[L-1] // not useful here
    // prefix[L-1] = prefix[R] - k

    // lets store prefix and the index in a hashmap
    // index is for length calculation
    // prev prefix is prefix[L-1]

    // then add the current element for the next run
    // we can check it in the loop

    int prefix_sum = 0;
    unordered_map<int, int> mpp; // prefix_sum, index

    for(int i=0; i<n; i++) {

        int curr = nums[i];

        cout << "curr: " <<  curr << " | ";
        cout << "prev_prefix: " <<  prefix_sum << " | ";
        cout << "lookup: " <<  abs(prefix_sum - k) << endl;

        // // new element is a solution, from index 0
        // if(prefix_sum + curr == k){
        //     max_length = max(max_length, i+1);
        // }
        // else{

        // }

        // check prev_prefix
        if(mpp.find(prefix_sum - k) != mpp.end()) {

            cout << "found in map at: " <<  mpp[prefix_sum - k] << endl;

            int length = i - mpp[prefix_sum - k] + 1;

            cout << "length: " << length << endl;

            max_length = max(max_length, length);

            cout << "max_length: " << max_length << endl;
        }

        // compute current prefix
        prefix_sum += curr;
        mpp[prefix_sum] = i;
    }

    // print mpp
    for(auto pair : mpp){
        cout << pair.first << " : " << pair.second << endl;
    }


    return max_length;
}

// negatives and zeros allowed
int longest_subarray_with_sum_K_cannon(vector<int>& nums, int k) {
    int n = nums.size();

    int prefix_sum = 0;
    int max_len = 0;
    unordered_map<int, int> mpp; // sum, idx
    mpp[0] = -1;

    for(int i=0; i<n; i++) {
        prefix_sum += nums[i];
        if(mpp.find(prefix_sum - k) != mpp.end()) {
            int len = i - mpp[prefix_sum - k];
            max_len = max(max_len, len);
        }

        if(mpp.find(prefix_sum) == mpp.end()) {
            mpp[prefix_sum] = i;
        }
    }
    return max_len;
}

// only positives
int longest_subarray_with_sum_K_2_pointer_cannon(vector<int>& nums, int k) {
    int n = nums.size();
    int left = 0, right = 0;
    int max_len = 0;
    int sum = 0;

    while(right < n) {
        sum += nums[right];
        if(left <= right && sum > k) {
            sum -= nums[left];
            left++;
        }

        if(sum == k) {
            max_len = max(max_len, right - left + 1);
        }

        right++;
    }

    return max_len;
}

int main() {
    vector<int> v = {10, 5, 2, 7, 1, 9};
    int k = 15;


    // v = {2, 0, 0, 0, 1};
    // k = 3;

    int ans = longest_subarray_with_sum_K_brute(v, k);
    cout << ans << endl;
    // int ans = longest_subarray_with_sum_K(v, k);
    ans = longest_subarray_with_sum_K_2_pointer_cannon(v, k);
    cout << ans << endl;
    return 0;
}

// curr_sum - sum_before = k    // valid solution
// curr_sum  = k - sum_before  // valid solution


// curr_sum = 0
// sum_before  = 0
// k= 15


// need quick lookup for prefix sum
// we can find the sum between 2 elements with the formula
// sum(L,R) = prefix[R] - prefix[L] for L>0 or prefix[R] for L=0

// if we know R, and have a target, we can search for L 
// with sum(L,R) == target
// this will take n^2 without a lookup

// so we store prefix[x] - target for each x
// check element first for a match
// if found 
// else
// add to sum minus target and store index

// hashmap(15-5) -> exists ()

 // TODO
 // this is wrong code
