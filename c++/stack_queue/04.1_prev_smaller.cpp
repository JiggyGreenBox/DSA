#include <iostream>
#include <stack>
#include <vector>

using namespace std;
void print(const vector<int> v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}
vector<int> prevSmaller1(const vector<int>& arr) {
    // brute force
    int n = arr.size();
    vector<int> ans(n, -1);
    for(int i=n-1; i>=0; i--) {
        for(int j=i-1; j>=0; j--) {
            if(arr[j] < arr[i]){
                ans[i] = arr[j];
                break;
            } 
        }
    }
    return ans;
}

vector<int> prevSmaller2(const vector<int>& arr) {
    // O(n)
    // forward pass

    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for(int i=0; i<n; i++) {
        // stack top is not allowed to be smaller than new
        // pop till valid
        while(!st.empty() && arr[i] <= arr[st.top()]) {
            st.pop();
        }

        // top is smaller than new
        // or the stack is empty
        if(!st.empty()) {
            ans[i] = arr[st.top()];
        }

        // store index for future processing
        st.push(i);
    }
    return ans;
}


vector<int> prevGreater(const vector<int>& arr) {
    // O(n)
    // forward pass
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for(int i=0; i<n; i++) {
        // stack top is not allowed to be greater than new
        // pop till valid
        while(!st.empty() && arr[i] >= arr[st.top()]) {
            st.pop();
        }

        // top greater than new
        // or the stack is empty
        if(!st.empty()) {
            ans[i] = arr[st.top()];
        }

        // store index for future processing
        st.push(i);
    }
    return ans;
}


vector<int> nextGreater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for(int i=0; i<n; i++) {
        // new element is larger than previous elements
        // so process and remove them from the stack
        while(!st.empty() && arr[i] > arr[st.top()]) {
            ans[st.top()] = arr[i];
            st.pop();
        }

        // store index for processing
        st.push(i);
    }
    return ans;
}


vector<int> nextSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for(int i=0; i<n; i++) {
        // new is strictly smaller so process previous elements
        // and remove previous elements from the stack
        while(!st.empty() && arr[i] < arr[st.top()]) {
            ans[st.top()] = arr[i];
            st.pop();
        }

        // push index for processing in the future
        st.push(i);
    }
    return ans;
}

int main() {
    // print(prevSmaller1({1, 6, 2}));
    // print(prevSmaller2({1, 6, 2}));    
    // print(prevSmaller1({1, 5, 0, 3, 4, 5}));
    // print(prevSmaller2({1, 5, 0, 3, 4, 5}));    

    // print(prevSmaller2({1,2,3,4,5}));
    // print(prevSmaller2({5,4,3,2,1}));
    // print(prevSmaller2({5,5,5}));

    print(prevGreater({5,4,3,2,1}));    
    print(prevGreater({1,2,3,4,5}));
    print(prevGreater({5,5,5}));



    // print(nextGreater({1,2,3,4,5}));
    // print(nextGreater({5,4,3,2,1}));
    // print(nextGreater({5,5,5}));


    // print(nextSmaller({1,2,3,4,5}));
    // print(nextSmaller({5,4,3,2,1}));
    // print(nextSmaller({5,5,5}));


    return  0;
}