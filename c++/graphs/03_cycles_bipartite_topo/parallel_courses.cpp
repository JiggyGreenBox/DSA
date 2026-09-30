/*
Problem: Minimum Semesters to Complete Courses

    There are n courses numbered 1 to n.

    You are given a list of prerequisite relationships:
        relations[i] = [prevCourse, nextCourse]

    This means:
    You must complete prevCourse before you can take nextCourse.

    You can take any number of courses simultaneously in one semester, as 
    long as all their prerequisites have already been completed.

    Return the minimum number of semesters required to complete all n 
    courses.

    If it is impossible because of a cycle, return -1.


Examples
n = 4

relations = [
    [1,3],
    [2,3],
    [3,4]
]

1 ──┐
    ├──> 3 ──> 4
2 ──┘

    sem 1
        [1,2]
    sem 2
        3
    sem 3
        4

    ans : 3

Example2:
n = 5

relations = [
    [1,2],
    [1,3],
    [2,4],
    [3,4],
    [4,5]
]

    Semester 1: 1
    Semester 2: 2, 3
    Semester 3: 4
    Semester 4: 5

    ans 4


n = 3

relations = [
    [1,2],
    [2,3],
    [3,1]
]

1 → 2 → 3
↑       ↓
└───────┘

ans -1
*/

/*
courses depend on each other
    so we have a graph where
    we can arrange topographically

    then at each level we push topo = 0
        into queue
        the queue represent each semester
        incremen the count for each level

    we also have to account for 1 more issue
        each time we process a course
        keep a count
    
    at the end if completed < n
        return -1
        could not take all courses
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int numSemesters(int n, vector<vector<int>> &relations) {
    vector<int> adj[n+1];
    for(auto &r : relations) {
        adj[r[0]].push_back(r[1]);
    }

    vector<int> indegree(n+1, 0);
    for(int i=1; i<=n; i++) {
        for(int course : adj[i])
            indegree[course]++;
    }


    int completed = 0; // courses completed
    int semesters = 0;

    queue<int> q;
    for(int i=1; i<=n; i++) {
        if(indegree[i] == 0) {
            q.push(i);            
        }            
    }

    

    while(!q.empty()) {
        int size = q.size();

        while(size--) {
            int course = q.front();
            q.pop();

            completed++;

            for(int next : adj[course]) {
                indegree[next]--;
                if(indegree[next] == 0) {                    
                    q.push(next);
                }
            }
        }
        semesters++;
    }
    
    if(completed < n)
        return -1;

    return semesters;
}

int main() {

    int n = 4;
    vector<vector<int>> relations = {
                                        {1,3},
                                        {2,3},
                                        {3,4}};

    auto x = numSemesters(n, relations);

    n = 5;
    relations = {
        {1,2},
        {1,3},
        {2,4},
        {3,4},
        {4,5}
    };
    x = numSemesters(n, relations);


    n = 3;
    relations = {
        {1,2},
        {2,3},
        {3,1}
    };
    x = numSemesters(n, relations);

    return 0;
}