#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/*
Task Scheduler
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
Task Scheduler

    find the max freq of tasks
    A,A,A n=2

    then we have 2 gaps between each task
    A--A--A

    we have (freq-1) blocks of gaps
        (block)(block)A
        (A--)(A--)A
        freq = 3, blocks = 2
            freq-1

    (A--) is considered as 1 block
        that is n+char, n+1

    after we complete the last task we are done
    so we finish at blocks + 1

    total_time  = nums_blocks + 1
                = (freq-1) * (blocks) + 1
                = (freq-1) * (n+1) + 1

    but what if we have another char with same frequency
    A,A,A,B,B,B n=2

    A--A--A
     B--B--B

    notice we will have to put it at the end of A
    if we had
    A = 3
    B = 3
    C = 3
    D = 3

    
    then we would have to put +4 after
    total_time  = (freq-1) * (n+1) + maxCount
        where maxCount is count of maxFreq
            in this case max_freq = 3, and 4 chars have max_freq=3
            maxCount = 4                
                
*/

 int leastInterval(vector<char>& tasks, int n) {

    vector<int> freq(26, 0);

    for (char task : tasks)
        freq[task - 'A']++;

    int maxFreq = *max_element(freq.begin(), freq.end());

    int maxCount = 0;

    for (int f : freq)
        if (f == maxFreq)
            maxCount++;

    return max(
        (int)tasks.size(),
        (maxFreq - 1) * (n + 1) + maxCount
    );
}

int main() {
    return 0;
}