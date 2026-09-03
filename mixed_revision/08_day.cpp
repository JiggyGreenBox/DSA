/*
27th aug
    last 26th


Problem 1
    You are given an array of intervals:
    Each interval represents a meeting.

    Return the minimum number of meeting rooms required so that all 
    meetings can take place without overlapping in the same room.

Examples
    intervals = [[0,30],[5,10],[15,20]]

    Output: 2

    -----

    intervals = [[7,10],[2,4]]

    Output: 1



Brute force:

Observation:
    for minimum platforms we are given 2 separate arrays
    which we can sort and then have a in-out counter system

    split into
    start  [0,5,15]
    end [10,20,30]

    s = 0;
    e = 0
    start[s] < end[e]
        rooms++
        s++
    else
        rooms--
        e++

    maxRooms = max(maxRooms, rooms)

    ---

    if we dont want to split
    sort by end time
    we want to finish meetings early
        [5,10],
        [15,20]
        [0,30],

    rooms = 1
    then iterate from 1..n-1
        if startTime > prevEnd
            rooms++

Invariant:
Algorithm:
    int meetingRoom(vector<vector<int>> &meetings) {

        sort(meetings.begin(), meetings.end(), [](const auto &a, const auto& b){
            return a[1] < b[1];
        });

        int rooms = 1;
        for(int i=1; i<meetings.size(); i++) {
            if(meetings[i][0] > meetings[i-1][1])
                rooms++;
        }
        return rooms;
    }
Complexity:
    nlogn to sort
    O(n) to iterate
    O(1) extra space


Review
    wrong algorithm

You remembered the correct pattern from Minimum Platforms, which is 
good. But the actual algorithm you coded is not the meeting-room 
problem.  


[0,10]
[1,9]
[2,8]

[2,8]
[1,9]

[0,10]

*/
#include <vector>
#include <algorithm>
using namespace std;
int meetingRooms(vector<vector<int>>& meetings) {

    int n = meetings.size();

    vector<int> start(n);
    vector<int> end(n);

    for(int i = 0; i < n; i++) {
        start[i] = meetings[i][0];
        end[i] = meetings[i][1];
    }

    sort(start.begin(), start.end());
    sort(end.begin(), end.end());

    int s = 0;
    int e = 0;

    int rooms = 0;
    int maxRooms = 0;

    while(s < n) {

        if(start[s] < end[e]) {
            rooms++;
            maxRooms = max(maxRooms, rooms);
            s++;
        }
        else {
            rooms--;
            e++;
        }
    }

    return maxRooms;
}




/*
Problem 2 — Mixed Revision

You are given an array of integers nums and an integer k.

Return the k-th largest element in the array.

You may assume k is valid.


Brute force:
    sort array then iterate backwards k times
    nlogn

    use a max heap and pop k times

    use a minheap of size k
    O(nlogk) time
    O(k) space
Observation:
Invariant:
Algorithm:
    int kthLargest(vector<int> &nums, int k) {

        priority_queue<int, vector<int>, greater<int>> pq;

        for(int num : nums) {
            pq.push(num);

            if(pq.size() > k)
                pq.pop();
        }
        return pq.top();
    }
Complexity:
    O(nlogk) time
    O(k) space


-----------------
review
    green


-----------------

Problem 3 — Mixed Revision

    You are given a binary search tree (BST) and two nodes p and q.

    Find the lowest common ancestor of p and q.


          6
        /   \
       2     8
      / \   / \
     0   4 7   9
        / \
       3   5


    p = 2
    q = 8
        6

    p = 2
    q = 4
        2

Brute Force:
    
Observation:
    BST property allows us to go left or right
    and eliminate half the tree easily
Invariant:
    if both values are less than node
        go left
    if both are greater
        go right
    else
        node is the lca
Algorithm:
    Node* lca(Node* root, Node* p, Node* q) {
        while(root->val < p->val && root->val < q->val) {
            root = root->left;
        }
        while(root->val > p->val && root->val > q->val) {
            root = root->right;
        }
        return root;
    }
Complexity:
    O(logn) time
    O(1) space
*/

