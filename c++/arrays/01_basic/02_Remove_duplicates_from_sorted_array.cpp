#include <iostream>
#include <vector>

using namespace std;

// 0(n), 0(n)
int remove_duplicates_extra_space(vector<int>& nums) {
    
    // brute force
    // 2 for loops and extra space
    int n = nums.size();
    if(n <= 1) return n;

    vector<int> temp;

    temp.push_back(nums[0]);

    for(int i=1; i<n; i++) {
        if(nums[i] != nums[i-1]){
            temp.push_back(nums[i]);
        }
    }

    for(int i=0; i<temp.size(); i++){
        nums[i] = temp[i];
    }

    return temp.size();
}

// we dont overwrite the first element
// only the second and further unique elements

// nums[0] is already in place
// we can compare j to i, since i=0
// 1,1,1,1,2,2,2,2,2,3
int remove_duplicates(vector<int>& vec) {

    if (vec.empty()) return 0;
    
    int n = vec.size();        
    int i=0;  // writer, i = index of the last unique element in the output.
    int j=0;  // reader, scanner

    for(j=1; j<n; j++){        
        if(vec[j] != vec[i]){            
            vec[++i] = vec[j];            
        }        
    }
    return i+1;
}

void print_no_dups(vector<int>& vec, int k) {
    cout << "[ " << endl;
    for(int i=0; i<k; i++) {
        cout << vec[i] << " ";
    }
    cout << "]" << endl;
}

int main() {
    vector<int> v = {0,0,3,3,5,6};

    // int k = remove_duplicates_extra_space(v);
    int k = remove_duplicates(v);

    print_no_dups(v, k);
    return 0;
}

/*
2 pointer
    reader, writer

    for each reader
        if reader != reader+1
            nums[writer++] = nums[reader]

*/