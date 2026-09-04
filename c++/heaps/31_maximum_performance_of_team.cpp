/*
Maximum Performance of a Team
    [https://leetcode.com/problems/maximum-performance-of-a-team/description/]

You are given two integers n and k and two integer arrays speed and 
efficiency both of length n. There are n engineers numbered from 1 to 
n. speed[i] and efficiency[i] represent the speed and efficiency of 
the ith engineer respectively.

Choose at most k different engineers out of the n engineers to form a 
team with the maximum performance.

The performance of a team is the sum of its engineers' speeds 
multiplied by the minimum efficiency among its engineers.

Return the maximum performance of this team. Since the answer can be 
a huge number, return it modulo 109 + 7.

 

Example 1:

    Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 
    2
    Output: 60
    Explanation: 
    We have the maximum performance of the team by selecting engineer 2 
    (with speed=10 and efficiency=4) and engineer 5 (with speed=5 and 
    efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.

Example 2:

    Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 
    3
    Output: 68
    Explanation:
    This is the same example as the first but k = 3. We can select 
    engineer 1, engineer 2 and engineer 5 to get the maximum performance 
    of the team. That is, performance = (2 + 10 + 5) * min(5, 4, 7) = 68.

Example 3:

    Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 
    4
    Output: 72
*/

// come back to this later



/*
Maximum Performance of a Team
    we want max performance

    we are given speed and efficiency for each worker
    we can choose k employees

    performance = sum of speed for k employees * min efficiency of these k employees


brute force
    for each idx
        choose k-1 other idx
        calculate min efficiency
        multiply by sum of speed
        track max performance

observation
    sort by descending efficiency
    then each idx is the min efficiency
        take k top speeds using a minHeap

        track max performance
*/
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int maxPerformance(int n, vector<int>& speed,
                   vector<int>& efficiency, int k) {

    vector<pair<int,int>> eng;

    for (int i = 0; i < n; i++)
        eng.push_back({efficiency[i], speed[i]});

    sort(eng.begin(), eng.end(),
         [](const auto& a, const auto& b) {
             return a.first > b.first;
         });

    priority_queue<int, vector<int>, greater<int>> pq;

    long long speedSum = 0;
    long long ans = 0;

    for (auto &[eff, spd] : eng) {

        speedSum += spd;
        pq.push(spd);

        if (pq.size() > k) {
            speedSum -= pq.top();
            pq.pop();
        }

        ans = max(ans, speedSum * eff);
    }

    return ans % 1000000007;
}


/*
Maximum Performance of Team

performance =
    sum(speed) * min(efficiency)

Hard part:
    min efficiency changes depending on team.

Sort efficiency descending.

Now at engineer i:
    current efficiency is the minimum efficiency
    for any team chosen from the prefix that includes this threshold.

So maximize:
    sum of speeds among at most K engineers seen so far.

Want K largest speeds:
    min heap of size K.

Maintain speedSum.

For each engineer:
    add speed
    if heap size > K:
        remove smallest speed
    performance = speedSum * currentEfficiency
    update answer
*/