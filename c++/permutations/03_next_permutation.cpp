#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(const vector<int>& v) {
    cout << "[ ";
    for(auto x : v) cout << x << " ";
    cout << "]";
    cout << endl;
    cout << endl;
}

void print(const vector<int>& v, int start, int end) {
    cout << "[ ";
    for(int i=start; i<=end; i++){
         cout << v[i] << " ";
    }
    cout << "]";
    cout << endl;
    cout << endl;
}

void my_reverse(vector<int>& v, int start, int end){
    while(start<end){
        int temp = v[start];
        v[start] = v[end];
        v[end] = temp;
        start++;
        end--;
    }
}

void next_permutation(vector<int>& v) {
    
    int n = v.size();

    // 1. find pivot
    int piv_idx = -1;
    for(int i=n-2; i>=0; i--){
        if(v[i] < v[i+1]){
            piv_idx = i;
            break;
        }
    }

    // gpt reccomendation
    if(piv_idx == -1){
        cout << "no pivot found, reversing entire array ";
        my_reverse(v, 0, n-1);
        return;
    }
    
    cout << "pivot: ";
    cout << v[piv_idx] << endl;

    // gpt reccomendation
    // -------------------------------------------------------------
    // int swap_idx;
    // int swap_val=v[piv_idx+1];

    // for(int i=piv_idx; i<n; i++){
    //     // less than max, more than pivot
    //     if(v[i] > v[piv_idx] && v[i] < swap_val){
    //         swap_val = v[i];
    //         swap_idx = i;
    //     }
    // }
    // cout << "swap: ";
    // cout << v[swap_idx] << endl;

    // cout << "suffix before swap: ";
    // print(v, piv_idx+1, n-1);

    // cout << "swapping " << v[piv_idx]
    //      << " with "    << v[swap_idx]
    //      << endl;

    // swap(v[piv_idx], v[swap_idx]);
    // -------------------------------------------------------------

    /*
    Step 2: Why is this suffix sorted (descending)?
    suffix = [5, 4, 3]
    Because if it wasn’t, we would’ve found a smaller i earlier.
    every element to the right of the pivot is greater
    but also they are increasing
    if not the pivot would be at that element
    */
    
    for (int i = n-1; i > piv_idx; i--) {
        if (v[i] > v[piv_idx]) {

            cout << "swap: ";
            cout << v[i] << endl;

            swap(v[i], v[piv_idx]);            
            break;
        }
    }

    my_reverse(v, piv_idx+1, n-1);
} 

// why bool return
bool next_permutation_cannonical(vector<int>& v){
    int n =- v.size();
    if(n<=1) return false;

    // we had a for n..0 with a if and break
    // that should be a while loop
    int i = n - 2;
    while(i>=0 && v[i]>=v[i+1]) i--;

    // If no pivot, it's the last permutation
    if(i<0){
        reverse(v.begin(), v.end()); // input is reverse sorted
        return false; // means it was the last permutation
    }

    // the suffix is sorted in descending order
    // every element to the right is greater
    // and we looked for L<R
    int j=n-1;
    while(v[j] <= v[i]) j--;   // [1,2,5,4,3,0] -> 3

    swap(v[i], v[j]); // pivot and successor

    // Reverse the suffix (to make it smallest possible)
    reverse(v.begin() + i + 1, v.end());

    return true; // means we found the next permutation
}

int main(){
    vector<int> v = {1, 2, 5, 4, 3};    

    print(v);

    next_permutation(v);

    print(v);
}