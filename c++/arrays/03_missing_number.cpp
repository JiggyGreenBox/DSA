#include <iostream>
#include <vector>

using namespace std;

void printVec(vector<int>& vec){
    for(auto x: vec){
        cout << x << " ";
    }
    cout << endl;
    
}

int missingNumber(vector<int>& nums) {
    // brute force
    // loop thru range
    // then loop thru array
    // flag missing
    // o(n^2)
    printVec(nums);

    int n = nums.size();
    for(int i=0; i<=n; i++) {
        cout << "i: " <<i << endl;
        bool found = false;
        for(int j=0; j<n; j++) {
            cout <<"\t"<< j;
            
            if(nums[j] == i){
                cout << "found" << nums[j] << i << endl;
                cout << "break" << i << endl;
                found = true;
                break;
            }
            
        }
        if(!found){
            cout << "return i;" << i << endl;
            return i;
        }
        cout << endl;
    }
    return -1;
}

int missing_num_w_sum(vector<int>& nums){
    int n = nums.size();
    int sum = n*(n+1)/2;
    for(auto num : nums){
        sum -= num;
    }
    return sum;
}

int missing_num_w_xor(vector<int>& nums) {
    int n = nums.size();
    int xor_sum = 0;
    for(int i=0; i<=n; i++) { // note the equal sign
        xor_sum = xor_sum^i;
    }
    cout << xor_sum << endl;

    for(int i=0; i<n; i++) {
        xor_sum = xor_sum^nums[i];
    }
    return xor_sum;
}

/*
int ans = 0;

for(int i=0; i<=n; i++)
    ans ^= i;

for(int x : nums)
    ans ^= x;

return ans;
*/
int missing_num_w_xor_2(vector<int>& nums) {

    int n = nums.size();
    int xor_all = n;// include 'n' upfront

    // OR
    // int ans = n;

    for(int i=0; i<n; i++) {
        xor_all ^= i ^ nums[i];

        // ans ^= i;
        // ans ^= nums[i];
    }    
    // return ans;
    return xor_all;
}

int main() {
    vector<int> v = {0, 2, 3, 1, 4};
    // missingNumber(v);
    cout << missing_num_w_sum(v) << endl;

    v = {0, 1, 2, 4, 5, 6};

    cout << missing_num_w_xor_2(v) << endl;
    return 0;
}