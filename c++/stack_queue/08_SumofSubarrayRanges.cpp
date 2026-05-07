#include <bits/stdc++.h>

using namespace std;

long long subArrayRanges1(const vector<int> &nums) {
    // brute force
    // get all sub arrays and subtract max and min
    long long sum=0;
    int n = nums.size();

    for(int i=0; i<n; i++) {
        int min_ele = INT_MAX;
        int max_ele = INT_MIN;
        for(int j=i; j<n; j++) {
            min_ele = min(min_ele, nums[j]);
            max_ele = max(max_ele, nums[j]);
            sum += max_ele - min_ele;
        }        
    }
    return sum;
}

vector<int> find_nge(const vector<int> &nums) {
    int n = nums.size();
    stack<int> st;
    vector<int> ans(n, n);
    for(int i=0; i<n; i++) {
        // [1,2,3,4,5]
        // [2,3,4,5,-1]
        // [5,4,3,2,1]
        // [-1,-1,-1,-1,-1]
        // pop when we find a BOSS, something larger
        while(!st.empty() && nums[i] >= nums[st.top()]){
            // ans[st.top()] = nums[i];
            ans[st.top()] = i;
            st.pop();
        }        

        // store idx for processing
        st.push(i);
    }
    return ans;
}
vector<int> find_nse(const vector<int> &nums) {
    int n = nums.size();
    stack<int> st;
    vector<int> ans(n, n);
    for(int i=0; i<n; i++) {
        // [1,2,3,4,5]
        // [-1,-1,-1,-1,-1]
        // [5,4,3,2,1]
        // [4,3,2,1,-1]
        while(!st.empty() && nums[i] <= nums[st.top()]) {
            // ans[st.top()] = nums[i];
            ans[st.top()] = i;
            st.pop();
        }

        // store idx for processing
        st.push(i);
    }
    return ans;
}
vector<int> find_pge(const vector<int> &nums) {
    // O(n)
    // forward pass
    int n = nums.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for(int i=0; i<n; i++) {
        // [1,2,3,4,5]
        // [-1,-1,-1,-1,-1]
        // [5,4,3,2,1]
        // [-1,5,4,3,2]
        // stack top is not allowed to be greater than new
        // pop till valid
        while(!st.empty() && nums[i] >= nums[st.top()]) {
            st.pop();
        }

        // top greater than new
        // or the stack is empty
        if(!st.empty()) {
            // ans[i] = nums[st.top()];
            ans[i] = st.top();
        }

        // store index for future processing
        st.push(i);
    }
    return ans;
}
vector<int> find_pse(const vector<int> &nums) {
    // O(n)
    // forward pass

    int n = nums.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for(int i=0; i<n; i++) {
        // [1,2,3,4,5]
        // [-1,1,2,3,4]
        // [5,4,3,2,1]
        // [-1,-1,-1,-1,-1]
        // stack top is not allowed to be smaller than new
        // pop till valid
        while(!st.empty() && nums[i] <= nums[st.top()]) {
            st.pop();
        }

        // top is smaller than new
        // or the stack is empty
        if(!st.empty()) {
            // ans[i] = nums[st.top()];
            ans[i] = st.top();
        }

        // store index for future processing
        st.push(i);
    }
    return ans;
}

long long subArrayRanges2(const vector<int> &nums) {
    // O(n)
    // get min element and max element of a subarray
    int n = nums.size();
    vector<int> nge = find_nge(nums);
    vector<int> pge = find_pge(nums);

    vector<int> nse = find_nse(nums);
    vector<int> pse = find_pse(nums);
    long long sum = 0;

    for(int i=0; i<n; i++) {
        // Count of first type of subarrays
        int left = i - pge[i];
        
        // Count of second type of subarrays
        int right = nge[i] - i;
        long long contribution = 1LL * nums[i] * left * right;
        sum += contribution;
    }
    for(int i=0; i<n; i++) {
        // Count of first type of subarrays
        int left = i - pse[i];
        
        // Count of second type of subarrays
        int right = nse[i] - i;
        long long contribution = 1LL * nums[i] * left * right;
        sum -= contribution;
    }
    return sum;
}

/*
for Sum of Subarray Ranges i got the brute force, now in plain english im trying to reason about the problem. 

    for each subarray sum += max - min

        (sum of subarray max) - (sum of subarray min)



        sum of subarray max
            for each idx, find left SAs where idx is max, and same for right
            then sum += arr[idx] * left1(idx) * right1(idx)

        
        sum of subarray min
            for each idx, find left SAs where idx is min, and same for right
            then sum -= arr[idx] * left2(idx) * right2(idx)
        


        left1 = pge, right1 = ngee
        left2 = pse, right2 = nsee
*/


int main() {
    cout << subArrayRanges1({1, 2, 3}) << endl;         // 4
    cout << subArrayRanges1({1, 3, 3}) << endl;         // 4
    cout << subArrayRanges1({4, -2, -3, 4, 1}) << endl; // 59

    cout << subArrayRanges2({1, 2, 3}) << endl;         // 4
    cout << subArrayRanges2({1, 3, 3}) << endl;         // 7
    cout << subArrayRanges2({4, -2, -3, 4, 1}) << endl; // 67
    
    
    return 0;
}
