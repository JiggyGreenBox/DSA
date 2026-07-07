#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Queue Reconstruction by Height
    [https://leetcode.com/problems/queue-reconstruction-by-height/description/]

You are given an array of people, people, which are the attributes of 
some people in a queue (not necessarily in order). Each people[i] = 
[hi, ki] represents the ith person of height hi with exactly ki other 
people in front who have a height greater than or equal to hi.

Reconstruct and return the queue that is represented by the input 
array people. The returned queue should be formatted as an array 
queue, where queue[j] = [hj, kj] is the attributes of the jth person 
in the queue (queue[0] is the person at the front of the queue).

Example 1:

    Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
    Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
    Explanation:
    Person 0 has height 5 with no other people taller or the same height 
    in front.
    Person 1 has height 7 with no other people taller or the same height 
    in front.
    Person 2 has height 5 with two persons taller or the same height in 
    front, which is person 0 and 1.
    Person 3 has height 6 with one person taller or the same height in 
    front, which is person 1.
    Person 4 has height 4 with four people taller or the same height in 
    front, which are people 0, 1, 2, and 3.
    Person 5 has height 7 with one person taller or the same height in 
    front, which is person 1.
    Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed 
    queue.

Example 2:
    Input: people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
    Output: [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
*/

/*
Invariant:
Every person already placed has height >= every person not yet placed.

Therefore, inserting a shorter person can never change the number of
people >= h in front of an already placed person.

[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]
sort by height in reverse but increasing spots (k)
    why? 
        because once we place tall people
        their spots are not affected by short people

        smaller inserts before do not change tall position
        so we will always use insert(begin + k) to shift tall people behind

    [7,0]
    [7,1]
    [6,1]
    [5,0]
    [5,2]
    [4,4]

    7,0
    insert at 0
        ans = [[7,0]]
    7,1
    insert at 1
        ans = [[7,0], [7,1]]

    6,1
    insert at 1
        7,1 will not be affected
        ans = [[7,0], [6,1], [7,1]]
    5,0
        insert at 0
        7,0 will not be affected
        ans = [[5,0],[7,0], [6,1], [7,1]]

    5,2
        insert at 2
        ans = [[5,0],[7,0], [5,2], [6,1], [7,1]]

    4,4
        insert at 4
        ans = [[5,0],[7,0], [5,2], [6,1], [4,4], [7,1]]

*/



vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    vector<vector<int>> ans;

    sort(people.begin(), people.end(), 
            [](const auto &a, const auto &b) {
                if(a[0] == b[0]) {
                    return a[1] < b[1];
                }
                return a[0] > b[0];
            });

    for(const auto &person : people) {
        int k = person[1];
        ans.insert(ans.begin() + k, person);
    }

    return ans;
}

void print(const vector<vector<int>>& ans) {
    cout << "[ ";
    for(auto &vec : ans) {
        cout << "[ ";
        cout << vec[0];
        cout << ",";
        cout << vec[1];
        cout << "] ";
    }
    cout << "]\n";
}

int main() {
    vector<vector<int>> people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    print(reconstructQueue(people));
    return 0;
}