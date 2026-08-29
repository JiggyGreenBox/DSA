// Sliding Window Median



// this is the next problem in the list. do we call the class that we just made with 2 heaps.
// add numbers till k window
//     then call median at each step

//     but its easy to add to the window
//     how do we remove the from the stream?



// It's one of the hardest heap questions on LeetCode.

/*
Sliding Window Median
    [https://leetcode.com/problems/sliding-window-median/description/]

    The median is the middle value in an ordered integer list. If the 
    size of the list is even, there is no middle value. So the median is 
    the mean of the two middle values.

    For examples, if arr = [2,3,4], the median is 3.
    For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.
    You are given an integer array nums and an integer k. There is a 
    sliding window of size k which is moving from the very left of the 
    array to the very right. You can only see the k numbers in the 
    window. Each time the sliding window moves right by one position.

    Return the median array for each window in the original array. 
    Answers within 10-5 of the actual value will be accepted.


    
Example 1:

    Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
    Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
    Explanation: 
    Window position                Median
    ---------------                -----
    [1  3  -1] -3  5  3  6  7        1
    1 [3  -1  -3] 5  3  6  7       -1
    1  3 [-1  -3  5] 3  6  7       -1
    1  3  -1 [-3  5  3] 6  7        3
    1  3  -1  -3 [5  3  6] 7        5
    1  3  -1  -3  5 [3  6  7]       6

Example 2:

    Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
    Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]


--------------------------------------------

when we want median from a stream
    we just add, the median updates

but now we have a moving window
    we need to be able to remove elements from the heap
    this isnt efficient

    priority queue gives top
    but O(n) to remove

we need a different DS
    insert
    remove any value
    get max
    get min

multiset
    with begin / end
    and rbegin / rend

    multiset<int> lower;
    multiset<int> upper;

derive the operations
    if lower empty
    or num <= largest element in lower

        put in lower

    else

        put in upper

    



*/

#include <vector>
#include <set>
using namespace std;

class Solution {

    multiset<int> lower;
    multiset<int> upper;

    /*
    rbegin vs prev(vec.end())

    we cant use rbegin for erase
    because erase needs an iterator
    not a reverse iterator

    Need to READ largest:
        *rbegin()

    Need to ERASE largest:
        prev(end())
    */

    void rebalance() {

        if (lower.size() > upper.size() + 1) {

            auto it = prev(lower.end());

            upper.insert(*it);
            lower.erase(it);
        }

        if (upper.size() > lower.size()) {

            auto it = upper.begin();

            lower.insert(*it);
            upper.erase(it);
        }
    }

    void add(int num) {

        if (lower.empty() || num <= *lower.rbegin())
            lower.insert(num);
        else
            upper.insert(num);

        rebalance();
    }

    void remove(int num) {

        auto it = lower.find(num);

        if (it != lower.end()) {
            lower.erase(it);
        }
        else {
            it = upper.find(num);
            upper.erase(it);
        }

        rebalance();
    }

    double median() {

        if (lower.size() == upper.size()) {
            return (*lower.rbegin() + *upper.begin()) / 2.0;
        }

        return *lower.rbegin();
    }

public:

    vector<double> medianSlidingWindow(
        vector<int>& nums,
        int k
    ) {

        vector<double> ans;

        // First window
        for (int i = 0; i < k; i++)
            add(nums[i]);

        ans.push_back(median());

        // Slide
        for (int i = k; i < nums.size(); i++) {

            remove(nums[i - k]);
            add(nums[i]);

            ans.push_back(median());
        }

        return ans;
    }
};

/*
Sliding Window Median

2 multisets:
    lower = smaller half
    upper = larger half

add:
    O(log k)

remove:
    O(log k)

rebalance:
    O(log k)

median:
    O(1)

Total:
    O(n log k)

Auxiliary space:
    O(k)

Output space:
    O(n)


*/