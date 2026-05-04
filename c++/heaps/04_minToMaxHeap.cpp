#include <iostream>
#include <vector>
using namespace std;


void heapify_up(vector<int>& nums, int i) {
    while(i > 0) {
        int parent = (i-1)/2;

        if(nums[parent] >= nums[i]) break;

        swap(nums[parent], nums[i]);
        i = parent;
    }
}

void heapify_down(vector<int>& nums, int i) {
    int n = nums.size();
    while(true) {
        int left = 2*i+1;
        int right = 2*i+2;
        int largest = i;

        if(left < n && nums[left] > nums[largest]) {
            largest = left;
        }

        if(right < n && nums[right] > nums[largest]) {
            largest = right;
        }

        if(largest == i) break;
        swap(nums[largest], nums[i]);
        i = largest;
    }
}

vector<int> minToMaxHeap_nlogn(vector<int> nums) {
    vector<int> max_heap;
    int n = nums.size();
    for(auto x : nums){
        max_heap.push_back(x);
        heapify_up(max_heap, max_heap.size()-1);
    }
    return max_heap;
}

vector<int> minToMaxHeap(vector<int> nums) {
    vector<int> max_heap = nums;
    int n = nums.size();
    for(int i=n/2-1; i>=0; i--) {
        heapify_down(max_heap, i);
    }
    return max_heap;
}

int main() {
    vector<int> nums = {10, 20, 30, 21, 23};
    nums = {-5, -4, -3, -2, -1};
    auto x = minToMaxHeap(nums);
    int u = 5;
    return 0;
}