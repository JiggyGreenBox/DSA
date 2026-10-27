#include <iostream>
#include <vector>
using namespace std;

/*
Longest Bitonic Subsequence

    Given an array arr of n integers, the task is to find the length of 
    the longest bitonic sequence. A sequence is considered bitonic if it 
    first increases, then decreases. The sequence does not have to be 
    contiguous.
*/

/*
similar to LIS
    we find longest increasing sequence, then we find longest decreasing 
    sequence.

    dp1[1,1,2,3,4,2]
    dp2[1,1,3,2,1,1]

    then max of dp1[1] + dp2[2]
*/

int LongestBitonicSequence(vector<int> arr) {
    int n = arr.size();

    vector<int> dp1(n, 1), dp2(n, 1);
    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            if(arr[j] < arr[i]) {
                dp1[i] = max(dp1[i], 1 + dp1[j]);
            }
        }
    }

    for(int i=n-1; i>=0; i--) {
        for(int j=n-1; j>i; j--) {
            if(arr[j] < arr[i]) {
                dp2[i] = max(dp2[i], 1 + dp2[j]);
            }
        }
    }    

    int ans = 0;
    for(int i=0; i<n; i++) {
        ans = max(ans, dp1[i] + dp2[i] - 1);
    }
    return ans;

    // Does the problem require BOTH an increase and a decrease?
    // [1,2,3,4], no decrease, would be dp1[4] + dp2[1] -1 = 4
    // might be wrong on some platforms
    // if(inc[i] > 1 && dec[i] > 1)
    //     ans = max(ans, inc[i] + dec[i] - 1);
}

int main() {
    vector<int> v = {5, 1, 4, 2, 3, 6, 8, 7};
    cout << LongestBitonicSequence(v) << endl;
    return 0;
}
