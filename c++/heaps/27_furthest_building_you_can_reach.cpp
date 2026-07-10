/*
furthest_building_you_can_reach
[https://leetcode.com/problems/furthest-building-you-can-reach/description/]

You are given an integer array heights representing the heights of 
buildings, some bricks, and some ladders.

You start your journey from building 0 and move to the next building 
by possibly using bricks or ladders.

While moving from building i to building i+1 (0-indexed),

If the current building's height is greater than or equal to the next 
building's height, you do not need a ladder or bricks.
If the current building's height is less than the next building's 
height, you can either use one ladder or (h[i+1] - h[i]) bricks.
Return the furthest building index (0-indexed) you can reach if you 
use the given ladders and bricks optimally.



*/

/*
furthest_building_you_can_reach
if curr_height >= next_height
    no ladder or brick required
    +1 move ahead

if curr_height < next_height
    use 1 ladder

    or use diff bricks

    move +1 ahead
    
    stop if no ladder or bricks

can we use pick and skip for each choice
    then return max_dist
    pick and skip, is basically either ladder or bricks at curr < next


it seems ladders are more valuable, since 1 ladder == many bricks
    how do we know when to use which



the greedy invariant is if we have k ladders
    then top k get ladders
    rest get bricks

    k largest,
        put all in max-heap
        pop k into result

    min heap of size k
        push
            pop

    when we pop we can subtract that from bricks?
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
    priority_queue<int, vector<int>, greater<int>> pq; // min-heap
    
    for(int i=1; i< heights.size(); i++) {

        int diff = heights[i] - heights[i-1];

        if(diff < 0)
            continue;

        pq.push(diff);

        if(pq.size() > ladders) {
            int top = pq.top();
            pq.pop();
            bricks -= top;
        }

        if(bricks < 0)
            return i - 1; // -1 because this jump wasnt possible
    }
    return heights.size() - 1;
}

int main() {
    vector<int> heights = {4,2,7,6,9,14,12};
    int bricks = 5;
    int  ladders = 1;

    cout << furthestBuilding(heights, bricks, ladders) << endl;

    heights = {4,12,2,7,3,18,20,3,19}; bricks = 10; ladders = 2;

    cout << furthestBuilding(heights, bricks, ladders) << endl;

    heights = {14,3,19,3}; bricks = 17; ladders = 0;

    cout << furthestBuilding(heights, bricks, ladders) << endl;
    return 0;
}