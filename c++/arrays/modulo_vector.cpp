#include <iostream>
#include <vector>
using namespace std;

void left_rotate_by_k_places(vector<int>& nums, int k){

    int n = nums.size();
    k = k%n;

    vector<int> aux = nums;

    // copy backwards
    for(int i=0; i<n; i++){
        nums[i] = aux[(i+k)%n];
    }    
}

// copy forwards
void right_rotate_by_k_places(vector<int>& nums, int k){

    int n = nums.size();
    k = k%n;

    vector<int> aux = nums;

    for(int i=0; i<n; i++){
        nums[(i+k)%n] = aux[i];        
    }    
}

void printVec(vector<int>& nums){
    for(auto num : nums) cout << num << " ";    
    cout << endl;
}

int main(){

    int a = 5;
    
    // move everything ahead by 1
    // right rotate
    for(int i=0; i<a; i++){
        // cout << a%i << endl; // math error
        cout << i%a;
        cout << " | ";
        cout << (i+1) % a << endl;
    }

    cout << endl;
    cout << endl;

    // move everything behind by 1
    // left rotate
    for(int i=0; i<a; i++){
        // cout << a%i << endl; // math error
        cout << (i-1) % a;
        cout << " | ";
        cout << i%a << endl;
        
    }


    vector<int> v = {1,2,3,4,5};
    printVec(v);
    left_rotate_by_k_places(v, 2);
    right_rotate_by_k_places(v, 2);
    printVec(v);


    return 0;
}