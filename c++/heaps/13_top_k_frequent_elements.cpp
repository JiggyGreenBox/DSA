
/*
Top K Frequent Elements
    [https://leetcode.com/problems/top-k-frequent-elements/description/]


Given an integer array nums and an integer k, return the k most 
frequent elements. You may return the answer in any order.

 

Example 1:

    Input: nums = [1,1,1,2,2,3], k = 2

    Output: [1,2]

Example 2:

    Input: nums = [1], k = 1

    Output: [1]

Example 3:

    Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2

    Output: [1,2]

*/


/*
Top K Frequent Elements
i need freq, element

this needs to be sorted by freq
    we could use a map
    and return the top k of map

we could use a min-heap of pair
    but why this over a map
        map would sort in ascending order

    also can we optimize?
    we use a min-heap
        for min pair
*/

/*
Top K Pattern

Approach 1

Sort all

O(n log n)

-------------------------

Approach 2

Max Heap

Push all

Pop K

O(n log n)

No improvement.

-------------------------

Approach 3

Min Heap of size K

Keep only K best elements.

Root = weakest candidate.

If better element arrives

    pop root

    push new

Complexity

O(n log K)

This is the canonical heap optimization.
*/
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) {

    unordered_map<int, int> freq;

    // Count frequencies
    for (int num : nums)
        freq[num]++;

    // Min heap: {frequency, element}
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    for (auto &[num, count] : freq) {

        pq.push({count, num});

        if (pq.size() > k)
            pq.pop();

        

        // if (pq.size() < k){
        //     pq.push({count, num});
        // }            
        // else if(count > pq.top().first){
        //     pq.pop();
        //     pq.push({count, num});
        // }            
    }

    vector<int> ans;

    while (!pq.empty()) {
        ans.push_back(pq.top().second);
        pq.pop();
    }

    return ans;
}

/*
if follow up of stream
then we have the option 
to just add freq
and build heap when queried
    this works when queries are not called often

if queries are very high now we change the approach:

    frequency map:
        freq[num] = count

    ordered set:
        (frequency, num)


        freq:
        A → 5
        B → 3
        C → 7
        D → 2

        ordered set:
        (2,D)
        (3,B)
        (5,A)
        (7,C)

    A = 5
    another A is added

        order.erase({freq[A], A});

        freq[A]++;

        order.insert({freq[A], A});

    we use heap over set
    heap is good for best right now

*/
#include <set>
class TopKFrequentStream {

    int k;

    unordered_map<int, int> freq;

    // sorted by frequency
    // then by value to make each pair unique
    set<pair<int, int>> order;

public:

    TopKFrequentStream(int k) : k(k) {}

    void add(int num) {

        if (freq[num] > 0)
            order.erase({freq[num], num});

        freq[num]++;

        order.insert({freq[num], num});
    }

    vector<int> topK() {

        vector<int> ans;

        auto it = order.rbegin();

        while (it != order.rend() && ans.size() < k) {
            ans.push_back(it->second);
            ++it;
        }

        return ans;
    }
};

// rbegin and rend is reverse
// set stores in ascending order