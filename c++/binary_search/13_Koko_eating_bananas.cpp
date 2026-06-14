#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Koko eating bananas

    A monkey is given n piles of bananas, where the 'ith' pile has 
    nums[i] bananas. An integer h represents the total time in hours to 
    eat all the bananas.

    Each hour, the monkey chooses a non-empty pile of bananas and eats k 
    bananas. If the pile contains fewer than k bananas, the monkey eats 
    all the bananas in that pile and does not consume any more bananas in 
    that hour.

    Determine the minimum number of bananas the monkey must eat per hour 
    to finish all the bananas within h hours.


    Ex 1:
        Input: n = 4, nums = [7, 15, 6, 3], h = 8
        Output: 5
        Explanation: If Koko eats 5 bananas/hr, he will take 2, 3, 2, and 1 
        hour to eat the piles accordingly. So, he will take 8 hours to 
        complete all the piles.  

    Ex 2:
        Input: n = 5, nums = [25, 12, 8, 14, 19], h = 5
        Output: 25
        Explanation: If Koko eats 25 bananas/hr, he will take 1, 1, 1, 1, and 
        1 hour to eat the piles accordingly. So, he will take 5 hours to 
        complete all the piles.
*/

/*

Koko eating bananas

div is ceil(num[i]/k)

so minimum is n bananas
    max is max of nums, because of ceil

    search [1..max(nums)]

    f(nums, k, h)
        sum=0
        for num in nums
            sum += ceil(num/k)
            if(sum > h) return h+1
        return sum

    int sum = f(nums, mid, h);    

    if sum > h        
        low = mid + 1
    else 
        ans = mid
        high = mid - 1
        
*/


/*
ceil(a / b)
=
(a + b - 1) / b
*/

// ceil(7/3) = 3

// ceil(6/3) = 2

// ceil divides the numerator into steps
//     for 3, 6/3 = 2; 7/3 = 8/3 = 9/3 = 3


//     so for 7/3, 7 should go >=9


int hours_needed(vector<int> &nums, int k) {
    long long hours = 0;

    for(int num : nums) {
        hours += (num + k - 1) / k; // ceil(num/k)
    }
    return hours;
}

int minimumRateToEatBananas(vector<int> &nums, int h) {
    int l = 1;
    int r = *max_element(nums.begin(), nums.end());

    int ans = r;

    while(l <= r) {
        int mid = l + (r-l)/2;
        
        if(hours_needed(nums, mid) <= h) {
            ans = mid; 
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return ans;
}

int main() {
    return 0;
}