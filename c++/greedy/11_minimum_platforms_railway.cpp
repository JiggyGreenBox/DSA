#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


int findPlatform2(vector<int>& Arrival, vector<int>& Departure){
    sort(Arrival.begin(), Arrival.end());
    sort(Departure.begin(), Departure.end());
    
    int i = 0;
    int j = 0;
    int n = Arrival.size();

    int count = 0;
    int max_count = 0;
    
    while(i<n && j<n) {

        // a train arrives
        if(Arrival[i] <= Departure[j]) {
            count++;
            i++;
        }
        // departs
        else {
            count--;
            j++;
        }
        max_count = max(max_count, count);
    }
    return max_count;
}

int main() {
    vector<int> Arrival   = {900,  940,  950, 1100, 1500, 1800};
    vector<int> Departure = {910, 1200, 1120, 1130, 1900, 2000};
    cout << findPlatform2(Arrival, Departure) << endl;
    return 0;
}

/*
Minimum number of platforms required for a railway

Given the arrival and departure times of all trains reaching a 
particular railway station, determine the minimum number of platforms 
required so that no train is kept waiting. Consider all trains arrive 
and depart on the same day.

In any particular instance, the same platform cannot be used for both 
the departure of one train and the arrival of another train, 
necessitating the use of different platforms in such cases.

Note: Time intervals are in the minutes , Leading zeros for minutes 
less than 1000 are optional (e.g., 0900 is the same as 900).

Example 1

    Input : Arrival =   [900,  940,  950, 1100, 1500, 1800] , 
            Departure = [910, 1200, 1120, 1130, 1900, 2000]

    Output : 3

    Explanation : The first , second , fifth number train can use the 
    platform 1.

    The third and sixth train can use the platform 2.
    The fourth train will use platform 3.
    So total we need 3 different platforms for the railway station so 
    that no train is kept waiting.

Example 2

    Input : Arrival   = [ 900, 1100, 1235] , 
            Departure = [1000, 1200, 1240]
    Output : 1

    Explanation : All the three trains can use the platform 1.
    So we required only 1 platform.

Example 3

    Input : Arrival   = [ 900, 1000, 1200] , 
            Departure = [1000, 1200, 1240]
    Output: 2
*/

/*

[ 900, 1000, 1200] , 
[1000, 1200, 1240]

900,1000
1000,1200
1200,1240

[ 900, 1100, 1235] , 
[1000, 1200, 1240]

900, 1000
900, 1200
1100,1300

Minimum number of platforms required for a railway
observation
    we can treat the arrival and departure as a pair or interval
    then if
    900,1000
    1100,1200
    can share the same platform because currStart > prevEnd

    but when
    900, 1000
    900, 1200
    1100,1300

    how do we know that train3 can use platform 1
        1100 > 1000 yes but state management is difficult
*/

/*
min heap approach
heap slots are platform slots
we push departure when we occupy the platform
then we use start times to check

900->1000
    push 1000
930->1100
    930 >= 1000?
        no push 1100
1030->1300
    1030 >= 1000
        pop
        push

return minHeap size
*/

int findPlatform(vector<int>& Arrival, vector<int>& Departure){

    vector<pair<int, int>> intervals;

    for(int i=0; i<Arrival.size(); i++)
        intervals.push_back({Arrival[i], Departure[i]});
    

    sort(intervals.begin(), intervals.end());  // sort by arrival

    priority_queue<int, vector<int>, greater<int>> minHeap;

    int ans = 0;

    for (auto &[arrival, departure] : intervals) {

        // Free every platform whose train has departed.
        while (!minHeap.empty() && 
            arrival >= minHeap.top()) {
                minHeap.pop();
        }
            
        // occupy a platform
        minHeap.push(departure);

        ans = max(ans, (int)minHeap.size());
    }

    return ans;
}

/*
Meeting Rooms / Railway Platforms

Sort by arrival time.

Min heap:
    departure times of currently active trains.

For each arriving train:

    Remove all departures <= arrival.

    Push current departure.

    heap.size()
        = platforms currently required.

    maximum heap.size()
        = answer.
*/

/*
                    "How many intervals are active?"
                              │
              ┌───────────────┴───────────────┐
              ↓                               ↓
        Two pointers                       Min heap
        event-based                        interval-based

        arrival → +1                         add departure
        departure → -1                       remove expired

        O(n log n)                           O(n log n)
        O(1) space                           O(n) space



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

/*
this problem was min meeting rooms 
    use a heap to see if we can make the meeting
    if not create another heap slot

then the extention
    can we track the rooms used
    return the roomId
*/
vector<int> minRooms2(vector<vector<int>>& intervals) {

    using P = tuple<int, int, int>; // start, end, original index

    vector<P> meetings;

    for(int i = 0; i < intervals.size(); i++)
        meetings.push_back({intervals[i][0], intervals[i][1], i});

    sort(meetings.begin(), meetings.end());

    using Room = pair<int,int>; // end_time, room_id

    priority_queue<Room, vector<Room>, greater<Room>> occupied;
    priority_queue<int, vector<int>, greater<int>> available;

    int lastRoom = 0;
    vector<int> roomsUsed(intervals.size());

    for(auto [start, end, idx] : meetings) {

        while(!occupied.empty() && start >= occupied.top().first) {
            available.push(occupied.top().second);
            occupied.pop();
        }

        int roomId;

        if(available.empty()) {
            roomId = lastRoom++;
        }
        else {
            roomId = available.top();
            available.pop();
        }

        occupied.push({end, roomId});
        roomsUsed[idx] = roomId;
    }

    return roomsUsed;
}