#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void no_dup_perms(vector<int>& nums, int start=0) {
    int n = nums.size();
    if(start == n) {
        for(int x:nums) cout << x << " ";
        cout << endl;
    }
    unordered_set<int> used; // per depth
    for(int i=start; i<n; i++) {
        if(used.count(nums[i])) continue; // skip the swap, already used

        // else, store value
        used.insert(nums[i]);
        swap(nums[start], nums[i]);
        no_dup_perms(nums, start+1);
        swap(nums[start], nums[i]);
    }
}

int main(){
    vector<int> v = {1, 1, 2};
    // permute_w_print(v);

    // unordered_set<int> used;// not global, only per depth

    no_dup_perms(v);
    /*
    no duplicate check
        1 1 2 
        1 2 1 
        1 1 2 
        1 2 1 
        2 1 1 
        2 1 1 
        
    with check
        1 1 2 
        1 2 1 
        2 1 1 
    */

    return 0;
}