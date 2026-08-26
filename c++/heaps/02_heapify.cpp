#include <iostream>
#include <vector>
using namespace std;



/*
after changing a heap key value
    either we can rerun the heap algo
    or
    we can check in which direction the invalidation occurs
    and then update up or down

-----------
    newValue < oldValue
        ↓
    could only violate parent relationship
        ↓
    heapify UP

-----------
    newValue > oldValue
        ↓
    could only violate child relationship
        ↓
    heapify DOWN

-----------

        change key
            ↓
      old vs new value
        /         \
    smaller       larger
       ↓             ↓
   violation       violation
    with parent     with children
       ↓             ↓
      UP             DOWN

*/

void updateHeapKey(vector<int> &nums, int ind, int val) {

    // assume nums is a min heap
    if(val < nums[ind]) {
        nums[ind] = val;
        //heapify_up(nums, ind);

        // smaller value needs to bubble up
    }
    else {
        nums[ind] = val;
        //heapify_down(nums, ind);

        // larger value needs to bubble down
    }
    
}
 

void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

int main() {
    vector<int> nums = {1, 4, 5, 5, 7, 6};
    int idx = 5, val = 2;

    print(nums);
    updateHeapKey(nums, idx, val);
    print(nums);

    nums = {2, 4, 3, 6, 5, 7, 8, 7}; 
    idx = 0, val = 7;

    print(nums);
    updateHeapKey(nums, idx, val);
    print(nums);

    // int x = 5;
    // while(true){
    //     cout << x << endl;
    //     if(x==0) break;
    //     x = x/2;
    // }

    return 0;
}