#include <vector>
#include <queue>
using namespace std;

/*
Kth largest element in a stream of running integers

Implement a class KthLargest to find the kth largest number in a 
stream. It should have the following methods:

KthLargest(int k, int [] nums) Initializes the object with the 
integer k and the initial stream of numbers in nums
int add(int val) Appends the integer val to the stream and returns 
the kth largest element in the stream.
Note that it is the kth largest element in the sorted order, not the 
kth distinct element.

*/

class KthLargest
{
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;

public:

    KthLargest(int k, vector<int>& nums)
    {
        this->k = k;

        for(int x : nums)
        {
            if(pq.size() < k)
            {
                pq.push(x);
            }
            else if(x > pq.top())
            {
                pq.pop();
                pq.push(x);
            }
        }
    }

    int add(int val)
    {
        if(pq.size() < k)
        {
            pq.push(val);
        }
        else if(val > pq.top())
        {
            pq.pop();
            pq.push(val);
        }

        return pq.top();
    }
};