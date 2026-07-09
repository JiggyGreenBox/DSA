
/*


Find K Closest Elements
    [https://leetcode.com/problems/find-k-closest-elements/description/]


Given a sorted integer array arr, two integers k and x, return the k 
closest integers to x in the array. The result should also be sorted 
in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b
 

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3

Output: [1,2,3,4]

Example 2:

Input: arr = [1,1,2,3,4,5], k = 4, x = -1

Output: [1,1,2,3]

*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


/*
we need the top k
or k smallest
use a min-heap and return top k
or use a max heap of size k
*/

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    priority_queue<pair<int,int>> pq;

    for(int num : arr) {

        int dist = abs(num-x);

        pq.push({dist, num});

        if(pq.size() > k)
            pq.pop();
    }

    vector<int> ans;
    while(!pq.empty()) {
        ans.push_back(pq.top().second);
        pq.pop();
    }

    sort(ans.begin(), ans.end());
    
    return ans;
}

int main() {

    



    return 0;
}