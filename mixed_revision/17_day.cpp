#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
/*
============================================
sep 18
    last sep 17
============================================

Problem 1 — Greedy

Jump Game II

Given an integer array nums, where nums[i] represents the maximum 
jump length from index i, return the minimum number of jumps required 
to reach the last index.

You may assume that you can always reach the last index.

Examples:
    nums = [2,3,1,1,4]

    answer = 2

    0 → 1 → 4


Brute Force:
    at each step take 
        idx -> idx+nums[idx], steps
        recursively
        track minJumps

Observation:
    at each step we have a range of steps possible
    for eg. if at idx[0] = 4
        we can take 1,2,3,4 steps to reach idx:1,2,3,4
    so we can say the range is [1,4]

    lets keep this range and take another steps
        check range of 1,4
            and see the max
                the range might now be [5,11]
    if 11 is the end or beyond
        we needed 2 steps

    so its a BFS simulation to get the maxRange >= lastIds

Invariant
    simulate bfs and track [min,max] for each step
    when max >= lastIds, return num of jumps

Algorithm:
int jump2(vector<int> &nums) {

    int left = 0;
    int right = 0;
    int n = nums.size();

    int jumps = 0;

    while(right < n-1) {

        int furthest = right;

        for(int i=left; i<=right; i++) { // range is closed
            furthest = max(furthest, i + nums[i]);
        }

        // explore next window
        left = right + 1;
        right = furthest;
        jumps++;
    }

    return jumps;
}

Complexity:
    O(n) time
    O(1) space

-----
review
    didnt code well and got stuck
====================================

Problem 2 — Heap

Top K Frequent Elements

Given an integer array nums and an integer k, return the k most 
frequent elements.

    nums = [1,1,1,2,2,3], k = 2
    answer = [1,2]

    nums = [4,4,4,4,5,5,5,2,2,8], k = 2
    answer = [4,5]


You can return the elements in any order.
Try to derive:

brute force
    use a unorderedmap to store the frequencies
    make val,key pair vector
        sort this vector
        return top k

why a heap helps
    for the brute force approach processing of elements
    means sorting ALL elements and then choosing from them
    nlogn to sort

    with a heap we can reduce this to nlogk
    which is great for large n and small k
min-heap vs max-heap
    to get the top k elements by freq
    we can either use a maxHeap
        and return the top k elements
            that will mean all elements are in the heap
                nlogn
    or we use a minHeap of size k
        and push and pop
            this will give us nlogk
                minHeap keeps k largest inside  
                    and pops the remaining

what you keep in the heap
invariant
    use a freq map to count freq
    use a min heap of size k to efficiently store the k most frequent elements


algo
    vector<int> topKfreq(vector<int> &nums, int k) {
        unordered_map<int, int> freq;

        for(int num : nums)
            freq[num]++;

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // min_heap

        for(auto &[num, count] : freq) {
            pq.push({count, num});

            if(pq.size() > k)
                pq.pop();
        }

        vector<int> ans;

        while(!pq.empty()) {
            ans.push_back(pq.top().second);
            pq.pop();
        }

        // optional reverse
        // most freq ordered
        reverse(ans.begin(), ans.end());
        return ans;
    }
complexity
    O(nlogk) to insert into heap
    O(k) space for the heap

=====================================

Problem 3 — Prefix Sum + Hashing

Longest Consecutive Subarray with Equal 0s and 1s

You've seen the standard Contiguous Array problem already, so let's 
make this one a slight modification rather than repeat it verbatim:

Given a binary array, return the maximum length of a contiguous 
subarray containing equal numbers of 0s and 1s, but the subarray must 
contain at least one 0 and one 1.

Derivation:
we want
    sum of 1s == 0s
    for any subarray
        then we want the max-len subarray

    we cant just use a regular sum, we cant account for 0s
    so we have 0 as -1
    and 1 as +1
    now the sum approach can work

    if the sum of any subarray after this transformation is 0, we have equal number of 1s and zeros

    prefix[r] - prefix[l-1] == 0
    we want prefix[r] == prefix[l-1]

    lets store this prefix in a hashmap for O(1) lookup
    we want longest, so when a dupilcate sum is found later dont update it
    our hashmap will store sum, idx

    when we find a match
        len == curr - oldidx

algo
    int longest(vector<int> &nums) {
        unordered_map<int, int> mpp; // sum, idx

        mpp[0] = -1;

        int prefix = 0;
        int max_len = 0;

        for(int i=0; i<nums.size(); i++) {
            if(nums[i] > 0)
                prefix += 1;
            else
                prefix -= 1;
            

            if(mpp.count(prefix) > 0) {            
                max_len = max(max_len, i - mpp[prefix]);
            }
            else {
                mpp[prefix] = i;
            }
        }
        return max_len;
    }


complexity
    O(n) time
    O(n) space

===================================

session 2

=================================== 

Problem 4 — Prefix Sum + Hashing

Subarray Sums Divisible by K

Given an integer array nums and an integer k, return the number of 
contiguous subarrays whose sum is divisible by k.


nums = [4,5,0,-2,-3,1]
k = 5

answer = 7


Derivation
    we have negative numbers here
        so sliding window approaches are not possible

    we want a subarray sum % k == 0
    we want the count of these subarrays

    17 + 13 == 30%5 ==0
    17%5 == 2
    13%5 == 3
        2+3 % 5 == 0

    we want 
        (prefix[r] - prefix[l-1]) % k == 0

        prefix[r] % k == prefix[l-1] % k

    and we want how many sub arrays so well keep a count
        of prefix%k, count


code:
    int countK(vector<int> &nums, int k) {

        unordered_map<int, int> mpp; // prefix % k, count
        mpp[0] = 1;

        int prefix = 0;

        int total = 0;

        for(int i=0; i<nums.size(); i++) {
            prefix += nums[i];

            int search = ((prefix % k) + k) % k; // negative guard

            if(mpp.count(search) > 0) {
                total += mpp[search];
            }

            mpp[search]++;
        }

        return total;
    }
    
Complexity
    O(n) time
    O(n) space
=====================================

Problem 5 — Sliding Window

Longest Repeating Character Replacement

Given a string s consisting of uppercase English letters and an 
integer k, you may replace at most k characters.

Return the length of the longest substring that can be made to 
contain only one distinct character.


s = "AABABBA", k = 1

answer = 4


Derivation:
    we want a substring which has all the same char
    AAAAA
    if we are allowed k different chars
        then AAAxxAAA is valid for k==2

    so for a valid window
        window_len - k <= maxFreq

    when greater
        we shrink the window len

Invariant
    using frequencies of chars
        we expand the window such that windowlen - l <= maxFreq
    when invalid shrink again

    keep a track of max_len

Complexity:

code:
int kreplacements(string &s, int k) {

    vector<int> freq(26, 0);    

    int left = 0;
    int max_freq = 0;
    int max_len = 0;
    int right = 0;
    for(right=0; right<s.size(); right++) {

        char c = s[right];
        freq[c]++;

        
        max_freq = max(max_freq, freq[c]); // we dont care about reducing from the max found

        if((right-left+1) - k > max_freq) {
            freq[s[left]]--;
            left++;            
            // we dont care about shrinking to the least possible value
            // carry the window till the end, thats ok
        }        
    }
    return right - left;
}
=======================================

Problem 6 — Greedy + Heap

Last one for today's block. This is deliberately a little more 
unfamiliar.

Minimum Number of Refueling Stops

You start with startFuel units of fuel. Your car uses 1 unit of fuel 
per mile.

You are given:
    target
    startFuel
    stations[i] = [position, fuel]


target = 100
startFuel = 10

stations:
[10, 60]
[20, 30]
[30, 30]
[60, 40]


we have 10 fuel
    we can reach position 10
        here we get 60 fuel more
    
    now with 60 fuel
        my choices are:
            [20, 30]
            [30, 30]
            [60, 40]

        i try take the stop at position 60
            which gives me 40 fuel
        now my target of 40 + 60 == 100 is achieved
            in 2 steps

i will first sort the pairs by positions
    this allows me to look at feasible choices
    then next i will add the max fuel
        this will again in turn give me more available positions

    which will again allow me to take the max fuel

the greedy choice is maximize fuel per availbe stations
    use a maxHeap

time complexity
    o(nlogn) time
    o(n) space

*/

int minRefuelingStops(vector<pair<int,int>> stations, int target, int start_fuel) {

    sort(stations.begin(), stations.end()); // order by position ascending

    int curr_fuel = start_fuel;

    priority_queue<int> pq;

    int n = stations.size();

    // push all feasible station options into heap
    int i =0;
    int stops = 0;

    while(i<n) {
        while(i<n && stations[i].first <= curr_fuel) {            
            int fuel = stations[i].second;
            pq.push(fuel);
            i++;
        }

        if(pq.empty())
            break;
            
        
        // take the best        
        curr_fuel += pq.top();
        pq.pop();
        stops++;

        if(curr_fuel >= target)
            return stops;
    }
    return -1;
}




int main() { 
    vector<pair<int,int>> stations = {
    {10,60},
    {20,30},
    {30,30},
    {60,40}};

    cout << minRefuelingStops(stations, 100, 10) << endl;
    return 0;
}