/*
============================================
nov 14
    last oct 21
============================================
Problem 1
============================================
You are given an integer array heights representing the heights of 
buildings, and an integer bricks and ladders.

You start at building 0 and want to move as far right as possible.

To move from building i to building i + 1:
- If the next building is shorter or equal in height, you can move 
without using resources.
- If it is taller, you must use either bricks equal to the height 
difference or one ladder.
Return the index of the furthest building you can reach.

heights = [4,2,7,6,9,14,12]
bricks = 5
ladders = 1

Output: 4

heights = [4,12,2,7,3,18,20,3,19]
bricks = 10
ladders = 2

Output: 7


brute force
    we can use a recursive approach
        at each idx starting at 1
        if greater than prev
            use bricks = ...
            use ladders = ...
            return max(bricks, ladders)

    2^n time
    n stack space

observation
    1 ladder can replace many bricks
    if we use ladders for the largest jumps
    we save bricks for later

invariant
    use a min-heap of size ladders
    then use bricks for the remaining
        if we run out of bricks 
        we return the last idx we reached

code
    // nlogk for k ladders, time
    // k space
    int furthest(vector<int> &heights, int bricks, int ladders) {
        int n = heights.size();
        priority_queue<int, vector<int>, greater<int>> pq;
        
        for(int i=1; i<n; i++) {

            int diff = heights[i] - heights[i-1];

            if(diff > 0) {
                pq.push(diff);
                if(pq.size() > ladders) {
                    // ladders--; // ERROR
                    bricks -= pq.top();
                    pq.pop();
                }

                if(bricks < 0)
                    return i-1;
            }
        }
        return n-1;
    }


============================================
Problem 2
============================================

Return the length of the shortest non-empty subarray whose sum is at least k.

we need a subarray with sum at least k

i see there are negative numbers present
so a sliding window approach is not possible due to monotic sum property not available

we want sum(i,j) <= k

we are not looking for a precise sum but rather a range
[2,-1,2]
    len of atLeast(k)
        2

we need prefix[j+1] - prefix[i] <= k
    new - old <= k
    new <= k + old

we store prefix sum in a deque
    when the sum is greater than k
    we remove from the front
    track max valid len

============================================
Problem 3
============================================

*/
#include <vector>
#include <queue>
#include <assert.h>
using namespace std;


int main() {

    // vector<int> heights = {4,2,7,6,9,14,12};
    // int bricks = 5;
    // int ladders = 1;
    // assert(furthest(heights, bricks, ladders) == 4);

    // heights = {4,12,2,7,3,18,20,3,19};
    // bricks = 10;
    // ladders = 2;
    // assert(furthest(heights, bricks, ladders) == 7);


    return 0;
}