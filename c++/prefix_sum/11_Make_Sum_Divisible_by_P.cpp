#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
Make Sum Divisible by P
    [https://leetcode.com/problems/make-sum-divisible-by-p/description/]

Given an array of positive integers nums, remove the smallest 
subarray (possibly empty) such that the sum of the remaining elements 
is divisible by p. It is not allowed to remove the whole array.

Return the length of the smallest subarray that you need to remove, 
or -1 if it's impossible.

A subarray is defined as a contiguous block of elements in the array.
 

Example 1:

    Input: nums = [3,1,4,2], p = 6
    Output: 1
    Explanation: The sum of the elements in nums is 10, which is not 
    divisible by 6. We can remove the subarray [4], and the sum of the 
    remaining elements is 6, which is divisible by 6.

Example 2:

    Input: nums = [6,3,5,2], p = 9
    Output: 2
    Explanation: We cannot remove a single element to get a sum divisible 
    by 9. The best way is to remove the subarray [5,2], leaving us with 
    [6,3] with sum 9.

Example 3:

    Input: nums = [1,2,3], p = 3
    Output: 0
    Explanation: Here the sum is 6. which is already divisible by 3. Thus 
    we do not need to remove anything.
*/

/*
Make Sum Divisible by P

prefix[i] = nums[0] .. nums[i]

we want 
    (total - sum[l,r]) % p == 0


    total % p == subarray % p

    subarray = prefix[r] - prefix[l-1]

            ↓

    prefix[l-1] % p
        =
    (prefix[r] - total) % p


nums = [3, 1, 4, 2]
p = 6
total = 10

    we want to remove a subarray whose mod is 4

    at each step we want the prefix sum
        we store the mod and the index
             mpp[prefix & p] = i

    then we can search for (prefix[r] - total) % p

    since we want the smallest len

    (((prefix - total)%p) + p) % p
*/

/*
[2,7,1] , total = 10, p=8
10%8 == 2
we want to remove shortest subarray with remainder of 2
which is [2]
then the problems becomes 10-2 = 8

total remainder = 2
find shortest subarray whose remainder is 2


prefix[r] - prefix[l-1]

we want 
    prefix[r] - prefix[l-1] ≡ 2

    prefix[l-1] ≡ prefix[r] - 2

    len for prefix array if storing idx
    is r - found because map has [l-1]

    so for r = 0
    l-1 = -1 
    so a subarray found at r=0
    has 0 - (-1) = 1 len
    so mpp[0] = -1
*/

int minSubarray(vector<int>& nums, int p) {

    int total = 0;
    for (int num : nums)
        total += num;

    if (total % p == 0)
        return 0;

    unordered_map<int, int> last; // prefix % p -> latest idx
    last[0] = -1;

    int prefix = 0;
    int minLen = nums.size();

    for (int i = 0; i < nums.size(); i++) {
        prefix += nums[i];

        // Need previous prefix remainder:
        // prefix - previousPrefix ≡ total (mod p)
        int search = (((prefix - total) % p) + p) % p;

        if (last.count(search)) {
            minLen = min(minLen, i - last[search]);
        }

        last[prefix % p] = i;
    }

    return minLen == nums.size() ? -1 : minLen;
}

/*
Make Sum Divisible by P
    we want to remove a subarray from the total that would make the remaining elements divisible by p
    and we want that subarray to be as short as possible

    we want 
        (total - subarray) % p == 0

        total % p == subarray % p

    let target = total % p

    then we want 
        subarray % p == target

    sum[l,r] % p == target

    (prefix[r] - prefix[l-1]) % p == target

    prefix[r] % p == target + (prefix[l-1] % p)

    prefix[l-1] % p == (prefix[r] % p) - target

    oldRem = currRem - target
    we normalize this to
        oldRem = (currRem - target + p) % p;

    so for a running prefix
        we store currRem = (prefix[l-1] % p) and (idx) in a hashmap

        then when we find the rem, calc len
        since we want min len
        if we find the same rem, update the hashmap

        we are looking for subarray len
        so mpp[0] = -1, allows any candidate starting from idx[0]
*/


int minSubarray2(vector<int>& nums, int p) {
    long long total = 0;
    for (int num : nums)
        total += num;

    int target = total % p;

    if (target == 0)
        return 0;

    unordered_map<int, int> last;
    last[0] = -1;

    long long prefix = 0;
    int ans = nums.size();

    for (int i = 0; i < nums.size(); i++) {
        prefix += nums[i];

        int current = prefix % p;
        int need = (current - target + p) % p;

        if (last.count(need))
            ans = min(ans, i - last[need]);

        last[current] = i;
    }

    return ans == nums.size() ? -1 : ans;
}

int main() {
    return 0;
}