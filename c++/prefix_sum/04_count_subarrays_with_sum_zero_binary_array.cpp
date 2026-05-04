#include <iostream>
#include <vector>
using namespace std;

/*
===================================================================================================
You are given a binary array arr of length n (where each element is either 0 or 1).
Your task is to find the number of subarrays whose sum is equal to 0.
===================================================================================================

Input:
    arr = [0, 1, 0, 0]  

Output: 
    4

Explanation:
    The subarrays with sum = 0 are:
    [0] (index 0)
    [0] (index 2)
    [0] (index 3)
    [0, 0] (index 2–3)

-----------------------------

Input:
    arr = [0, 0, 1, 0, 0]

Output:
    6

Explanation:
    The subarrays with sum = 0 are:
    [0] (index 0)
    [0] (index 1)
    [0,0] (index 0–1)
    [0] (index 3)
    [0] (index 4)
    [0,0] (index 3–4)

===================================================================================================
*/

int main() {

    // arr = [0, 1, 0, 0] 
    // arr = [0, 1, 1, 1] 

    // sum(L,R) == 0
    // prefix[R] - prefix[L-1] == 0
    // prefix[R] == prefix[L-1]

    vector<int> v = {0, 1, 0, 0};

    int prefix_sum = 0;
    int subarray_count = 0;

    for(int i=0; i<v.size(); i++){
        int curr = v[i];
        if(prefix_sum + curr == prefix_sum){
            subarray_count++;
        }
        
        // add to prefix for next iteration
        prefix_sum += curr;
    }   
    
    cout << subarray_count << endl;

    return 0;
}



// prefix[R] - prefix[L-1] = sum(L,R) 

// find sum(L,R) == k

// for i,j look for sum(i,j) == k still n^2

// sum(L,R) == k
// prefix[R] - prefix[L-1] == k
// prefix[R] == k + prefix[L-1]
// prefix[L-1] == prefix[R] - k

// L is prev
// R is curr

// for count we dont need hashmap, but hash set
// lets store prefix for O(1) lookup
// 


/*
arr     = [1,1,1,1,1]
pref    = [1,2,3,4,5]

k   =   3
n   =   0   1   2   3   4
curr    1   1   1   1   1
pref    1   2   3   4   5


n=2

    [0,1]
    curr=1
    curr+old 2+1 == 3 == k
        count++

n==3
    curr =1
    3+1 = 4
        4-3 = 1
        count++
        index would have been i+1


*/