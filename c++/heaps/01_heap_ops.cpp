#include <iostream>
#include <vector>
using namespace std;


// given a idx, compare upwards
// this is useful if we start at last internal node
// because all leaf nodes are already heaps
void heapify_up(vector<int>& nums, int i) {
    while(i > 0) {
        int parent = (i-1) / 2;

        if(nums[parent] <= nums[i]) break;

        swap(nums[i], nums[parent]);
        i = parent;
    }
}

// we have put a value at the top of the heap
// we need to push it down to the correct position
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


/*
logic for push and pop 
is determined by vector
easy to push back for push

and for pop we dont want to copy all backwards
rather we overwrite first with last
    and heapify down
*/

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

// Build heap from a given Array
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

/*
1. for a min heap
    parent is lesser than children

    2
    1 3

    need to move 1 up
        heapify_up

2. heapify_up()
        get parent 
        compare
            if ok break                                                     
        swap                                                                
        check next level
        
3. heapify_down
     1
    3 5

    pop 1
    now what?

    take last element and put it at top

    and push it down

    heapify_down
        find left and right child
        find smallest
        swap if required
            not required break
        i = smallest

pop
    min is arr[0]
    pop back
    move last first
    heapify_down(0)

push
    push_back    
    heapify_up(n-1)


PUSH → UP
POP  → DOWN

Build O(nlog)
    check each and heapify up for each

BUILD O(n):
    leaves already heaps
    start at n/2 - 1
    move backwards
    heapify DOWN

Why O(n)?
    Most nodes are near leaves
    and therefore move only a small distance.
*/