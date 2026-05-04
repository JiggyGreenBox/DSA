#include <iostream>
#include <vector>

using namespace std;

void printVec(vector<int> &v) {
    cout << "[ ";
    for(auto x : v) cout << x << " ";    
    cout << "]" << endl;
}

std::string printVecIdx(vector<int>& vec, int start, int end) {
    std::string multiplied_tab = "";
    multiplied_tab += "[ ";

    for(int i=start; i<=end; i++){
        multiplied_tab +=  std::to_string(vec[i]) + " ";
    }    
    multiplied_tab += "]";
    return multiplied_tab;
}

int naive_partition_and_swap_dry_run(vector<int> &vec, int start, int end) {
    int part = vec[end];
    int idx = -1;
    vector<int> smaller;    
    vector<int> larger;

    for(int i=start; i<end; i++){
        if(vec[i] >= part) {
            larger.push_back(vec[i]);
        }
        else{
            smaller.push_back(vec[i]);
        }
    }

    int k = start;
    for(auto x : smaller){
        vec[k++] = x;
    }

    idx = k;
    vec[k++] = part;
    

    for(auto x : larger){
        vec[k++] = x;
    }
    return idx;
}


// i, less than pivot accumulator
// j, processed elements
int lomuto_partion(vector<int> &vec, int start, int end) {

    int i = start-1; // no elements found less than pivot, YET    
    int pivot = vec[end];

    for(int j=start; j<end; j++){ // skip last element
        if(vec[j] <= pivot){
            // cout << "i: " << i << endl;
            // add to i
            i++; 

            // cout << "before swap(vec[i], vec[j]) : swap(" << vec[i] << "," << vec[j]<< ")"<< endl;
            swap(vec[i], vec[j]);
            // cout << "after  swap(vec[i], vec[j]) : swap(" << vec[i] << "," << vec[j]<< ")"<< endl;
            
        }        
    }
    // cout << "swap(vec[i+1], vec[end]); : swap(" << vec[i+1] << "," << vec[end]<< ")"<< endl;
    swap(vec[i+1], vec[end]);
    return i+1;
}


int lomuto_practic(vector<int> &vec, int start, int end) {
    cout << "start: " << start;
    cout << " end: " << end << endl;
    cout << "\t" << printVecIdx(vec, start, end) << endl;

    int i = start - 1;  // accumulates <= elements
    int j = start;      // proccessed elements
    int pivot = vec[end];

    for(int j=start; j<end; j++) { // skip the pivot, last element
        // skip larger elements
        // look for insertion point
        if(vec[j] <= pivot) {
            i++;
            cout << "\tswap: " << i <<","<< j<< endl;
            swap(vec[i], vec[j]);
        }
    }
    cout << "\tswap(vec[i+1], vec[end]); : swap(" << vec[i+1] << "," << vec[end]<< ")"<< endl;
    swap(vec[i+1], vec[end]); // pivot placed

    cout << "\t" << printVecIdx(vec, start, end) << endl;
    return i+1;
}

// no mid like merge sort
// think of mid to be auto calculated
void quick_sort_dry_run(vector<int> &vec, int start, int end) {

    cout << "start: " << start;
    cout << " end: " << end << endl;    

    if(start >= end) return;

    // partition and swap
    // return partition index
    // int part_idx = lomuto_partion(vec, start, end);
    int part_idx = lomuto_practic(vec, start, end);    
    printVec(vec);

    // quick_sort L of partition
    // quick_sort R of partition
    quick_sort_dry_run(vec, start, part_idx-1); // we dont include the part_idx
    quick_sort_dry_run(vec, part_idx+1, end);
}

int main() {
    vector<int> v = {9,8,7,6,5,4,3,2,1, 0};
    v = {1,5,4,2,3};

    printVec(v);

    quick_sort_dry_run(v, 0, v.size()-1);

    printVec(v);

    return 0;
}


// i, less than pivot accumulator
// j, processed elements
// [0,1,2,3,4,5]
// p=5
// i=-1
// i,j=0
// i,j=1
// i,j=2
// i,j=3
// i,j=4


// [5,2,1,0,4,3]
// p=3
// i=-1
// i=0,j=1
// [2,5,1,0,4,3]
// i=1,j=2
// [2,1,5,0,4,3]
// i=2,j=3
// [2,1,0,5,4,3]

// i=2,j=5
// [2,1,0,3,4,5]