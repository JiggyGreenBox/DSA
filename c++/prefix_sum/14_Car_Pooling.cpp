/*

Car Pooling
    [https://leetcode.com/problems/car-pooling/description/]

There is a car with capacity empty seats. The vehicle only drives 
east (i.e., it cannot turn around and drive west).

You are given the integer capacity and an array trips where trips[i] 
= [numPassengersi, fromi, toi] indicates that the ith trip has 
numPassengersi passengers and the locations to pick them up and drop 
them off are fromi and toi respectively. The locations are given as 
the number of kilometers due east from the car's initial location.

Passengers are dropped off before new passengers are picked up at the 
same location. At every point along the route, the total number of 
passengers in the car must not exceed capacity.

Return true if it is possible to pick up and drop off all passengers 
for all the given trips, or false otherwise.

 

Example 1:

    Input: trips = [[2,1,5],[3,3,7]], capacity = 4
    Output: false
    Explanation:
    At kilometer 1, 2 passengers are picked up, so the car holds 2.
    At kilometer 3, 3 more are picked up, so the car holds 5.
    Since 5 > capacity = 4, the trips cannot all be completed.

Example 2:

    Input: trips = [[2,1,5],[3,3,7]], capacity = 5
    Output: true
    Explanation:
    At kilometer 1, the car holds 2 passengers.
    At kilometer 3, the car holds 5 passengers.
    At kilometer 5, the first 2 are dropped off, so the car holds 3.
    At kilometer 7, the last 3 are dropped off, so the car holds 0.
    The maximum occupancy is 5, which never exceeds capacity = 5.


*/

#include <vector>
using namespace std;
bool carPooling(vector<vector<int>>& trips, int capacity) {

    vector<int> diff(1001, 0);

    for(auto &t : trips) {
        int numPassengers = t[0];
        int from = t[1];
        int to = t[2];

        diff[from] += numPassengers;
        diff[to]     -= numPassengers;
    }

    int curr = 0;
    for(int i=0; i <= 1000; i++) {
        curr += diff[i];
        if(curr > capacity)
            return false;
    }
    return true;
}

int main() {

    vector<vector<int>> trips = {{2,1,5},{3,3,7}};
    int capacity = 4;
    trips = {{2,1,5},{3,3,7}}; capacity = 5;
    bool res = carPooling(trips, capacity);
    int x = 5;
    return 0;
}