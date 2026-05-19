#include <iostream>
#include <vector>

using namespace std;

// start from the first element
// find the min in this range
// insert into the first spot 
// continue till the end
void selection_sort_dry_run(vector<int> &vec) {
    int n = vec.size();
    cout << "start" << endl;
    for(int i=0; i<n-1; i++) {        
        int idx_swap = i;
        for(int j=i+1; j<n; j++) {
            cout << "\tchecking element: " << vec[j] << endl;
            if(vec[idx_swap] > vec[j]) {
                idx_swap = j;
            }
        }
        cout << "min_ele: " << vec[idx_swap] << endl;
        cout << "\tswapping min: " << vec[idx_swap] << " with " << vec[i] << endl;
        swap(vec[i], vec[idx_swap]);
        cout << "inner loop done" << endl;
    }
    cout << "end" << endl;
    return;
}

void selection_sort(vector<int> &vec) {
    int n = vec.size();
    
    for(int i=0; i<n-1; i++) {

        int idx_swap = i;

        for(int j=i+1; j<n; j++) {
            if(vec[i] > vec[j]) {
                idx_swap = j;
            }
        }

        if (idx_swap != i) {
            swap(vec[i], vec[idx_swap]);
        }
         
    }    
    return;
}

int main() {
    vector<int> v = {3,4,2,1,0,-5};
    selection_sort_dry_run(v);
    // selection_sort(v);

    for(auto x: v) {
        cout << x << endl;
    }
    return 0;
}

/*
selection sort is put min from 0..n-1
but we can just find min, we need to swap
so we need min_idx

    for 0..n-1
        find min-idx
            swap

    for i=0..n-1
        min-idx = i
        for j=i+1..n-1
            if min-idx < j
                min-idx - j
        swap

*/