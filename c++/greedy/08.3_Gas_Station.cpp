#include <iostream>
#include <vector>
using namespace std;

/*
Gas Station
    [https://leetcode.com/problems/gas-station/description/]

There are n gas stations along a circular route, where the amount of 
gas at the ith station is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas 
to travel from the ith station to its next (i + 1)th station. You 
begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas 
station's index if you can travel around the circuit once in the 
clockwise direction, otherwise return -1. If there exists a solution, 
it is guaranteed to be unique.

Example 1:

    Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
    Output: 3
    Explanation:
    Start at station 3 (index 3) and fill up with 4 unit of gas. Your 
    tank = 0 + 4 = 4
    Travel to station 4. Your tank = 4 - 1 + 5 = 8
    Travel to station 0. Your tank = 8 - 2 + 1 = 7
    Travel to station 1. Your tank = 7 - 3 + 2 = 6
    Travel to station 2. Your tank = 6 - 4 + 3 = 5
    Travel to station 3. The cost is 5. Your gas is just enough to travel 
    back to station 3.
    Therefore, return 3 as the starting index.


Example 2:

    Input: gas = [2,3,4], cost = [3,4,3]
    Output: -1
    Explanation:
    You can't start at station 0 or 1, as there is not enough gas to 
    travel to the next station.
    Let's start at station 2 and fill up with 4 unit of gas. Your tank = 
    0 + 4 = 4
    Travel to station 0. Your tank = 4 - 3 + 2 = 3
    Travel to station 1. Your tank = 3 - 3 + 3 = 3
    You cannot travel back to station 2, as it requires 4 unit of gas but 
    you only have 3.
    Therefore, you can't travel around the circuit once no matter where 
    you start.
*/

/*
Gas Station
observations:
    gas =  [1,2,3,4,5]
    cost = [3,4,5,1,2]

    travel = gas - cost
    so travel only possible when gas > cost

    first travel is possible at idx 3,
         4-1 = 3
    
    then at idx 4
        3 + 5 - 2 = 6
    
    at idx 0
        6+1-3 = 4

    at idx 1
        4+2-4 = 2
    at idx 2
        2+3-5=0
    we reach back to 3



    ---
    gas  = [2,3,4], 
    cost = [3,4,3]

    starting only possible at idx2
        4-3 = 1
    idx 0
        1+2-3
    idx 1
        3-4

        wecant reach idx2

    ---
  
    
    n^2
    try every starting index
    if tank < 0 
        false

    the greedy solution has this approach vs brute
        idx 1 2 3 4 5 6
            T F F F

        if we start at 1
        n^2 will start at 2
        but we should start at 5

        point   A  B  C  D
        tank    5  4  3  -1

        if we start at A and fail at D
        we will fail at B,C as well
        why?
            at D we have sum of A,B,C
        its only possible if we have more fuel at point A
        now we are removing A, so its definitely not possible
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

        int start = 0;

        int tank = 0;
        int total = 0;

        for (int i = 0; i < gas.size(); i++) {

            int diff = gas[i] - cost[i];

            tank += diff;
            total += diff;

            if (tank < 0) {
                start = i + 1;
                tank = 0;
            }
        }

        return (total >= 0) ? start : -1;
    }
};

/*
so the greedy solution doesnt require modulo wrapping because we dont reset the total over o(n)

brute force is trying to complete a circle

greedy is trying to find a starting candidate
    also keeps total while checking
        if total < 0
            not possible

another thing for greedy
    is that a solution is only possible when the total > 0
    so we check 2 things with this solution
*/

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

    int n = gas.size();

    for (int start = 0; start < n; start++) {

        int tank = 0;
        bool possible = true;

        for (int k = 0; k < n; k++) {

            int station = (start + k) % n;

            tank += gas[station];
            tank -= cost[station];

            if (tank < 0) {
                possible = false;
                break;
            }
        }

        if (possible)
            return start;
    }

    return -1;
}