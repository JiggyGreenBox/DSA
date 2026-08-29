/*
Aug 26th
    last 22nd

added greedy and heap
    although we still have 7 problems left to be added

------------------------------

Problem 1 — Greedy/Heap

    You are given a list of tasks represented by uppercase letters.

    Each task takes exactly one unit of time to execute.

    There is a non-negative integer n representing a cooldown interval. 
    Between two executions of the same task, there must be at least n 
    units of time.

    Return the minimum number of time units required to complete all 
    tasks.

    You may execute tasks in any order. Idle intervals are allowed.

    Example
        tasks = [A,A,A,B,B,B]
        n = 2

        Output = 8
      
------------------------------
Brute force:
    this is the task scheduler problem
        we can solve this be using a heap
        or by a counting formula

Observation:
    we need the frequency of all elements
    
    lets say AAA and n=2
    then we have A--A--A
    the gaps are maxFreq - 1
    each block is char + n
    n+1 * maxFreq-1 + 1

    but we might have more than 1 char having maxFreq
    so the answer becomes 
    (n+1)*(maxFreq-1) + countMaxFreq

    we can also use a heap and a cooldown queue
    this is more suitable for actually constructing the string of tasks

Invariant:
Algorithm:
*/
#include <vector>
#include <algorithm>
#include <string>
using namespace std;


    int taskTime(string taskList, int n) {

        vector<int> freq(26,0);

        for(auto task : taskList) {
            freq[task - 'A']++;
        }

        int maxFreq = *max_element(freq.begin(), freq.end());

        int countMaxFreq = 0;
        for(int f : freq) {
            if(f == maxFreq)
                countMaxFreq++;
        }

        int time = ((n+1)*(maxFreq-1))+countMaxFreq;
        return max(time, (int)taskList.size());
    }

/*
Complexity:
    O(n) time
    O(n) 1 
*/


/*
Problem 2 — New Mixed Pool

    You are given an integer array nums and an integer k.

    Return the k most frequent elements in nums.

    The answer may be returned in any order.


Example 1
    nums = [1,1,1,2,2,3]
    k = 2

    Output = [1,2]

Example 2
    nums = [4,4,4,1,1,2,2,2,2,3]
    k = 2

    Output = [2,4]



Brute force:
    we can store freq of each num in a map
    then we iterate backwards k times and store the answer

    we can also use a minHeap of size k
Observation:
Invariant:
Algorithm:
*/
#include <unordered_map>
#include <vector>
#include <queue>
vector<int> kFreq(vector<int> &nums, int k) {

    unordered_map<int, int> freq;

    for(int x : nums)
        freq[x]++;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    for(auto [num, f] : freq ) {

        pq.push({f, num});

        if(pq.size() > k)
            pq.pop();
    }

    vector<int> ans;
    while(!pq.empty()) {
        auto [f,num] = pq.top();
        pq.pop();
        ans.push_back(num);
    }
    return ans;
}


//Complexity:
// nlogk time
// O(n+k) space


/*
Find the length of the longest consecutive sequence of integers.


Example 1
    nums = [100, 4, 200, 1, 3, 2]

    Output = 4
    1, 2, 3, 4

Example 2
    nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]

    Output = 9
    0,1,2,3,4,5,6,7,8

Example 3
    nums = []

    Output = 0

Brute force:
    nested for loop to check if the next element exists
    n^2

    sort and then use 2 pointer to check maxLen
    nlogn

Observation:
    we can use a hashmap to make the look up efficient
Invariant:
Algorithm:
    int longestSequence(vector<int> &nums) {
        unordered_map<int,int> mpp;

        for(int x : nums)
            mpp[x]++;

        int maxCount = 0;

        for(int x : nums) {
            // only consider sequence starts
            if(mpp.count(x-1) > 0)
                continue;

            int count = 0;
            int check = x;
            while(mpp.count(check) > 0) {
                mpp[check]--;
                check++;
                count++;
                maxCount = max(maxCount, count);
            }
        }

        return maxCount;
    }

Complexity:
    O(n) time
    O(n) space

orange for implementation
*/
#include <unordered_set>
int longestSequence(vector<int>& nums) {
    unordered_set<int> st(nums.begin(), nums.end());

    int maxCount = 0;

    for(int x : st) {

        // x is the beginning of a sequence
        if(st.count(x - 1))
            continue;

        int count = 0;
        int check = x;

        while(st.count(check)) {
            check++;
            count++;
        }

        maxCount = max(maxCount, count);
    }

    return maxCount;
}

