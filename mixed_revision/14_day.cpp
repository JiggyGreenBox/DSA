/*
===========================================
sep 13
    last 10
===========================================
focus heap / greedy
===========================================
Problem 1 — Heap

You are given an integer array nums and an integer k.

Return the k-th largest element in the array.

The array is not necessarily sorted, and you should solve it without 
fully sorting the array.

Brute force
    sort array return n-k

Obervation
    we can use a heap DS to return our element
    
    we can use a min heap of size k

Algorithm
int kthLargest(vector<int> &nums, int k) {

    if(nums.empty())
        return -1;

    priority_queue<int, vector<int>, greater<int>> pq;

    for(int num : nums) {
        pq.push(num);

        if(pq.size() > k)
            pq.pop();
    }
    return pq.top();
}
Complexity:
    O(nlogk) time
    O(k) space

===========================================

Problem 2 — Greedy

You are given a list of intervals where intervals[i] = [startᵢ, 
endᵢ].

Return the minimum number of intervals you need to remove so that the 
remaining intervals are non-overlapping.

Intervals that only touch at an endpoint are considered 
non-overlapping.

Example
    intervals = [[1,2], [2,3], [3,4], [1,3]]

    Output: 1   

brute force

observation
    if the end of an interval is greater than the start of another interval
    they are overlapping and we cant consider it

    we need to sort the intervals by end to do this in a single pass
invariant
    sort by end
        if next_start >= prev_end
            proceed
        else 
            remove interval
algorithm
    int minRemovals(vector<vector<int>> &intervals) {
        int removals = 0;
        
        sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b){
            return a[1] < b[1];
        });

        int prev_end = INT_MIN;

        for(const auto &i : intervals) {
            
            int start = i[0];
            int end = i[1];

            if(start >= prev_end) {
                prev_end = end;
            }
            else {
                removals++;
            }
        }

        return removals;
    }
complexity
    O(nlogn) time
    O(1) space

===========================================

Problem 3 — Heap + Greedy

You are given an integer array nums representing the heights of buildings and an integer bricks and ladders.

You start at building 0 and want to reach the last building.

To move from building i to i + 1:

If nums{i+1} <= nums{i}, you can move without using anything.
Otherwise, you must use either:
nums{i+1} - nums{i} bricks, or
one ladder.

Return the furthest building index you can reach.


    nums = {4, 2, 7, 6, 9, 14, 12}
    bricks = 5
    ladders = 1

    Output: 4


derivation
    we need bricks or ladders to climb
    if no climb continue

    ladders are valueable
        a single ladder is worth many bricks
        so we want to use ladders for the biggest climbs

    if have k ladders
        then we use them for the k largest climbs

    we are moving 1 step by step

    so we use what we can until we dont have any bricks left

    we want k largest climbs
        we use a minHeap of size k

    use bricks for the remaining until we can go any further


algorithm:
    int furthest(vector<int> &nums, int bricks, int ladders) {

        int n = nums.size();

        priority_queue<int, vector<int>, greater<int>> pq;

        for(int i=1; i<n; i++) {

            int diff = nums[i] - nums[i-1];

            if(diff <= 0)
                continue;

            pq.push(diff);

            if(pq.size() > ladders) {
                bricks -= pq.top();
                pq.pop();
            }

            if(bricks < 0)
                return i-1;
        }
        return n-1;
    }
complexity:
    O(nlogk) time
    O(k) space
    where k is ladders
*/
