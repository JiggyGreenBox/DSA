#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void print(const vector<int>& res) {
    cout << "[ ";
    for(int n : res) {
        cout << n << " ";
    }
    cout << "]\n";
}

vector<int> nextLargerElement1(const vector<int> arr) {
    // brute force
    int n = arr.size();
    vector<int> ans(n,-1);
    for(int i=0; i<n; i++){
        bool found = false;
        for(int j=i+1; j<n; j++){
            if(arr[j] > arr[i]){
                ans[i] = arr[j];
                found = true;
                break;
            }
        }

        // if we didnt break
        // try from the start till ith
        if(!found){
            for(int k=0; k<i; k++){
                if(arr[k] > arr[i]){
                    ans[i] = arr[k];
                    break;
                }
            }
        }
        
    }
    return ans;
}

/*
[3, 10, 4, 2, 1, 2, 6, 1, 7, 2, 9]
[10,-1, 6, 6, 2, 6, 7, 7, 9, 9,10]
*/

vector<int> nextLargerElement2(const vector<int> arr) {
    int n = arr.size();
    vector<int> ans(n,-1);

    for(int i=0; i<2*n; i++){
        for(int j=i+1; j<2*n; j++){
            if(arr[j%n] > arr[i%n]){
                ans[i%n] = arr[j%n];                
                break;
            }
        }
    }
    return ans;
}

vector<int> nextLargerElement3(const vector<int> arr) {
    int n = arr.size();
    vector<int> ans(n,-1);
    stack<int> st;

    for(int i=0; i<2*n; i++){
        int idx = i%n;
        while(!st.empty() && arr[idx] > arr[st.top()]) {
            ans[st.top()] = arr[idx];
            st.pop();
        }

        if(i<n){
            st.push(idx);
        }        
    }
    return ans;
}

vector<int> nextLargerElement4(const vector<int> arr) {
    int n = arr.size();
    vector<int> res(n,-1);
    stack<int> st;

    // backward
    for(int i=2*n-1; i>=0; i--) {
        int idx = i%n;
        int curr = arr[idx];
        while(!st.empty() && curr >= st.top()) {
            st.pop();
        }

        if(i<n && !st.empty()) {
            res[idx] = st.top();
        }            
        st.push(curr);
    }
    return res;
}


int main() {
    print(nextLargerElement1({3, 10, 4, 2, 1, 2, 6, 1, 7, 2, 9}));
    print(nextLargerElement2({3, 10, 4, 2, 1, 2, 6, 1, 7, 2, 9}));
    print(nextLargerElement3({3, 10, 4, 2, 1, 2, 6, 1, 7, 2, 9}));
    print(nextLargerElement4({3, 10, 4, 2, 1, 2, 6, 1, 7, 2, 9}));
    return 0;
}