#include <iostream>
#include <vector>


using namespace std;

void revert_k_places(vector<int>& vec, int k) {
    int n = vec.size();
    k = k % n; // normalize k > n

    for (int i = 0; i < n; i++) {        
        cout << (i - k + n) << endl;
        int newPos = (i - k + n) % n;
        cout << "vec["<<i<<"] : " << "vec[" <<newPos <<"]"<< endl;
    }
}



void left_rotate_1_place_mod(){}
void right_rotate_1_place_mod(){}

void left_rotate_1_place(){}
void right_rotate_1_place(){}

// shift everything right by k, 
// and wrap-around the last k elements to the end.
void right_rotate_k_places(vector<int>& vec, int k) {

    cout << "left_rotate_k_places" << endl;
    int n = vec.size();

    vector<int> ans = vec;
    
    if(k > n){
        cout << "k before modulo: " << k << endl;
        k = k % n;
        cout << "k after modulo: " << k << endl;
    }
    
    // add k to i and wrap around
    // i from the start
    for(int i=0; i<n; i++) {
        cout << "(i+k) % n: " << (i+k) % n << " : " << "i: " << i << endl;
        ans[(i+k) % n] = vec[i];
    }
    vec = ans;
}

// shift everything left by k, 
// and wrap-around the first k elements to the end.
void left_rotate_k_places(vector<int>& vec, int k) {
    cout << "right_rotate_k_places" << endl;

    int n = vec.size();
    vector<int> ans = vec;

    if(k > n){
        cout << "k before modulo: " << k << endl;
        k = k % n;
        cout << "k after modulo: " << k << endl;
    }

    // sub k from i and wrap around
    // i from the end
    for(int i=0; i<n; i++){
        // cout << i;    
        cout << "(i-k)+n % n: " << ((i-k)+n) % n << " : " << "i: " << i << endl;
        ans[((i-k)+n) % n] = vec[i];
    }

    vec = ans;
    // k = 2
    // 1, 2, 3, 4, 5, 6, 7, 8
    // 3, 4, 5, 6, 7, 8, 1, 2
    // 0 -> 6  n-k+i  8-2+0
    // 1 -> 7  n-k+i  8-2+1
    // 2 -> 0         8-2+2 = 8%8=0
    // 3 -> 1         8-2+3 = 9%8=1
    // 4 -> 2         8-2+4 = 10%8=2
    // 5 -> 3         8-2+5 = 11%8=3
    // 6 -> 4         8-2+6 = 12%8=4    

}

void printVec(vector<int> vec) {
    cout << "[ ";
    for(auto x: vec) {
        cout << x << " ";
    }
    cout << "]" << endl;
}

int main() {
    vector<int> vec = {1,2,3,4,5,6,7,8};
    int k = 2;

    printVec(vec);    
    right_rotate_k_places(vec,k);
    left_rotate_k_places(vec, k);
    printVec(vec);
    // left_rotate_k_places(vec, k);

    k = 1;    
    return 0;
}