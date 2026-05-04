#include <iostream>
#include <vector>
using namespace std;

/*
--------------------------------------------
Input: [1, 2, 3]
Output:
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1

1
    2 3     no swap
    3 2     1 swap

2           1 swap
    1 3     no swap
    3 1     1 swap

3           1 swap
    1 2     no swap
    2 1     1 swap
--------------------------------------------
Input: [1, 2, 3, 4]
Output:
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1

1               choose 1, proceed
    2 3 4           choose 2, proceed
    2 4 3
    3 2 4           choose 3, proceed
    3 4 2
    4 2 3           choose 4, proceed
    4 3 2

2
    1 3 4    
    1 4 3
    3 1 4
    3 4 1
    4 1 3
    4 3 1

3 
    1 2 4
    1 4 2
    2 1 4
    2 4 1
    4 1 2
    4 2 1

    what is proceed?
    reduce the search space

    choose 0
        swap 0,1
        choose(..)
        swap 1 0

        choose 1
            swap 1,2
            choose(..)
            swap 2 1

            choose 2
                swap 2,3
                choose(..)
                swap 3 2

                choose 3
                    swap 3,4
                    choose(..)
                    swap 4 3

this becomes n! code

  1        2      3
 2  3     1 3    1 2
3    2   3   1  2   1
                
*/



void permute(vector<int> nums, int start=0){
    int n = nums.size();
    // base case
    if(start == n){
        for(int x:nums) cout << x << " ";
        cout << endl;
        return;
    }

    for(int i=start; i<n; i++){
        swap(nums[start], nums[i]); // swap every number with num[start]
        permute(nums, start+1);
        swap(nums[start], nums[i]); // unchoose
    }
}

void permute_w_print(vector<int> nums, int start=0){
    string tabs(1 * start, '\t');
    string line(100, '-');
    cout << tabs << "start val: " << start << endl;
    int n = nums.size();
    // base case
    if(start == n){
        cout << tabs << "perm: [ ";
        for(int x:nums) cout <<  x << " ";
        cout << " ]" << endl;
        cout << line << endl;
        return;
    }

    for(int i=start; i<n; i++){
        cout << tabs << "swapping " << nums[start] << " with " << nums[i] << endl;
        swap(nums[start], nums[i]); // swap every number with num[start]


        cout << tabs << "[ ";
        for(int x:nums) cout <<  x << " ";
        cout << " ]" << endl;


        cout << tabs << "permute from idx " << start << " to " << (start+1) << endl;
        permute_w_print(nums, start+1);
        swap(nums[start], nums[i]); // unchoose
        cout << tabs << "unswapping " << nums[start] << " with " << nums[i] << endl;
    }
}

void solve_perms(vector<int>& nums, int start, vector<vector<int>>& ans){
    int n = nums.size();
    if(start == n){
        ans.push_back(nums);
    }

    for(int i=start; i<n; i++){
        swap(nums[start], nums[i]);
        solve_perms(nums, start+1, ans);
        swap(nums[start], nums[i]);
    }
}

/*
The approach of passing the result vector by reference
(vector<vector<int>>& result) is the standard, most efficient way to collect
results in recursive backtracking functions in C++. It avoids the
overhead of creating and merging large temporary vectors on the
stack, which is what your initial design intended to do with the
return value.
*/
vector<vector<int>> return_perms(vector<int>& nums){
    vector<vector<int>> ans;
    solve_perms(nums, 0, ans);
    return ans;
}

int main(){
    // vector<int> v = {1,2,3};
    vector<int> v = {1,2,3,4};
    // permute_w_print(v);

    vector<vector<int>> ans = return_perms(v);
    for(const auto& vec : ans){
        cout << "[ ";
        for(auto x : vec){
            cout << x << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}