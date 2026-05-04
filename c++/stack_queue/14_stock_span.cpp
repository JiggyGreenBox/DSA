#include <iostream>
#include <vector>
#include <climits>
#include <stack>
using namespace std;

void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

vector<int> stockSpan(vector<int> arr) {
    int n = arr.size();
    vector<int> ans(n, 0);
    stack<int> st;
    // keep the stack a decreasing stack
    for(int i=0; i<n; i++) {
        
        while(!st.empty() && arr[i] >= arr[st.top()]) {
            st.pop();
        }
        ans[i] = (st.empty()) ? (i+1) : (i - st.top());
        st.push(i);
    }
    return ans;
}

int main() {
    print(stockSpan({120, 100, 60, 80, 90, 110, 115}));
    print(stockSpan({15, 13, 12, 14, 16, 20}));    
    return 0;
}