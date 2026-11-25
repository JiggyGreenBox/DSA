#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm> 

using namespace std;

/*
either we start a new subarray or we dont
but because of negatives, if we come across another negative
the product could be large

[10,-5,10,10] ans=100
[10,-5,10,10,-5] ans=2500

kadanes breaks
    because we cant discard previous states

    -5 * -5
    at second -5, we could start, but also prev -5 gives +25

    for every index
        we can start a new subarray 
            nums[i]
        extend prevMin
            nums[i] * minEnding
        extend prevMax
            nums[i] * maxEnding
*/


/*
brute force is make every subarray
    check prod

there is a dp approach
    in max sum, we had f(i) / dp[i], is max sum ending at
        dp[i] = max(a[i], dp[i-1] + a[i])

    for max prod
        since we have negative numbers
            -2,3,-4, max==24

        we need to track negative also

    dpMax[i] = max prod ending at i
    dpMin[i] = min prod ending at i


    dpMax[i] = max( a[i], dpMax[i-1]*a[i], dpMin[i-1]*a[i])
    dpMin[i] = min( a[i], dpMax[i-1]*a[i], dpMin[i-1]*a[i])

    ans = max(ans, dpMax[i])
*/

int maxProduct1(vector<int>& nums) {
    int n = nums.size();
    vector<int> dpMax(n);
    vector<int> dpMin(n);
    dpMax[0] = nums[0];
    dpMin[0] = nums[0];
    int ans = nums[0];

    for(int i = 1; i < nums.size(); i++) {
        int x = nums[i];        

        dpMax[i] = max({x, dpMax[i-1] * x, dpMin[i-1] * x});
        dpMin[i] = min({x, dpMax[i-1] * x, dpMin[i-1] * x});

        ans = max(ans, dpMax[i]);
    }

    return ans;
}
/*
since we only depend on dp[i-1] we can space optimize it
*/
int maxProduct2(vector<int>& nums) {
    int maxProd = nums[0];
    int minProd = nums[0];
    int ans = nums[0];

    for(int i = 1; i < nums.size(); i++) {
        int x = nums[i];

        int newMax = max({
            x,
            maxProd * x,
            minProd * x
        });

        int newMin = min({
            x,
            maxProd * x,
            minProd * x
        });

        maxProd = newMax;
        minProd = newMin;

        ans = max(ans, maxProd);
    }

    return ans;
}

/*
we take 3 way comparision
    because nums[i] might be negative or positive
    if positive
        the max will increase
    if min
        tje max will become negative, and the min will become positive
        so we can swap here
*/
int maxProduct3(vector<int>& nums) {
    int maxProd = nums[0];
    int minProd = nums[0];
    int ans = nums[0];

    for(int i = 1; i < nums.size(); i++) {
        int x = nums[i];

        if(x < 0)
            swap(maxProd, minProd);

        maxProd = max(x, maxProd * x);
        minProd = min(x, minProd * x);

        ans = max(ans, maxProd);
    }

    return ans;
}



int main(){
    vector<int> v = {};
    v = {5,4,3,2,1};
    assert(maxProduct1(v) == 120);
    assert(maxProduct2(v) == 120);
    cout << maxProduct1(v) << endl; // 120

    v = {2, 3, 4, 5};
    cout << maxProduct1(v) << endl; // 120
    assert(maxProduct1(v) == 120);
    assert(maxProduct2(v) == 120);

    v = {7};
    cout << maxProduct1(v) << endl; // 7
    assert(maxProduct1(v) == 7);
    assert(maxProduct2(v) == 7);

    v = {-2, -3, -4};
    cout << maxProduct1(v) << endl; // 12
    assert(maxProduct1(v) == 12);
    assert(maxProduct2(v) == 12);

    v = {-2, -3, -4, -5};
    cout << maxProduct1(v) << endl; // 120
    assert(maxProduct1(v) == 120);
    assert(maxProduct2(v) == 120);

    v = {0, 2, 3, -2, 4};
    cout << maxProduct1(v) << endl; // 6
    assert(maxProduct1(v) == 6);
    assert(maxProduct2(v) == 6);

    v = {2, 3, -2, 4, 0};
    cout << maxProduct1(v) << endl; // 6
    assert(maxProduct1(v) == 6);
    assert(maxProduct2(v) == 6);

    v = {2, 3, 4, -5, 6, 7};
    cout << maxProduct1(v) << endl; // 42
    assert(maxProduct1(v) == 42);
    assert(maxProduct2(v) == 42);

    
    return 0;
}