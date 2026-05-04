#include <iostream>
#include <vector>
using namespace std;


// Problem: Count Even Numbers in a Range

// You are given an array arr of n integers and q queries.
// Each query gives two indices L and R (0-based, inclusive).
// For each query, you need to output the number of even numbers in the subarray arr[L..R].

// Array = [2, 7, 4, 9, 12]

// Query (0,2) → subarray [2,7,4] → evens = 2.
// Query (1,4) → subarray [7,4,9,12] → evens = 2.
// Query (2,4) → subarray [4,9,12] → evens = 2.


vector<int> build_prefix_even(vector<int>& v){
    int n = v.size();

    vector<int> prefix_even(n); // hold even numbers here

    int even_count = 0;

    for(int i=0; i<n; i++) {        
        // even
        if(v[i] % 2 == 0) {
            even_count++;
        }
        prefix_even[i] = even_count;
    }

    // print
    cout << "[ ";
    for(auto x : prefix_even) cout << x << " ";
    cout << "]" << endl;

    return prefix_even;
}

int main() {
    vector<int> v = {2, 7, 4, 9, 12};

    vector<int> prefix_even = build_prefix_even(v);

    // queries
    vector<vector<int>> queries = {{0,2}, {1,4}, {2,4}}; // 2, 2, 2

    
    for(auto query  : queries){
        int L = query[0];
        int R = query[1];

        int even_count = prefix_even[R] - (L>0 ? prefix_even[L-1] : 0);
        cout << "even count: " << even_count << endl;
    }
    

    return 0;
}