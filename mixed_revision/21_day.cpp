/*
============================================
sep 25
    last sep 24
============================================

Question 1 — Array / Hashing

Given an integer array nums, return the length of the longest consecutive sequence of integers.

The elements do not need to be adjacent in the original array.

Example:



Brute force
    sort the array (nlogn)
    and then count the max sequence possible
Observation
    if we use a set, and if know the starting of a sequence (num-1 doesnt exist)
    we can count the longest subsequce in O(n) expected time
Invariant
    use a set and pruning to achieve 1 pass
Algorithm
    int longest(vector<int> &nums) {
        int max_len = 0;
        unordered_set<int> mset;

        for(int num : nums) 
            mset.insert(num);

        
        for(int num : nums) {
            // ignore non-starting of sequence nums
            if(mset.count(num-1))   
                continue;

            int count = 1;
            while(mset.count(++num))
                count++;

            max_len = max(max_len, count);
        }

        return max_len;
    }
Complexity
    O(n) time
    O(n) space

============================================

Question 2 — Binary Search

Given a sorted array nums that has been rotated at some unknown 
pivot, return the minimum element.

You may assume all elements are distinct.


nums = [4,5,6,7,0,1,2]

answer = 0

nums = [3,4,5,1,2]

answer = 1



Brute force
    linear scan to find the minimum element
Observation
    we can discard 1 half if we know which half to discard
    since rotation is allowed
        if m < r
            go left, include m
        else
            go right ,m  not in solution
Invariant
    binary search to find which side to discard
Algorithm
    int min_elem(vector<int> &nums) {
        int n = nums.size();
        int l = 0;
        int r = n-1;

        while(l<r) {
            int m = l + (r-l)/2;

            if(nums[m] < nums[r]) {
                r = m; // m is possible answer
            }
            else {
                l = m + 1;
            }
        }
        return nums[l];
    }
Complexity
    O(logn) time
    O(1) space

l   m   r
0 1 2 3 4  m<r, left, include m
4 0 1 2 3  m<r  left, include m
3 4 0 1 2  m<r  left, include m
2 3 4 0 1  m>r  right  no m
1 2 3 4 0  m>r  right  no m

==============================================

Question 3 — Tree / Linked List

Let's test recognition rather than giving you the category.

Given the head of a singly linked list, remove the nth node from the 
end of the list and return the head.

1 → 2 → 3 → 4 → 5
n = 2   
1 → 2 → 3 → 5

1 → 2
n = 2

2

Brute force
    store nodes into vector
        reverse vector
        remove n-1th num
        overwrite
        erase remaining
Observation
    we can use 3 pointers
        prev,slow and fast
    note we are counting in a 1-based system

    we need the len of the LL
    put a fast pointer len-n steps ahead
        at len-n, the next node is node to delete
Invariant
        use pointers to find the node to delete        
Algorithm
    Node* deleteNth(Node* head, int k) {
        if(!head || k < 1) // last node is at k=1
            return head;

        Node dummy(-1);
        dummy.next = head;

        int len = 1;
        Node* curr = head;
        while(curr->next) {
            len++;
            curr = curr->next;
        }

        // k = k % len;

        Node* prev = &dummy;
        curr = head;    
        int count = 0; // removals become 0indexed now
        while(count < len-k) {
            count++;
            prev = prev->next;
            curr = curr->next;
        }

        prev->next = curr->next;
        delete curr;
        
        return dummy.next;
    }
Complexity
    O(n) time
    O(1) space

didnt use the simple solution because this topic is not fresh!


===========================================

session 4

Question 1

You are given an array nums where nums[i] represents the maximum 
number of positions you can jump forward from index i.

Return whether you can reach the last index.

Brute force
    at each step try to take 1..steps
        in a recursive fashion
    if we reach the end or cross it
        return true

    max^n time
    n recursion stack space
    
Observation
    at each step
        note the max u can reach
    
    if at idx
        idx >= n-1
            true
        if idx< maxreach
            false

    this allows for a O(n) approach

Invariant
    store maxreach at each idx
    but take 1 step at a time
        then either prune or return early based on maxreach
Algorithm
    bool canReach(vector<int> &nums) {
        int n = nums.size();
        int farthest = nums[0];
        for(int i=1; i<n; i++) {

            if(i > farthest)
                return false;

            farthest = max(farthest, i + nums[i]);

            if(farthest >= n-1)
                return true;
        }
        return false;
    }
Complexity  
    O(n) time
    O(1) space
====================================

Question 2 — Heap

Given an integer array nums, return the kth largest element in the 
array.

You may assume k is valid.


Brute force
    sort
    then reverse iterate till k-1
        return

    nlogn

Observation
    we can use a maxheap then pop k-1 times
        nlogn time
        n space
    or we can use a minHeap of size k
        O(nlogk) time
        O(k) time

Invariant
    use a minHeap of size k
    return top
Algorithm
    int klargest(vector<int> &nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;

        for(int num : nums) {
            pq.push(num);

            if(pq.size() > k)
                pq.pop();
        }
        return pq.top();
    }
Complexity
    O(nlogk) time
    O(k) time
============================================

Question 3 — Prefix Sum / Sliding Window

Given an integer array nums and an integer k, return the number of 
subarrays whose sum is divisible by k.

Brute force
    enumerate every subarray
        add, if total%k==0
            count++
    
Observation
    we want subarraysum %k == 0
    there are negatives so we need a prefix array

    we want (prefix[r] - prefix[l-1]) %k == 0


    we want prefix[r]%k == prefix[l-1]%k
    need to ensure -ve%k is handled

    then we store the frequency of this and count

Invariant
    use prefix sum with frequency hashmaps to count valid subarrays
Algorithm
Complexity
    O(n) time
    O(n) space
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;


int count_div_k(vector<int> &nums, int k) {
    unordered_map<int, int> freq; //<sum%k, count>
    freq[0] = 1;

    int count = 0;
    int prefix = 0;

    for(int i=0; i<nums.size(); i++) {
        prefix += nums[i];

        int search = ((prefix%k) + k) %k; // neg guard

        if(freq.count(search)) {
            count += freq[search];
        }
        freq[search]++;
    }
    return count;
}

int main() {
    vector<int> nums = {4,5,0,-2,-3,1};
    auto x = count_div_k(nums, 5);
    return 0;
}
