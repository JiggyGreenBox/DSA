#include <iostream>
#include <vector>

using namespace std;

// 0(n), 0(n)
int remove_duplicates_extra_space(vector<int>& nums) {
    
    // brute force
    // 2 for loops and extra space
    int n = nums.size();
    if(n <= 1) return n;

    vector<int> temp;

    temp.push_back(nums[0]);

    for(int i=1; i<n; i++) {
        if(nums[i] != nums[i-1]){
            temp.push_back(nums[i]);
        }
    }

    for(int i=0; i<temp.size(); i++){
        nums[i] = temp[i];
    }

    return temp.size();
}

// we dont overwrite the first element
// only the second and further unique elements

// nums[0] is already in place
// we can compare j to i, since i=0
// 1,1,1,1,2,2,2,2,2,3

int remove_duplicates(vector<int>& vec) {
    int n = vec.size();
    // 2 pointers
    // 1st for insertion of non-zero, aka storage / slow
    // 2nd is processed pointer / fast
    int i=0;  // slow
    int j=0;  // fast

    for(j=1; j<n; j++){
        // cout << vec[i] << endl;
        // cout << vec[j] << endl;
        if(vec[j] != vec[i]){
            cout << "not equal at i: " << i;
            cout << " j: " << j;
            cout << " vec[i]: ";
            cout << vec[i] << " vec[j]: ";
            cout << vec[j] << endl;
            vec[++i] = vec[j];
            // cout << vec[i] << endl;
            cout << "\tnow vec[i] is: " << vec[i] << endl;
        }
        else{
            cout << "elemen are equal for i,j at " << i << "," << j << endl;
        }
    }
    return i+1;
}

void print_no_dups(vector<int>& vec, int k) {
    cout << "[ " << endl;
    for(int i=0; i<k; i++) {
        cout << vec[i] << " ";
    }
    cout << "]" << endl;
}

int main() {
    vector<int> v = {0,0,3,3,5,6};

    // int k = remove_duplicates_extra_space(v);
    int k = remove_duplicates(v);

    print_no_dups(v, k);
    return 0;
}