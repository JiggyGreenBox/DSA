#include <iostream>
#include <vector>
using namespace std;

void heapify_down(vector<int>& nums, int i, int size) {    
    while(true) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int largest = i;

        if(left < size && nums[left] > nums[largest]) {
            largest = left;
        }
        if(right < size && nums[right] > nums[largest]) {
            largest = right;
        }
        if(largest == i) break;
        swap(nums[largest], nums[i]);
        i = largest;
    }
}

void heapSort(vector<int>&nums) {
    int n = nums.size();
    
    // 1. build max heap
    for(int i=n/2-1; i>=0; i--) {
        heapify_down(nums, i, n);
    }

    // 2. extract elements
    for(int i=n-1; i>0; i--) { // loop goes till i==1
        swap(nums[0], nums[i]);
        heapify_down(nums, 0, i); // children stop before i
    }
}

void print(const vector<int>& v) {
    cout  << "[ ";
    for(auto i : v) cout << i << " ";
    cout  << "]\n";
}

int main() {
    vector<int> nums = {7, 4, 1, 5, 3};
    heapSort(nums);
    print(nums);
    return 0;
}

/*
buildHeap(nums);

for (int i = n - 1; i > 0; i--)
{
    swap(nums[0], nums[i]);     // largest goes to its final position
    heapifyDown(nums, i, 0);    // restore heap in the remaining unsorted part
}

TC
    buildHeap(nums);                 // O(n)

    for (int i = n - 1; i > 0; i--)
    {
        swap(nums[0], nums[i]);      // O(1)
        heapifyDown(nums, i, 0);     // O(log i)
    }
    n time we have log i
        so its less than nlog


    n + nlogn
*/