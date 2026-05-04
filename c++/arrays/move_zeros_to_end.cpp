#include <iostream>
#include <vector>

using namespace std;

void move_zeros_to_end(vector<int>& nums){
    int i=0;
    int j=0;
    int n = nums.size();

    for(j=0; j<n; j++){
        if(nums[j] != 0){
            nums[i++] = nums[j];
        }
    }

    while(i<n){
        nums[i++] = 0;
    }
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