/*
============================================
sep 14
    last sep 13
============================================

Greedy heap focus

============================================

Problem 1 — Greedy

You are given an array nums where nums[i] represents the maximum 
number of positions you can jump forward from index i.

You start at index 0.

Return true if you can reach the last index, otherwise return false.

Examples:
    nums = [2,3,1,1,4]
    Output: true

    nums = [3,2,1,0,4]
    Output: false

Brute force
    recursion style
        try to visit each idx of idx+nums[idx]
            
        return true if last index is reached or crossed
        else false
        
observation
    we can take a greedy approach
        store max_reach for each step
    and take 1 step

invariant
    keep a track of max reach
        if idx > maxreach
            return false

        else true

algorithm
    bool canReach(vector<int> &nums) {
        int furthest = -1;
        int n = nums.size();

        for(int i=0; i<n; i++) {
            furthest = max(furthest, i + nums[i]);

            if(furthest < i)
                return false;

            if(furthest >= n-1)
                return true;
        }
        return true;
    }
complexity
    O(n) time
    O(1) space

=======================================

Problem 2 — Greedy

You're given an array nums representing the ratings of children 
standing in a line.

You must give each child at least one candy.

Additionally:

A child with a higher rating than an immediate neighbor must receive 
more candies than that neighbor.

Return the minimum total number of candies required.

ratings = [1,0,2]
Output: 5
    2, 1, 2

---
Derivation
    we need to know if a child is greater than its neighbour from both sides
    to decide whether to give an extra candy

    from L-R check if R>L then kids[r]++

    then from R-L if L>R then max(kids[l], kids[r]+1)


int candies(const vector<int> &kids) {
    int n = kids.size();
    vector<int> ans(n, 1);    

    for(int i=1; i<n; i++) {
        if(kids[i] > kids[i-1])
            ans[i] = ans[i-1] + 1;
    }

    for(int i=n-2; i>=0; i--) {
        if(kids[i] > kids[i+1])
            ans[i] = max(ans[i], ans[i+1] + 1);
    }
    
    int candy = 0;
    for(int x : ans)
        candy += x;
    return candy;
}

complexity
    O(n) time
    O(n) space

----
there is another derivation based on peak finding

when the peak increases we have a +1 addition
    1 to 4

   4
  3 3
 2   2
1     1

    we also have the same thing from the right
        1 to 4


we can also walk down like this
    the total will be the same
   4
  3 1
 2   2
1     3

but now we have an issue with this arrangement
    the walkdown miscount the 5


   4(5)
  3 4
 2   3
1     2
       1

so this is how we approach this


   4
  3 1
 2   2
1     3
       4(+1 for peak)





complexity

    O(n) time
    O(1) space
==================================================

Problem 3 — Heap

You are given a stream of integers arriving one at a time.

After each number arrives, you must be able to return the median of 
all numbers seen so far.

Implement:
class MedianFinder {
public:
    void addNum(int num);
    double findMedian();
};

addNum and findMedian should each be O(log n) or better.


Derivation
    at each step the brute force is to sort
        and point to the n/2 or take the average of n/2, n/2+1

    but we dont actually care about sorting each element
    we can split the numbers into 2 DS
        left, right
    left has max,
    right has min
        then return left-max, or left-max+right-min/2

    rebalance these when required
        keep left + 1 to right
        then for odd return left-min
        for even take average

    we use 2 heaps to achieve this

class MedianFinder {
private:
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;

    void rebalance() {
        // left can be right + 1

        // left too big
        if(left.size() > 1 + right.size()) {
            right.push(left.top());
            left.pop();
        }

        // right cant be bigger than left
        if(right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }
    }
public:
    void addNum(int num) {
        if(left.empty() || num <= left.top())
            left.push(num);
        else
            right.push(num);

        rebalance();
    }

    double findMedian() {
        if(size() & 1)
            return left.top();

        return (left.top() + right.top()) / 2.0;
    }

    int size() {
        return left.size() + right.size();
    }
};
====================================

Problem 4 — Greedy + Heap

You are given n projects. For each project:

    capital[i] = minimum capital required to start the project
    profit[i]  = profit earned after completing it

You start with w units of capital.

You can complete at most k projects.

After completing a project, its profit is immediately added to your 
capital.

You may only start a project if your current capital is at least its 
required capital.

Return the maximum capital you can have after completing at most k 
projects.


Derivation  
    we can only take k projects
        we can only start projects in our budget

        we want maximum capital

    if we sort by capital
    at each step
        insert all feasible projects
        take the top project by profit
            using a heap

        add this back to capital
        can do this k times

int maxprofit(vector<int> &capital, vector<int> &profit, int k, int money) {
    vector<pair<int,int>> projects;

    int n = capital.size();

    for(int i =0; i<n; i++) 
        projects.push_back({capital[i], profit[i]});

    sort(projects.begin(), projects.end());


    priority_queue<int> pq;

    int i=0;

    while(k--) {
        while (i<n && money >= projects[i].first)
        {
            pq.push(projects[i].second); // profit
            i++;
        }

        if(pq.empty())
            break; // no projects possible
        
        money += pq.top();
        pq.pop();
    }

    return money;
}


O(nlogn + nlogn) to sort for heap
    and klogn removals
O(n) space


============================================

Problem 5 — let's push the difficulty

You are given n courses. For each course:
    courses[i] = [duration, deadline]

You start at time 0.

To take a course, you must spend its full duration. You can take 
courses sequentially, and a course must be completed on or before its 
deadline.

Return the maximum number of courses you can take.

---

courses have a duration and deadline
    if we take 2 courses
        t1 + t2 < deadline2
        to be valid
    
    so we sort by deadlines
        this allows us to pick and not pick easily

    so the entire sum of durations must be less than deadlines to be valid
        we remove the longest duration class

    we want max courses
        so we want to remove the least

    we will process earliest deadlines first
        this will increase the flexibilty of choosing longer deadlines later


complexity
    O(nlog + nlogn) time for sorting and heap
    O(n) space
*/
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

int maxCourses(vector<pair<int,int>> &courses) {

    sort(courses.begin(), courses.end(), [](const auto &a, const auto &b){
        return a.second < b.second;
    });

    priority_queue<int> pq; // store max durations

    int time = 0;
    int count = 0;

    for(auto &[duration, deadline] : courses) {

        // take the course
        time += duration;
        pq.push(deadline);
        count++;

        if(time > deadline) {
            // remove the longest course
            time -= pq.top();
            pq.pop();
            count--;
        }
    }
    return count;
}

int main() {
    
    vector<pair<int,int>> courses = {{100,200}, {200,1300}, {1000,1250}, {2000,3200}};
    

    cout << maxCourses(courses) << endl;

    return 0;
}
