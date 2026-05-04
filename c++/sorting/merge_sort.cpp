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

void merge_dry_run(vector<int>& vec, int start, int mid, int end, int level) {

    string prefix = levelTab(level);
    cout << prefix << "before merge: " << printVecIdx(vec, start, end) << endl;
    // cout << "\t\tstart: "<< start << " mid: " << mid << " end: " << end << endl;

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
        // cout << x << endl;
        vec[y++] = x;        
    }    
    cout << prefix << "after merge: " << printVecIdx(vec, start, end) << endl;
}

void merge_sort_dry_run(vector<int>& vec, int start, int end, int level) {

    if(start >= end) return;

    string prefix = levelTab(level);
    
    cout << prefix <<"[" << start << ".." << end << "]  "<<vec[start]<<".."<<vec[end] << endl;

    int mid = (start + end) / 2;
    // cout << "\tmid -> "<< mid << endl;

    merge_sort_dry_run(vec, start, mid, level+1);
    merge_sort_dry_run(vec, mid+1, end, level+1);
    merge_dry_run(vec, start, mid, end, level+1);



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

    printVec(v);

    merge_sort_dry_run(v, 0, v.size()-1, 0);
    // merge_sort(v, 0, v.size()-1);

    printVec(v);

    return 0;
}