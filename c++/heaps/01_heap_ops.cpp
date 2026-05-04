#include <iostream>
#include <vector>
using namespace std;

// node is too small
// push up
void heapify_up(vector<int>& nums, int i) {
    while(i > 0) {
        int parent = (i-1) / 2;

        if(nums[parent] <= nums[i]) break;

        swap(nums[i], nums[parent]);
        i = parent;
    }
}

// node too big 
// push down
void heapify_down(vector<int>& nums, int i) {
    int n = nums.size();
    while(true) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;

        if(left < n && nums[left] < nums[smallest]) {
            smallest = left;
        }
        if(right < n && nums[right] < nums[smallest]) {
            smallest = right;
        }

        if(smallest == i) break;

        swap(nums[i], nums[smallest]);
        i = smallest;
    }
}


void push(vector<int>& heap, int val) {
    heap.push_back(val);
    heapify_up(heap, heap.size()-1);
}

int pop(vector<int>& heap) {
    int min_val = heap[0];

    heap[0] = heap.back();
    heap.pop_back();

    heapify_down(heap, 0);

    return min_val;
}


void build_heap_nlogn(vector<int>& nums) {
    int n = nums.size();
    for(int i=0; i<n; i++) {
        heapify_up(nums, i);
    }
}

void build_heap_n(vector<int>& nums) {
    int n = nums.size();

    for(int i = n/2 - 1; i >= 0; i--) {
        heapify_down(nums, i);
    }
}

int main() {
    return 0;
}