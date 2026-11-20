/*
============================================
nov 19
    last nov 14
============================================
Problem 1
============================================
minimum number of conference rooms required

we are given meetings in this manner
    intervals[i] = {start_i, end_i};

if we sort by end
    then we have a few options
    [1,2]
    [3,4]
    end is less than next start
        no overlap

    [1,5]
    [2,6]
        end is larger than next start
            overlap, need another room

    what about clearing rooms
        [1,5]
        [2,8]
        [6,10]
            store 5 in heap
                2 < 5
                    push 6
            6 > heap.top() 5
                pop / vacate room

            6 > 8?
                no
                    push 10

        we can track heap size
            in this case we needed 2 rooms

    complexity
        nlogn sorting
        nlogn heap insert

        time total nlogn
        space n heap

int minRooms(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b) {
        return a[0] < b[0];
    });
    

    priority_queue<int, vector<int>, greater<int>> pq;

    int ans = 0;

    // add room information
    vector<int> rooms;

    for(auto &i : intervals) {

        while(!pq.empty() && i[0] >= pq.top())
            pq.pop(); // vacate room

        rooms.push_back(pq.size());
        pq.push(i[1]); // occupy room
        ans = max(ans, (int)pq.size());
    }
    // return rooms
    return ans;
}

now track the room number used at each step

vector<int> minRooms2(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b) {
        return a[0] < b[0];
    });
    
    using P = pair<int,int>; // endtime, roomid
    priority_queue<P, vector<P>, greater<P>> pq;

    // add room information
    priority_queue<int, vector<int>, greater<int>> available;

    int lastRoom = 0;
    vector<int> roomsUsed;

    for(auto &i : intervals) {

        while(!pq.empty() && i[0] >= pq.top().first) {
            available.push(pq.top().second); // make room available
            pq.pop(); // vacate room
        }
            

        // use a new room
        if(available.empty()) {
            pq.push({i[1], lastRoom}); // occupy new room
            roomsUsed.push_back(lastRoom);            
            lastRoom++;
        }            
        // reuse a room
        else {
            pq.push({i[1], available.top()}); // occupy reused room     
            roomsUsed.push_back(available.top());  
            available.pop();
        }
            
    }
    return roomsUsed;    
}
============================================
Problem 2
============================================
longest consecutive sequence.

Input:  [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: [1, 2, 3, 4]

Input:  [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
Output: 9

Input:  [1, 0, 1, 2]
Output: 3

-----
brute force approach
    for each number found start a loop
        break when the next number isnt found
            n^2 worst time

observation
    we need query access
        well use a unordered_set

    then for each num in nums
        if num-1 exists
            this cant be the start
            skip

        while num+1 is in map
            count++

        track max-count

// O(n) time
// O(n) space
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> mset(nums.begin(), nums.end());

    int longest = 0;
    int longestStart = 0;

    for(int num : nums) {
        if(mset.count(num-1))
            continue; // not the starting of the sequence

        int count = 1;
        int start = num;        
        while(mset.count(num + 1)){
            num++;
            count++;
        }
        // longest = max(longest, count);
        if(count > longest) {
            longestStart = start;
            longest = count;
        }
    }
    vector<int> result;
    for(int i=0; i<longest; i++)
        result.push_back(longestStart+i);

    return longest;
}

modification was to print the longest sequence

============================================
Problem 3
============================================

subarrays whose sum equals k.
    we have negative numbers
    so sliding window cant be used

    we want count of sum(i,j) == k
        prefix[r] - prefix[l-1] == k
        prefix[l-1] == prefix[r] - k



*/

#include <vector>
#include <queue>
#include <unordered_map>
#include <assert.h>
using namespace std;

// O(n) time
// O(n) space
int subarraySum(vector<int>& nums, int k) {

    int n = nums.size();

    unordered_map<int, int> mpp;
    mpp[0] = 1;

    int prefix = 0;
    int count = 0;
    for(int i=0; i<n; i++) {
        prefix += nums[i];

        int search = prefix - k;
        if(mpp.count(search)) {
            count += mpp[search];
        }

        mpp[prefix]++;
    }
    return count;
}

int main() {
    vector<int> nums = {1, 1, 1};
    int k = 2;
    assert(subarraySum(nums, k) == 2);
    
    nums = {1, 2, 3}; k = 3;
    assert(subarraySum(nums, k) == 2);

    nums = {1, -1, 0}; k = 0;
    assert(subarraySum(nums, k) == 3);
    return 0;
}