#include <iostream>
#include <climits>
#include <stack>
#include <vector>
using namespace std;

void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

int sumSubarrayMins(const vector<int> &arr) {
    int ans = 0;

    // brute force
    // generate all subarrays and get the min
    int n = arr.size();
    for(int i=0; i<n; i++) {
        int min_ele = INT_MAX;
        for(int j=i; j<n; j++) {
            // if(arr[j] < min_ele) min_ele = arr[j];
            // if(min_ele != INT_MAX) ans += min_ele;
            min_ele = min(min_ele, arr[j]);
            ans += min_ele;
        }        
    }

    return ans;
}

// 2 pass
int sumSubarrayMins2(const vector<int> &arr) {
    // 2n pass
    stack<int> st;
    int n = arr.size();
    int sum=0;

    // int left[n] = {0};
    // int right[n] = {0};
    vector<int> left(n);
    vector<int> right(n);

    // L to R
    for(int i=0; i<n; i++) {
        while(!st.empty() && arr[st.top()] > arr[i]) {
            st.pop();
        }

        int prev_smaller = (st.empty()) ? -1 : st.top();
        left[i] = i - prev_smaller;

        st.push(i);
    }

    st = {};

    // R to L
    for(int i=n-1; i>=0; i--) {
        while(!st.empty() && arr[st.top()] >= arr[i]) {
            st.pop();
        }

        int prev_smaller = (st.empty()) ? n : st.top();
        right[i] = prev_smaller - i;
        
        st.push(i);
    }

    for(int i=0; i<n; i++) {
        sum += arr[i] * left[i] * right[i];
    }

    return sum;
}

// 1 pass
int sumSubarrayMins3(const vector<int> &arr) {

    int n = arr.size();
    stack<int> st;
    long long sum = 0;
    int mod = 1e9 + 7; // large prime number

    for(int i=0; i<n; i++) {

        int pop_idx = -1;

        // increasing stack only
        while(!st.empty() && arr[st.top()] > arr[i]) {
            pop_idx = st.top();
            st.pop();

            int prev_smaller = (st.empty()) ? -1 : st.top();

            int start   = pop_idx - prev_smaller;
            int end     = i - pop_idx;
            
            long long contribution = 1LL * arr[pop_idx] * start * end;
            sum = (sum + contribution) % mod;
        }

        st.push(i);
    }

    // process remaining stack elements
    while(!st.empty()) {
        int pop_idx = st.top();
        st.pop();

        int prev_smaller = (st.empty()) ? -1 : st.top();

        int start   = pop_idx - prev_smaller;
        int end     = n - pop_idx;

        long long contribution = 1LL * arr[pop_idx] * start * end;
        sum = (sum + contribution) % mod;        
    }
    
    return sum;
}

int main() {
    cout << sumSubarrayMins({3, 1, 2, 5}) << endl;
    cout << sumSubarrayMins2({3, 1, 2, 5}) << endl;
    cout << sumSubarrayMins3({3, 1, 2, 5}) << endl;
    cout << sumSubarrayMins({2, 3, 1}) << endl;
    cout << sumSubarrayMins2({2, 3, 1}) << endl;
    cout << sumSubarrayMins3({2, 3, 1}) << endl;
    return 0;
}

