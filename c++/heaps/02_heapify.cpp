#include <iostream>
#include <vector>
using namespace std;



void heapify(vector<int> &nums, int ind, int val) {


    
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
    heapify(nums, idx, val);
    print(nums);

    nums = {2, 4, 3, 6, 5, 7, 8, 7}; 
    idx = 0, val = 7;

    print(nums);
    heapify(nums, idx, val);
    print(nums);

    // int x = 5;
    // while(true){
    //     cout << x << endl;
    //     if(x==0) break;
    //     x = x/2;
    // }

    return 0;
}