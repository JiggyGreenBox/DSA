#include <iostream>
#include <vector>
using namespace std;


bool isHeap(const vector<int>& nums) {
    int n = nums.size();

    for(int i=0; i<n; i++) {
        int left = 2*i + 1;
        int right = 2*i + 2;

        cout << "i: " << nums[i];
        cout << " left: " << nums[left];
        cout << " right: " << nums[right] << endl;

        if(left >=n && right >=n) break;

        if(left < n && nums[left] < nums[i]) return false;
        if(right < n && nums[right] < nums[i]) return false;
    }
    return true;
}

int main() {
    if(isHeap({10, 20, 30, 25, 15})) cout << "true" << endl;
    else cout << "false" << endl;

    if(isHeap({10, 20, 30, 21, 23})) cout << "true" << endl;
    else cout << "false" << endl;

    // if(isHeap({})) cout << "true";
    // else cout << "false";
    return 0;
}