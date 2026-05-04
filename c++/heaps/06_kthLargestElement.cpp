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

int main() {
    cout << kthLargestElement_good({1, 2, 3, 4, 5}, 2) << endl;
    cout << kthLargestElement_better({1, 2, 3, 4, 5}, 2) << endl;
    return 0;
}