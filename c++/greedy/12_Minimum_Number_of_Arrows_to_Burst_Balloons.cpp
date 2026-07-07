#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Minimum Number of Arrows to Burst Balloons
    [https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/description/]

There are some spherical balloons taped onto a flat wall that 
represents the XY-plane. The balloons are represented as a 2D integer 
array points where points[i] = [xstart, xend] denotes a balloon whose 
horizontal diameter stretches between xstart and xend. You do not 
know the exact y-coordinates of the balloons.

Arrows can be shot up directly vertically (in the positive 
y-direction) from different points along the x-axis. A balloon with 
xstart and xend is burst by an arrow shot at x if xstart <= x <= 
xend. There is no limit to the number of arrows that can be shot. A 
shot arrow keeps traveling up infinitely, bursting any balloons in 
its path.

Given the array points, return the minimum number of arrows that must 
be shot to burst all balloons.


Example 1:

    Input: points = [[10,16],[2,8],[1,6],[7,12]]
    Output: 2
    Explanation: The balloons can be burst by 2 arrows:
    - Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
    - Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

Example 2:

    Input: points = [[1,2],[3,4],[5,6],[7,8]]
    Output: 4
    Explanation: One arrow needs to be shot for each balloon for a total 
    of 4 arrows.

Example 3:

    Input: points = [[1,2],[2,3],[3,4],[4,5]]
    Output: 2
    Explanation: The balloons can be burst by 2 arrows:
    - Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
    - Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].

*/

/*
Minimum Number of Arrows to Burst Balloons
maybe we can try to think of ballons as intervals
sort by end

[1,6]
[2,7]
[3,8]
now an arrow from 6
    will pop all baloons where start<=6
when that is not the case 
    take end of next interval
    fresh arrow
*/


int findMinArrowShots(vector<vector<int>>& points) {
    
    sort(points.begin(), points.end(), 
        [](const auto &a, const auto &b){
            return a[1] < b[1];
        });

    int n = points.size();
    int i = 0;
    int total_arrows = 0;

    while(i<n) {

        int curr_arrow = points[i][1];

        while(i<n && points[i][0] <= curr_arrow) {
            i++;
        }
        total_arrows++;
    }    

    return total_arrows;
}

int main() {
    vector<vector<int>> points = {{10,16},{2,8},{1,6},{7,12}};
    cout << findMinArrowShots(points) << endl; // 2

    points = {{1,2},{3,4},{5,6},{7,8}};
    cout << findMinArrowShots(points) << endl; // 4

    points = {{1,2},{2,3},{3,4},{4,5}};
    cout << findMinArrowShots(points) << endl; // 2
    return 0;
}

/*
Take one arrow

↓

Burst everything possible

↓

Take next arrow

↓

Burst everything possible
*/