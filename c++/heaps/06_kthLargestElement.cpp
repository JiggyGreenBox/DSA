#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int kthLargestElement_mine(const vector<int>& nums, int k) {
    priority_queue<int> pq;
    for(auto x : nums) {
        pq.push(x);
    }

    for(int i=1; i<k; i++) {
        pq.pop();
    }
    return (pq.empty()) ? -1 : pq.top();
}

int kthLargestElement_good(const vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    int n = nums.size();
    for(int i=0; i<n; i++) {
        pq.push(nums[i]);
        if(pq.size() > k) {
            pq.pop();
        }
    }
    return pq.top();
}
// this is better because each insert opertion
// is log k
// if less than top
// avoid that logk operation
int kthLargestElement_better(const vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    int n = nums.size();
    // 1. pq of size k
    for(int i=0; i<k; i++) {
        pq.push(nums[i]);        
    }

    // 2. only insert a bigger value, than top
    for(int i=k; i<n; i++) {
        if(nums[i] > pq.top()){
            pq.pop();
            pq.push(nums[i]);
        }
    }
    return pq.top();
}

int kthLargestElement_best(const vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;

    for(auto x : nums) {

        if (pq.size() < k)
        {
            pq.push(x);
        }
        // replace only if larger
        else if (x > pq.top())
        {
            pq.pop();
            pq.push(x);
        }
    }
    return pq.top();
}

int main() {
    cout << kthLargestElement_good({1, 2, 3, 4, 5}, 2) << endl;
    cout << kthLargestElement_better({1, 2, 3, 4, 5}, 2) << endl;
    return 0;
}

/*
we can sort and find the kth largest

we can use a max heap then pop k-1 times
    build heap O(n)
    pop k-1 times klogn

    (n + klogn)

we can maintain a min heap of size k

    time  O(n log k)
    space O(k)

    [1,2,3,4,5,6,7,8,9] k=2

    h = [1]
    h = [1,2]
    h = [1,2,3] pop 1
    h = [2,3] pop 1

    h = [2,3,4] pop 1
    h = [3,4]
    h = [3,4,5]  pop 1

    we will be left wuth 8,9
    8 = pq.top
    which is our answer

    another case
    1,9,7,6, k=2
    h = [1,9]
        7 greater than top(1)?
            yes replace
    h = [7,9]
        6 greater than top(7)?
            no skip
    h = [7,9]
    ...
    

O(n log k)
O(k)
*/