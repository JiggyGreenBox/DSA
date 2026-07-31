#include <iostream>
#include <deque>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

void print(const deque<int>& dq) {
    cout << "[ ";
    for(auto x : dq) {
        cout << x << " ";
    }
    cout << "]\n";
}

void print(stack<int> st) {
    vector<int> temp;    
    while(!st.empty()) {        
        temp.push_back(st.top());
        st.pop();        
    }
    reverse(temp.begin(), temp.end());
    

    cout << "[ ";
    for(int x : temp) cout << x << " ";
    cout << "]\n";
}

void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

vector<int> maxSlidingWindow1(const vector<int> &arr, int k) {
    int n = arr.size();    
    vector<int> ans(n-k+1, 0);    

    for(int i=0; i<n-k+1; i++) {
        // cout << "[ ";
        for(int j=i; j<i+k; j++) {
            // cout << arr[j] << ",";
            ans[i] = max(ans[i], arr[j]);
        }
        // cout << "], ";
    }

    return ans;
}

vector<int> maxSlidingWindow2(const vector<int> &arr, int k) {
    int n = arr.size();
    deque<int> dq;
    vector<int> ans;
    // decreasing monotonic deque
    // because max element will be at the front
    // then we pop front

    // expand till k

    // k to n
    //  ans.push_back dq.front
    //  dq.pop_front
    // while process new element
    // add new element

    for(int i=0; i<k; i++) {        
        while(!dq.empty() && arr[i] > dq.back()) {
            dq.pop_back();
        }
        dq.push_back(arr[i]);        
    }

    for(int i=k; i<n; i++) { 
        if(!dq.empty()) {
            ans.push_back(dq.front());
            dq.pop_front();
        }
        
        while(!dq.empty() && arr[i] > dq.back()) {
            dq.pop_back();
        }
        dq.push_back(arr[i]);        
    }

    // for the last element
    if(!dq.empty()) {
        ans.push_back(dq.front());
        dq.pop_front();
    }
    return ans;
}

vector<int> maxSlidingWindow3(const vector<int> &arr, int k) {
    int n = arr.size();

    if(n==0 || k<=0) return {};
    if(k>n) k = n;

    deque<int> dq;
    vector<int> ans;

    // use indices as we can easily pop based on window size
    for(int i=0; i<n; i++) {
        // remove before the window
        if(!dq.empty() && dq.front() == i-k) {
            dq.pop_front();
        }        

        // add to monotonic queue
        // monotonic decreasing queue
        // [10,7,5]
        while (!dq.empty() && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
        
        // add to answer
        // after the window is expanded we can add answers
        // for k=3
        // i must 2 or greater
        if(i >= k-1) {
            ans.push_back(arr[dq.front()]);
        }
    } 
    return ans;
}

// keep the order ascending
deque<int> createIncreasingMonoticQueue(const vector<int>& nums) {
    deque<int> dq;
    int n = nums.size();
    for(int i=0; i<n; i++) {
        while(!dq.empty() && nums[i] < dq.back()) {
            dq.pop_back();
        }
        dq.push_back(nums[i]);
    }
    return dq;
}

// keep the order decreasing
deque<int> createDecreasingMonoticQueue(const vector<int>& nums) {
    deque<int> dq;
    int n = nums.size();
    for(int i=0; i<n; i++) {
        while(!dq.empty() && nums[i] > dq.back()) {
            dq.pop_back();
        }
        dq.push_back(nums[i]);
    }
    return dq;
}

stack<int> createIncreasingStack(const vector<int>& nums) {
    stack<int> st;
    int n = nums.size();
    for(int i=0; i<n; i++) {
        while(!st.empty() && nums[i] < st.top()) {
            st.pop();
        }
        st.push(nums[i]);
    }
    return st;
}
stack<int> createDecreasingStack(const vector<int>& nums) {
    stack<int> st;
    int n = nums.size();
    for(int i=0; i<n; i++) {
        while(!st.empty() && nums[i] > st.top()) {
            st.pop();
        }
        st.push(nums[i]);
    }
    return st;
}

int main() {
    // print(maxSlidingWindow1({4, 0, -1, 3, 5, 3, 6, 8}, 3));
    // print(maxSlidingWindow1({20, 25}, 2));

    // 1,2,3,4,5,6,7
    // 3,4,5,6,7

    // [4, 0, -1, 3, 5, 3, 6, 8] 
    // [4, 0, -1] 4
    // [0, -1, 3] 3
    // [-1, 3, 5] 5
    // [3, 5, 3]  5
    // [5, 3, 6]  6
    // [3, 6, 8]  8



    // print(maxSlidingWindow2({4, 0, -1, 3, 5, 3, 6, 8}, 3));
    // print(maxSlidingWindow2({20, 25}, 2));

    // print(maxSlidingWindow3({4, 0, -1, 3, 5, 3, 6, 8}, 3));
    // print(maxSlidingWindow3({20, 25}, 2));
    

    

    print(createIncreasingMonoticQueue({1,2,3,4,5,6}));
    print(createIncreasingMonoticQueue({1,2,5,4,5,10}));
    print(createIncreasingMonoticQueue({3,2,1}));

    print(createIncreasingStack({1,2,3,4,5,6}));
    print(createIncreasingStack({1,2,5,4,5,10}));
    print(createIncreasingStack({3,2,1}));

    print(createDecreasingMonoticQueue({1,2,3,4,5,6}));
    print(createDecreasingMonoticQueue({1,2,5,4,5,10}));
    print(createDecreasingMonoticQueue({3,2,1}));

    print(createDecreasingStack({1,2,3,4,5,6}));
    print(createDecreasingStack({1,2,5,4,5,10}));
    print(createDecreasingStack({3,2,1}));    

    return 0;
}

/*
as seen from the helper code
    deque and stack can be used in similar fashion
        increasing / decreasing 

    [1,2,3,4,5,1,2], k=3

    push 1
    push 2 pop 1
    push 3 pop 2
        earlier smaller candidates dont matter
            [0,1,2,3,4,5]
                k=4
                [0,1,2,3] max is 3
                    [1,2] will never be needed
            
            [100,99,2,4] max is 100
                when we pop 100
                    99 is required
                        when we pop 99 the 2 is useless
                            because of the 4

    stack can keep the order but not flush from the start

*/

/*

push every num in dq

eject invalid
    [0,1,2,3,4,5] k=2
    dq = [0,1,2,3]
        at i=2, 0 is invalid
        at i=3, 1 is invalid
        i-k is invalid

store candidates
    100,99.. store

    1,2
        1 is useless
        pop

    if num > dq.back
        pop
    
add to answer
    dq has the max
        it is at the front
            next best are after that

    idx cant be less than the window size
        but valid for each after that
    idx >= k-1

    if(idx >= k-1)
        ans.push_back(nums[dq.front])



*/