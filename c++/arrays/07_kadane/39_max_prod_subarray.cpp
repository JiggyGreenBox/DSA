#include <iostream>
#include <vector>
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

int maxProduct(vector<int>& nums) {
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

int maxProduct(vector<int>& nums) {
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

int main(){
    vector<int> v = {};
    v = {5,4,3,2,1};
    cout << maxProduct(v) << endl;

    v = {2, 3, 4, 5};
    cout << maxProduct(v) << endl;

    v = {7};
    cout << maxProduct(v) << endl;

    v = {-2, -3, -4};
    cout << maxProduct(v) << endl;

    v = {-2, -3, -4, -5};
    cout << maxProduct(v) << endl;

    v = {0, 2, 3, -2, 4};
    cout << maxProduct(v) << endl;

    v = {2, 3, -2, 4, 0};
    cout << maxProduct(v) << endl;

    v = {2, 3, 4, -5, 6, 7};
    cout << maxProduct(v) << endl;

    
    return 0;
}