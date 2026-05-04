#include <iostream>
#include <vector>

using namespace std;

std::string levelTab(int level) {
    std::string multiplied_tab = "";
    for (int i = 0; i < level; ++i) {
        multiplied_tab += "\t";
    }
    return multiplied_tab;
}

void printVec(vector<int>& vec) {
    cout << "[ ";
    for(auto x: vec){
        cout << x << " ";
    }
    cout << "]" << endl;

    cout << endl;
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

void merge_aux_dry_run(vector<int>& vec, vector<int>& aux, int start, int mid, int end, int level) {

    cout << "s:" << start<< " m:" << mid << " e:" << end << endl;

    string prefix = levelTab(level);
    cout << prefix << "before merge: " << printVecIdx(vec, start, end) << endl;
    
    // copy  vec to aux
    for(int i=start; i<= end; i++) {
        aux[i] = vec[i];
    }
    cout << "vec";
    printVec(vec);
    cout << "aux";
    printVec(aux);

    // i start of 1st array
    // j start of 2nd array
    int i = start;
    int j = mid+1;

    // sizes of both arrays
    int n = mid - start + 1;
    // int m = end - (mid + 1) + 1;
    int m = end - mid;

    int k = start; // counter for aux
    
    while(i<=mid && j<=end){
        if(vec[i] <= vec[j]){
            aux[k++] = vec[i++];
        }
        else{            
            aux[k++] = vec[j++]; 
        }
    }

    while(i<=mid){
        aux[k++] = vec[i++];
    }
    // this isnt needed! 
    // while(j<=end){
    //     aux[k++] = vec[j++];
    // }

    // In merge sort, leftover right-half elements stay in place, 
    // but leftover left-half elements must be copied back 
    // if the right half ever contributed.
    // slots were stolen

    // In merge sort, after copying the current range into an auxiliary array, 
    // elements are merged back into the main array. 
    // If the left half is exhausted first (all its elements are ≤ all right-half elements),
    // the remaining right-half elements are already in place in the main array and need no copying.
    // But if the right half contributes at least once (some right element < some left element),
    // then part of the left half’s original slots in the main array may have been overwritten. 
    // In that case, any leftover left-half elements must be explicitly copied back from the auxiliary array, 
    // while right-half leftovers never require copying.

    // if already sorted first half exhausts first
    // if even 1 swap is required
    // there are remainders in the first half and never in the second
    




    // overwrite back
    // copy  vec to aux
    for(int i=start; i<= end; i++) {
        vec[i] = aux[i];
    }   
    cout << "aux";
    printVec(aux);
    cout << "vec";
    printVec(vec);
    cout << prefix << "after merge: " << printVecIdx(vec, start, end) << endl;
}

void merge_sort_aux_dry_run(vector<int>& vec, vector<int>& aux, int start, int end, int level) {

    if(start >= end) return;

    string prefix = levelTab(level);
    
    cout << prefix <<"[" << start << ".." << end << "]  "<<vec[start]<<".."<<vec[end] << endl;

    int mid = (start + end) / 2;
    // cout << "\tmid -> "<< mid << endl;

    merge_sort_aux_dry_run(vec, aux, start, mid, level+1);
    merge_sort_aux_dry_run(vec, aux, mid+1, end, level+1);
    merge_aux_dry_run(vec, aux, start, mid, end, level+1);



    return;
}



void merge(vector<int>& vec, int start, int mid, int end) {    
    int i = start;
    int j = mid+1;

    int n = mid - start + 1;
    // int m = end - (mid + 1) + 1;
    int m = end - mid;

    vector<int> temp;
    while(i<=mid && j<=end){
        if(vec[i] <= vec[j]){
            temp.push_back(vec[i]);
            i++;
        }
        else{
            temp.push_back(vec[j]);
            j++;
        }
    }

    while(i<=mid){
        temp.push_back(vec[i]);
        i++;
    }
    while(j<=end){
        temp.push_back(vec[j]);
        j++;
    }
    
    // overwrite back
    int y = start;
    for(auto x: temp){        
        vec[y++] = x;        
    }        
}


void merge_sort(vector<int>& vec, int start, int end) {

    if(start >= end) return;    

    int mid = (start + end) / 2;    

    merge_sort(vec, start, mid);
    merge_sort(vec, mid+1, end);
    merge(vec, start, mid, end);
    return;
}





int main() {
    // vector<int> v = {9,8,7,6,5,4,3,2,1};
    // vector<int> v = {2,1}; // no splits, straight to merge
    // vector<int> v = {3,2,1};  // 1 split 2 merges
    // vector<int> v = {4,3,2,1};   // 2 split, 3 merges
    // vector<int> v = {5,4,3,2,1};   // 3 split, 4 merges
    vector<int> v = {6,5,4,3,2,1};   // 4 split, 5 merges

    vector<int> aux(v.size());

    printVec(v);

    merge_sort_aux_dry_run(v, aux, 0, v.size()-1, 0);
    // merge_sort_aux(v, 0, v.size()-1);

    printVec(v);

    return 0;
}