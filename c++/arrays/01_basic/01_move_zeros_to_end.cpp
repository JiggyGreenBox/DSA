#include <iostream>
#include <vector>

using namespace std;

/*
Example 1:

    Input: nums = [0,1,0,3,12]
    Output: [1,3,12,0,0]
*/

void move_zeros_to_end(vector<int>& nums){
    int i=0;    
    int n = nums.size();

    for(int j=1; j<n; j++){
        if(nums[j] != nums[i]){
            nums[++i] = nums[j];
        }
    }

    while(i<n-1){
        nums[++i] = 0;
    }
    // return i+1; // i is last unique, so size is +1
}

void move_zeros_to_end_2(vector<int>& nums){
    int i=0;
    int j=0;
    int n = nums.size();

    for(j=0; j<n; j++){
        if(nums[j] != 0){
            // nums[i++] = nums[j];
            swap(nums[i++], nums[j]);
        }
    }
}

// which method is better
// 1 does an extra i < n loop
// 1 does a lot of writes
// 2 does lots swaps
// 1 is better if less zeros
// 2 is better is more zeros


// improved version
// dont swap the same element
void move_zeros_to_end_3(vector<int>& nums){
    int i=0;
    int j=0;
    int n = nums.size();

    for(j=0; j<n; j++){
        if(nums[j] != 0){
            if(i!=j){
                swap(nums[i], nums[j]);
            }            
            i++;
        }
    }
}

void print_vec(vector<int>& v){
    for(auto x:v) cout << x << " ";
    cout << endl;
}

int main() {

    vector<int> v = {0, 1, 4, 0, 5, 2};

    print_vec(v);

    move_zeros_to_end_2(v);

    print_vec(v);

    return 0;
}

/*
move zeros to end
2 pointer

    reader, writer
    i,j
    for each reader
        if reader != 0        
            nums[writer++] = reader
    for remaining readers
        nums[reader++] = 0
*/