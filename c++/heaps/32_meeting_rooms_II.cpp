/*
Meeting Rooms II
    [https://www.geeksforgeeks.org/problems/attend-all-meetings-ii/1]


Given two arrays start[] and end[] such that start[i] is the starting 
time of ith meeting and end[i] is the ending time of ith meeting. 
Return the minimum number of rooms required to attend all meetings.

Note: A person can also attend a meeting if it's starting time is 
same as the previous meeting's ending time.

Examples:

    Input: start[] = [1, 10, 7], end[] = [4, 15, 10]
    Output: 1
    Explanation: Since all the meetings are held at different times, it 
    is possible to attend all the meetings in a single room.

    Input: start[] = [2, 9, 6], end[] = [4, 12, 10]
    Output: 2
    Explanation: 1st and 2nd meetings at one room but for 3rd meeting one 
    another room required.
Constraints:
    1 ≤ start.size() = end.size() ≤ 105
    0 ≤ start[i] < end[i] ≤ 106

*/

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int minMeetingRooms(vector<vector<int>>& intervals) {

    // Process meetings by start time
    sort(intervals.begin(), intervals.end());

    // End times of meetings currently using rooms
    priority_queue<int, vector<int>, greater<int>> pq;

    for (auto& interval : intervals) {

        int start = interval[0];
        int end   = interval[1];

        // Earliest room is free
        if (!pq.empty() && start >= pq.top()) {
            pq.pop();
        }

        // Occupy a room until 'end'
        pq.push(end);
    }

    return pq.size();
}

/*
difference vs max meetings in 1 room
    we dont choose a meeting

    here we have to choose all meetings
*/


/*
Meeting Rooms II

Goal:
    minimum rooms for ALL meetings

Approach 1:
    sort starts
    sort ends
    two pointers
    → O(n log n)

Approach 2:
    sort meetings by start
    min-heap of end times

    top = earliest room to become free

    if start >= top:
        pop → reuse room

    push current end

    → O(n log n)


NOTE
    while vs if
    it changes the meaning of the heap
    for while
        heap means current rooms/platforms
            need to track max at each step

    for if
        heap means total created
            we only pop once per iteration
                we can return the heap size
*/