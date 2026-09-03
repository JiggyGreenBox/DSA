#include <iostream>
#include <vector>

using namespace std;

vector<int> union_sorted_arrays(vector<int>& v1, vector<int>& v2) {

    int n = v1.size();
    int m = v2.size();

    int i=0, j=0;

    vector<int> ans;

    while(i<n && j<m) {
        if(v1[i] < v2[j]) {
            if(!ans.size() || ans.back() != v1[i]) {
                ans.push_back(v1[i]);
            }
            i++;
        }
        else if(v1[i] > v2[j]) {
            if(!ans.size() || ans.back() != v2[j]) {
                ans.push_back(v2[j]);
            }
            j++;
        }
        else {
            if(!ans.size() || ans.back() != v1[i]) {
                ans.push_back(v1[i]);
            }
            i++;
            j++;
        }
    }
    
    
    while(i<n){
        if(!ans.size() || ans.back() != v1[i]) {
            ans.push_back(v1[i]);
        }
        i++;
    }
    while(j<m){
        if(!ans.size() || ans.back() != v2[j]) {
            ans.push_back(v2[j]);
        }
        j++;
    }
    return ans;
}


vector<int> union_sorted_arrays_2(vector<int>& v1, vector<int>& v2) {
    int n = v1.size();
    int m = v2.size();

    int i=0, j=0;

    vector<int> ans;

    while(i<n && j<m) {
        if(v1[i] <= v2[j]) {
            if(!ans.size() || ans.back() != v1[i]) {
                ans.push_back(v1[i]);
            }
            i++;
        }
        else {
            if(!ans.size() || ans.back() != v2[j]) {
                ans.push_back(v2[j]);
            }
            j++;
        }
    }
    
    
    while(i<n){
        if(!ans.size() || ans.back() != v1[i]) {
            ans.push_back(v1[i]);
        }
        i++;
    }
    while(j<m){
        if(!ans.size() || ans.back() != v2[j]) {
            ans.push_back(v2[j]);
        }
        j++;
    }
    return ans;
}

int main() {
    vector<int> v1 = {1,1,1,1,1,1,7};
    vector<int> v2 = {6,6,6,7,8,8,8};

    vector<int> ans = union_sorted_arrays_2(v1, v2);
    for(auto x: ans){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

/*
if arrays are not sorted we use a set
O(n+m)log(n+m)

but since arrays are sorted we can just check ans.back
O(m+n) T
O(1)   S
*/