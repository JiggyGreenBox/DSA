#include <iostream>
#include <vector>

using namespace std;

vector<int> union_sorted_arrays(vector<int>& v1, vector<int>& v2) {
    int n = v1.size();
    int m = v2.size();

    vector<int> ans;

    int i=0;
    int j=0;

    while(i<n && j<m) {
        // skip duplicates second element onwards        
        while(i>0 && v1[i] == v1[i-1]) {
            cout << "v1[i] duplicate: "<< v1[i] << endl;
            ++i;
        }
        while(j>0 && v2[j] == v2[j-1]){
            cout << "v2[j] duplicate: "<< v2[j] << endl;
            ++j;
        }
        

        // entire arrays can be duplicate
        // so check here
        if(i>=n || j>=m) {
            cout << "out of bounds for 1 of the 2 arrays" << endl;
            break;
        };

        // if equal insert any, increment both pointers
        if(v1[i] == v2[j]){
            cout << "v1[i] == v2[j]: "<< v1[i] << endl;
            ans.push_back(v1[i]);
            cout << "ans.push_back(v1[i]): "<< v1[i] << endl;
            ++i;
            ++j;
        }
        // v1 is lesser
        else if(v1[i] < v2[j]){
            cout << "v1[i] < v2[j]: "<< v1[i] << " < " << v2[j] << endl;
            cout << "ans.push_back(v1[i]): "<< v1[i] << endl;
            ans.push_back(v1[i]);
            ++i;            
        }
        // v2 is lesser
        else {
            cout << "v1[i] > v2[j]: "<< v1[i] << " > " << v2[j] << endl;
            cout << "ans.push_back(v2[j]): "<< v2[j] << endl;
            ans.push_back(v2[j]);            
            ++j;
        }
    }
    
    cout << "first while loop ended" << endl;
    while(i<n){
        cout << "remaining in v1" << endl;
        // skip duplicates second element onwards        
        while(i>0 && v1[i] == v1[i-1]) {
            cout << "v1[i] duplicate: "<< v1[i] << endl;
            ++i;
        }
        if(i>=n) break;
        // duplicate check here?
        ans.push_back(v1[i++]);
    }
    while(j<m){
        cout << "remaining in v2" << endl;
        // skip duplicates second element onwards        
        while(j>0 && v2[j] == v2[j-1]) {
            cout << "v2[j] duplicate: "<< v2[j] << endl;
            ++j;
        }
        if(j>=m) break;
        // duplicate check here?
        ans.push_back(v2[j++]);
    }
    return ans;
}


vector<int> union_sorted_arrays_2(vector<int>& v1, vector<int>& v2) {
    int i=0, j=0;
    int n = v1.size();
    int m = v2.size();

    vector<int> ans;

    while(i<n && j<m){
        if(v1[i] < v2[j]) { cout << "i: " <<i << endl; i++; }
        else if(v1[i] > v2[j]) { cout << "j: " << j << endl; j++;  }
        else{
            cout << v1[i] << endl;
            ans.push_back(v1[i]);
            i++;j++;
        }
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