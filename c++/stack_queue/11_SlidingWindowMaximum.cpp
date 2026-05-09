#include <iostream>
#include <deque>
#include <vector>
using namespace std;

void print(const deque<int>& dq) {
    cout << "[ ";
    for(auto x : dq) {
        cout << x << " ";
    }
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

    if(n==0 || k<= 0) return {};
    if(k>n) k= n;

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
deque<int> createMonoticQueue(const vector<int>& nums) {
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

int main() {
    print(maxSlidingWindow1({4, 0, -1, 3, 5, 3, 6, 8}, 3));
    print(maxSlidingWindow1({20, 25}, 2));

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

    print(maxSlidingWindow3({4, 0, -1, 3, 5, 3, 6, 8}, 3));
    print(maxSlidingWindow3({20, 25}, 2));
    

    // print(createDecreasingMonoticQueue({1,2,3,4,5,6}));
    // print(createDecreasingMonoticQueue({1,2,5,4,5,10}));
    // print(createDecreasingMonoticQueue({3,2,1}));

    return 0;
}