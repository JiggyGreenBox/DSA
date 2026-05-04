#include <iostream>
#include <vector>

using namespace std;

void printVec(vector<int>& vec) {
    cout << "[ ";
    for(auto x: vec){
        cout << x << " ";
    }
    cout << "]" << endl;

    cout << endl;
}



void merge_dry_run(vector<int> &vec, vector<int> &aux, int start, int mid, int end) {

    // copy vec into aux, as ground truth
    for(int k=start; k<=end; k++) {
        aux[k] = vec[k];
    }

    cout << "vec: ";
    printVec(vec);
    cout << "aux: ";
    printVec(aux);

    int i = start; // L start
    int j = mid+1; // R start
    int k = start; // vec start

    // iterate thru first half
    while(i<=mid && j<=end) {
        if(aux[i] <= aux[j]) {
            vec[k++] = aux[i++];            
        }
        else{
            vec[k++] = aux[j++];            
        }
    }

    // left over elements because at least 1 R was copied to L
    while(i<=mid){        
        vec[k++] = aux[i++];
    } 
    
    cout << "aux: ";
    printVec(aux);
    cout << "vec: ";
    printVec(vec);
    
}

// each merge op calls itself twice
// function calls = 2n-1
// merges = n-1

// bottom up
// function calls = 0
// merges = n-1
void bottom_up_merge_sort_dry_run(vector<int> &vec) {
    int n = vec.size();

    if(n<=1) return;

    // use an aux array
    vector<int> aux(n);

    // merge L R arrays from the bottom up (size 1 and upwards)
    // size is the length of L/R array
    // start at 1 for multiplier
    // 1,2,4,8..n
    for(int size=1; size<n; size *=2){
        cout << "size: " << size << endl;        

        // for 1, merge these indexes
        // [0..1] [2..3] [3..4]

        // for 2
        // [0..3] [4..7] [8..11]

        // for 4
        // [0..7] [8..11] [12..15]


        for(int start=0; start < n-size; start += 2*size) {                    
            // L: [start..mid] merges with R: [mid+1..end]

            // (start + size - 1) has to be less than (n)
            // or mid will be out of bounds
            // start + size < n
            // start < n - size
            int mid = start + size - 1; 
            int end = min(start + 2*size -1, n-1);

            cout << "start: " << start << " mid: " << mid << " end: "<< end << endl;

            merge_dry_run(vec, aux, start, mid, end);
        }
    }

}


int main() {
    // bottom_up_merge_sort
    vector<int> v = {7,6,5,4,3,2,1};
    // vector<int> v = {4,3,2,1};

    printVec(v);

    bottom_up_merge_sort_dry_run(v);

    printVec(v);
}