#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void next_permutation(vector<int>& v) {
    // The next permutation is the smallest arrangement that is larger than the current one
    // 123
    // 132

    // 13542
    // we find the pivot:
    //      it is the first decreasing number from the right
    //      3 <- 5
    //      3 needs to be increased, so we need the next largest num on the right = 4
    // when we swap 3 and 4 we have increased the number
    // 14532
    // but this maybe larger, the actual smallest number is 14235,
    // after swapping we need to arrange the remaining nums in increasing order

    // also notice the edge case 
    //      where we at the last permutation
    //      5,4,3,2,1
    //      then we return the first permutation
    //      1,2,3,4,5
    //      in the while loop i will be -1
    //      so the reverse loop will return the first combination
    // 


    int n = v.size();
    if(n<=1) return;

    // 1. find first decrease from right to left
    int i=n-2;
    while (i>=0 && v[i] >= v[i+1]) --i;

    if (i >= 0) {
        // 2. find element greater than pivot
        int j = n-1;
        while (v[j] <= v[i]) --j;
        swap(v[i], v[j]);
    }

    // 3. reverse suffix
    reverse(v.begin()+i+1, v.end());
    
}

int main() {
    // vector<int> v = {1,3,5,4,2};
    vector<int> v = {5,4,3,2,1};
    next_permutation(v);

    for(auto x:v){ cout << x << " ";}
    return 0;
}