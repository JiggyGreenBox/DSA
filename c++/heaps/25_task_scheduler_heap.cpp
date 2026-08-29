/*
task_scheduler_heap
    [https://leetcode.com/problems/task-scheduler/description/]

You are given an array of CPU tasks, each labeled with a letter from 
A to Z, and a number n. Each CPU interval can be idle or allow the 
completion of one task. Tasks can be completed in any order, but 
there's a constraint: there has to be a gap of at least n intervals 
between two tasks with the same label.

Return the minimum number of CPU intervals required to complete all 
tasks.

 

Example 1:

    Input: tasks = ["A","A","A","B","B","B"], n = 2

    Output: 8

    Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle 
    -> A -> B.

    After completing task A, you must wait two intervals before doing A 
    again. The same applies to task B. In the 3rd interval, neither A nor 
    B can be done, so you idle. By the 4th interval, you can do A again 
    as 2 intervals have passed.

Example 2:

    Input: tasks = ["A","C","A","B","D","B"], n = 1

    Output: 6

    Explanation: A possible sequence is: A -> B -> C -> D -> A -> B.

    With a cooling interval of 1, you can repeat a task after just one 
    other task.

Example 3:

    Input: tasks = ["A","A","A", "B","B","B"], n = 3

    Output: 10

    Explanation: A possible sequence is: A -> B -> idle -> idle -> A -> B 
    -> idle -> idle -> A -> B.

    There are only two types of tasks, A and B, which need to be 
    separated by 3 intervals. This leads to idling twice between 
    repetitions of these tasks.
*/

/*
task_scheduler_heap
    
We maintain:
    freq map
        ↓
    max heap of available tasks
        ↓
    always choose highest-frequency available task

But when we use a task, it becomes unavailable for the next n intervals.

So we need a cooldown queue as well.


               max heap
           available tasks
                 ↓
             choose A
                 ↓
        A goes into cooldown
                 ↓
       ┌─────────────────┐
       │ cooldown queue  │
       │ (A, ready_time) │
       └─────────────────┘

Max heap:
    tasks that are currently available
    ordered by remaining frequency

Cooldown queue:
    tasks that were recently used
    ordered by when they become available
*/

#include <vector>
#include <queue>
using namespace std;

int leastInterval(vector<char>& tasks, int n) {

    vector<int> freq(26, 0);

    for (char task : tasks)
        freq[task - 'A']++;

    priority_queue<int> pq;

    for (int f : freq)
        if (f > 0)
            pq.push(f);

    // {time when available, remaining frequency}
    queue<pair<int, int>> cooldown;

    int time = 0;

    while (!pq.empty() || !cooldown.empty()) {

        time++;

        // Tasks whose cooldown has finished
        if (!cooldown.empty() &&
            cooldown.front().first == time) {

            pq.push(cooldown.front().second);
            cooldown.pop();
        }

        if (!pq.empty()) {

            int remaining = pq.top();
            pq.pop();

            remaining--;

            if (remaining > 0) {
                cooldown.push({time + n + 1, remaining});
            }
        }
    }

    return time;
}

/*
Why time + n + 1?

    If we execute A at:
    time = 1

    time 1: A
    time 2: idle/other
    time 3: idle/other
    time 4: A
*/

// what if we had to return the tasks instead of the time
#include <string>
#include <tuple>
string scheduleTasks(vector<char>& tasks, int n) {

    vector<int> freq(26, 0);

    for (char task : tasks)
        freq[task - 'A']++;

    priority_queue<pair<int, char>> pq;

    for (char c = 'A'; c <= 'Z'; c++) {
        if (freq[c - 'A'] > 0)
            pq.push({freq[c - 'A'], c});
    }

    // {time when available, remaining frequency, task}
    queue<tuple<int, int, char>> cooldown;

    string ans;
    int time = 0;

    while (!pq.empty() || !cooldown.empty()) {

        time++;

        // Release tasks whose cooldown is finished
        while (!cooldown.empty() &&
               get<0>(cooldown.front()) <= time) {

            auto [readyTime, remaining, task] = cooldown.front();
            cooldown.pop();

            pq.push({remaining, task});
        }

        if (!pq.empty()) {

            auto [remaining, task] = pq.top();
            pq.pop();

            ans.push_back(task);

            remaining--;

            if (remaining > 0) {
                cooldown.push({
                    time + n + 1,
                    remaining,
                    task
                });
            }

        } else {
            ans.push_back('_'); // idle
        }
    }

    return ans;
}