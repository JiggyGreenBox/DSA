/*
find median from data stream
    [https://leetcode.com/problems/find-median-from-data-stream/description/]

The median is the middle value in an ordered integer list. If the 
size of the list is even, there is no middle value, and the median is 
the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the 
data structure.
double findMedian() returns the median of all elements so far. 
Answers within 10-5 of the actual answer will be accepted.
 

Example 1:

    Input
    ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", 
    "findMedian"]
    [[], [1], [2], [], [3], []]
    Output
    [null, null, null, 1.5, null, 2.0]

    Explanation
    MedianFinder medianFinder = new MedianFinder();
    medianFinder.addNum(1);    // arr = [1]
    medianFinder.addNum(2);    // arr = [1, 2]
    medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
    medianFinder.addNum(3);    // arr[1, 2, 3]
    medianFinder.findMedian(); // return 2.0
*/


/*
find median from data stream
    do we need a heap
    if i make sure vector is always sorted
        i know the size
        i can find n/2 if n is odd
        and n/2 -1 and n/2 if n is even


    [2,4,7,8] n=4
    [2,4,7,8, 9] n=5
    5/2 = 2

    [2,4,7,8,9,10] n=6

    [(n/2)-1, (n/2)]
        7,8

    this is valid but expensive


----

    we use 2 heaps

    we dont care about all elements being sorted
    we just want the middle or midle 2

    split all elements into 2 halves
    2,3,5    8,10,12

    we only care about 5 and 8
    an incoming element will cause shifts only based on 5 and 8
    we want max from the left and min from the right
    we maintain a size difference of max 1
    this gives us the median property



Max Heap

Stores lower half.

Top = largest of lower half.

--------------------------

Min Heap

Stores upper half.

Top = smallest of upper half.

*/


/*
Invariants

1. Order

    Every element in the max heap
        <=
    Every element in the min heap.

2. Size

    |maxHeap| == |minHeap|

    OR

    |maxHeap| == |minHeap| + 1

    (We usually allow the max heap to have one extra element.)

Insertion

Insert into the appropriate heap based on the boundary.

If the heaps become unbalanced,
move the top element from one heap to the other.

Median

Odd number of elements

    maxHeap.top()

Even number of elements

    (maxHeap.top() + minHeap.top()) / 2


*/


#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class MedianFinder {

private:
    priority_queue<int> lower; // lower_half
    priority_queue<int, vector<int>, greater<int>> upper; // upper_half

    

public:
    MedianFinder() {}
    
    void addNum(int num) {
        
        // we allow lower to handle odd case
        // lower will be +1, but never +2
        // that also means lower is first insert, if both are empty

        // if num belongs in the lower half push ([1,3,5], num=2)
        if(lower.empty() || num <= lower.top()) {
            lower.push(num);
        }
        else {
            upper.push(num);
        }

        // check balance
        if(lower.size() > upper.size() + 1) {
            upper.push(lower.top());
            lower.pop();
        }

        // lower allowed to be upper+1
        // that means upper is never allowed to be bigger
        if(upper.size() > lower.size()) {
            lower.push(upper.top());
            upper.pop();
        }
    }
    
    double findMedian() {
        if(lower.size() == upper.size()) {
             return (lower.top() + upper.top()) / 2.0;
        }
        
        return lower.top();
    }
};

int main() {
    return 0;
}

/*
Two Heap Median

addNum:
    O(log n)

findMedian:
    O(1)

Space:
    O(n)


addNum
    each heap operation is log-n
        lower, upper and the shift between both
        worst case is 3 logn

            lower.push(num);              // O(log n)
            upper.push(lower.top());      // O(log n)
            lower.pop();                  // O(log n)

        OR
            upper.push(num);              // O(log n)
            lower.push(upper.top());      // O(log n)
            upper.pop();                  // O(log n)
*/