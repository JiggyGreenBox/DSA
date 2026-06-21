#include <iostream>
#include <vector>
using namespace std;

/*
Minimize Max Distance to Gas Station
    Given a sorted array arr of size n, containing integer positions of n 
    gas stations on the X-axis, and an integer k, place k new gas 
    stations on the X-axis.

    The new gas stations can be placed anywhere on the non-negative side 
    of the X-axis, including non-integer positions.

    Let dist be the maximum distance between adjacent gas stations after 
    adding the k new gas stations.

    Find the minimum value of dist.

    Your answer will be accepted if it is within 1e-6 of the true value.
*/

/*
Minimize Max Distance to Gas Station

Answer:
    minimum feasible D

    choose a distance such that we create some new segments
    segments are divided by points(stations) which can be up k stations

D = maximum allowed distance
    Can every gap be reduced to <= D
    using at most k new stations?

ex1
    3..12 (gap=9)
    D=3
    12-3 = 9
    9/3 = 3
    3..6..9..12
    3 segments by adding 2 points at 6 and 9

ex2
    1..15 (gap=14)
    D = 5
    1..6..11..15
    3 segments with 2 stations at 6 and 11
        notice 11-15 is 4
    ceil(14/5) = ceil(2.8) = 3

Monotonic for D
    Smaller D
        -> more segments required
        -> more stations required
    Larger D
        -> fewer segments required
        -> fewer stations required

increasing D, stations <= k
    F F F F T T T T

find first T

    f_num_stations(D):
        for(i=1;i<n;i++)
            dist = nums[i] - nums[i-1]
            if(dist > D)
                stations += ceil(d/D) - 1
        return stations

int l = 0
int r = max_diff

while(r-l > 1e-6)
    long double mid = l + (r-l)/2;

    if(f_num_stations(mid) <= k) {
        ans = mid
        r = mid
    }
    else{
        l = mid
    }
return r
*/

int main() {
    return 0;
}