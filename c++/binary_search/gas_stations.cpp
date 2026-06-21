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
max gap = D
    when D, are k stations placed?
Monotonic value of D:
    F F F F T T T

larger D has less new stations placed
    D = 5  -> 12 stations
    D = 8  -> 5 stations
    D = 10 -> 3 stations
    D = 15 -> 1 station
we can only place <= k stations 
    D is feasible when
    stations required <= stations available

Goal:
    Find first True.




Minimize Max Distance to Gas Station
    D = maximum allowed distance between adjacent stations

    Can I add at most k stations so that
    every gap is <= D?

    3,12
        gap = 12-3 = 9
        3--6--9--12
        3 segments 9/3 = 3
        3 segments need 2 divisions or stations

    1..15
        gap = 14
        D = 5
        1..6..11..15

        14/5 = 2.8 
        we take ceil because 11..15 is 4
        3 segments formed by 2 points/stations


    [3, 6, 12, 19, 33, 44, 67, 72, 89, 95], k = 2    

    f(D) return stations placed
        int stations
        for(i=1; i<n; i++) 
            d = n[i] - n[i-1]
            if(d > D)
                stations += ceil(d/D) - 1                
        return stations

    l = 0
    r = maxGap

    larger D = less k
    smaller D = more k

    while(r-l > 1e-6)
        int mid = ..

        if(f(mid) <= k) {
            ans = mid
            try smalled mid
        }
        else
            increase mid           

*/

long double minimiseMaxDistance(vector<int> &arr, int k) {

}

int main() {
    return 0;
}