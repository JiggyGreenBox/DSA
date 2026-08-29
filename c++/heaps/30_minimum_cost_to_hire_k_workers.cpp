/*
Minimum Cost to Hire K Workers
    [https://leetcode.com/problems/minimum-cost-to-hire-k-workers/]

There are n workers. You are given two integer arrays quality and 
wage where quality[i] is the quality of the ith worker and wage[i] is 
the minimum wage expectation for the ith worker.

We want to hire exactly k workers to form a paid group. To hire a 
group of k workers, we must pay them according to the following rules:

Every worker in the paid group must be paid at least their minimum 
wage expectation.
In the group, each worker's pay must be directly proportional to 
their quality. This means if a worker’s quality is double that of 
another worker in the group, then they must be paid twice as much as 
the other worker.
Given the integer k, return the least amount of money needed to form 
a paid group satisfying the above conditions. Answers within 10-5 of 
the actual answer will be accepted.

 

Example 1:

    Input: quality = [10,20,5], wage = [70,50,30], k = 2
    Output: 105.00000
    Explanation: We pay 70 to 0th worker and 35 to 2nd worker.

Example 2:

    Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], k = 3
    Output: 30.66667
    Explanation: We pay 4 to 0th worker, 13.33333 to 2nd and 3rd workers 
    separately.


*/




/*

Worker A:
quality = 10
minimum wage = 70

Worker B:
quality = 5
minimum wage = 30

every worker gets paid either the minimum wage or proportion of quality

if A has quality = 10
    then wage can be 10r

if B has quality = 5
    wage can be 5r

A needs 70 or more
    10r >= 70

B needs 30 or more
    5r >= 30

r >= 7
OR
r >= 6

so we take r = 7
10r + 5r = 105


quality × r >= wage
    r >= wage / quality


Now imagine hiring a group

    Worker     Quality    Wage

    A            10         70      70/10 = 7
    B             5         30      30/5  = 6
    C             2         20      20/2  = 10


wage / quality sets the entire group multiplier


once we have the smallest multplier
the next thing to minimize is the qualities
    we want the k smallest
    max heap of size k
*/

/*
Minimum Cost to Hire K Workers

Rule:
    pay must be proportional to quality.

Therefore there is one common multiplier r:

    pay[i] = quality[i] × r


Every worker must receive minimum wage:

    quality[i] × r >= wage[i]

Solve for r:

    r >= wage[i] / quality[i]

So every worker has a minimum
required pay-per-quality rate:

    ratio = wage / quality


For a group:

    required rate =
        maximum ratio in the group


------------------------------------------------

Sort workers by ratio ascending.

At current worker:

    current ratio = required group rate

    all previously seen workers
    can be hired at this rate.


Since rate is now fixed:

    total cost =
        rate × total quality


To minimize cost:

    choose K smallest qualities.


Use max heap of quality:

    root = largest quality
         = worst member of current K


If size > K:

    remove largest quality.


For every worker with >= K workers:

    cost = current ratio × sumQuality

    answer = minimum cost seen.
*/

#include <vector>
#include <queue>
#include <cfloat>
#include <algorithm>
using namespace std;

double mincostToHireWorkers(vector<int>& quality,
                            vector<int>& wage,
                            int k) {

    int n = quality.size();

    // {wage / quality, quality}
    vector<pair<double, int>> workers;

    for (int i = 0; i < n; i++) {
        double ratio = (double)wage[i] / quality[i];
        workers.push_back({ratio, quality[i]});
    }

    // Process increasing required pay-per-quality rate
    sort(workers.begin(), workers.end());

    // Keep K smallest qualities
    priority_queue<int> pq; // max heap

    int totalQuality = 0;
    double ans = DBL_MAX;
    // #include <limits>
    // double ans = numeric_limits<double>::max();

    for (auto &[ratio, q] : workers) {

        pq.push(q);
        totalQuality += q;

        // Keep exactly K smallest qualities
        if (pq.size() > k) {
            totalQuality -= pq.top();
            pq.pop();
        }

        // Current ratio is the group's required rate
        if (pq.size() == k) {
            ans = min(ans, ratio * totalQuality);
        }
    }

    return ans;
}