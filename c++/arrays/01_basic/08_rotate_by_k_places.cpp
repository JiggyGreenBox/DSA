#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void right_rotate_k_places(vector<int>& vec, int k) {
    int n = vec.size();
    vector<int> temp(n);
    k = k % n;
    for(int i=0; i<n; i++) {        
        temp[(i+k) % n] = vec[i];
    }
    vec = temp;
}

void left_rotate_k_places(vector<int>& vec, int k) {
    int n = vec.size();
    vector<int> temp(n);
    k = k % n;
    for(int i=0; i<n; i++) {        
        temp[i] = vec[(i+k) % n];
    }
    vec = temp;
}

void left(vector<int>& vec, int k) {
    int n = vec.size();
    k %= n;
    reverse(vec.begin(), vec.begin() + k);
    reverse(vec.begin() + k, vec.end());
    reverse(vec.begin(), vec.end());;
}

void printVec(vector<int> vec) {
    cout << "[ ";
    for(auto x: vec) cout << x << " ";    
    cout << "]" << endl;
}

int main() {
    vector<int> vec = {1,2,3,4,5,6};
    int k = 2;

    printVec(vec);    
    // right_rotate_k_places(vec,k);
    // left_rotate_k_places(vec, k);
    left(vec, k);
    printVec(vec);    
    return 0;
}

/*
Interview takeaway

This is one of those algorithms worth memorizing. The observation to 
remember is:

Right rotate by k: Reverse whole → first k → remaining.
Left rotate by k: Reverse first k → remaining → whole.

right rotate by k=2
    1,2,3,4 | 5,6
    5,6 | 1 2 3 4
        rotate all
        rotate first 2, rotate remaining        

left rotate by k=2
    1 2 | 3 4 5 6
    3 4 5 6 | 1 2
        rotate k
        rotate remaining
        rotate all



ok so we can remember by saying if k is the starting, first rotate k, 
then remaining then all. if k is at the end first rotate all, then k, 
then remaining, k is at the starting for left, k is at the ending for 
right
*/