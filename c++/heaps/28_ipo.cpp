/*
IPO
    [https://leetcode.com/problems/ipo/description/]
Suppose LeetCode will start its IPO soon. In order to sell a good 
price of its shares to Venture Capital, LeetCode would like to work 
on some projects to increase its capital before the IPO. Since it has 
limited resources, it can only finish at most k distinct projects 
before the IPO. Help LeetCode design the best way to maximize its 
total capital after finishing at most k distinct projects.

You are given n projects where the ith project has a pure profit 
profits[i] and a minimum capital of capital[i] is needed to start it.

Initially, you have w capital. When you finish a project, you will 
obtain its pure profit and the profit will be added to your total 
capital.

Pick a list of at most k distinct projects from given projects to 
maximize your final capital, and return the final maximized capital.

The answer is guaranteed to fit in a 32-bit signed integer.


Example 1:

    Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
    Output: 4
    Explanation: Since your initial capital is 0, you can only start the 
    project indexed 0.
    After finishing it you will obtain profit 1 and your capital becomes 
    1.
    With capital 1, you can either start the project indexed 1 or the 
    project indexed 2.
    Since you can choose at most 2 projects, you need to finish the 
    project indexed 2 to get the maximum capital.
    Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
Example 2:

    Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
    Output: 6
*/

/*
IPO

Observation

Capital determines whether a project is available.

Profit determines which available project we should choose.

Algorithm

1. Pair (capital, profit).

2. Sort by capital.

3. Maintain a pointer into the sorted array.

4. While capital <= currentCapital
       push profit into max heap.

5. Pop the largest profit.

6. Increase currentCapital.

7. Repeat k times.
*/

/*
projects
    sorted by capital

i
    first project not yet pushed into heap

heap
    profits of all currently affordable projects

Each project

    enters the heap once
    leaves the heap once

No rescanning.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {

    int n = profits.size();

    vector<pair<int,int>> projects;

    for(int i=0; i<n; i++) {
        projects.push_back({capital[i], profits[i]});
    }

    sort(projects.begin(), projects.end());

    priority_queue<int> pq;    

    int i=0;

    // k times
    while(k--) {
        
        // Add every project we can currently afford.
        while(i<n && w >= projects[i].first) {
            pq.push(projects[i].second); // push profit, no capital - profit
            i++;
        }

        if(pq.empty())
            break;

        w += pq.top();
        pq.pop();
    }    

    return w;
}

int main() {
    
    int k = 2; int w = 0;
    vector<int> profits = {1,2,3};
    vector<int> capital = {0,1,1};
    cout << findMaximizedCapital(k, w, profits, capital) << endl; // 4

    k = 3; w = 0;
    profits = {1,2,3};
    capital = {0,1,2};
    cout << findMaximizedCapital(k, w, profits, capital) << endl; // 6

    cout << "nothing" << endl;
    return 0;
}

/*
does this work because we always get more capital
old project are in the heap
so we only consider new projects?
*/