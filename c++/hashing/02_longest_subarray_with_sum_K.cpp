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


// negatives and zeros allowed
int longest_subarray_with_sum_K_cannon(vector<int>& nums, int k) {
    int n = nums.size();

    
    unordered_map<int, int> mpp; // sum, idx

    mpp[0] = -1;

    int prefix = 0;
    int max_len = 0;

    for(int i=0; i<n; i++) {

        prefix += nums[i];

        int search = prefix - k; 

        if(mpp.count(search)) {
            int len = i - mpp[search];
            max_len = max(max_len, len);
        }
        else {
            mpp[prefix] = i;
        }        
    }
    return max_len;
}

// only positives
// this works because adding elements increases the sum
// removing elements reduces the sum
// we use a while loop to account for 0s
int longest_subarray_with_sum_K_2_pointer_cannon(vector<int>& nums, int k) {
    int left = 0;
    int sum = 0;
    int maxLen = 0;

    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];

        // dont let sum be more than k
        // sum will be either less or exactly equal to k 
        // after the while loop
        while (left <= right && sum > k) {
            sum -= nums[left];
            left++;
        }

        if (sum == k)
            maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
}

/*
Subarray Sum K

Positive numbers:
    Sliding window
    Time: O(n)
    Space: O(1)

Negative numbers possible:
    Prefix sum + hashmap
    Time: O(n) average
    Space: O(n)
*/

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

