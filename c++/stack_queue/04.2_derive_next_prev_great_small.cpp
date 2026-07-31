#include <iostream>
#include <vector>
#include "../common/printer.h"
#include <stack>
using namespace std;

/*
------------------

3 decisions

    1. L-R / R-L

    2. increasing / decreasing stack

    3. prev ans  / next ans
    
------------------

stack is storage
    discard useless

    while(top is useless)
        pop


------------------
use 1 template and fill accordingly
------------------

for (...) {

    while (!st.empty() && useless(st.top(), nums[i]))
        st.pop();

    ans[i] = st.empty() ? -1 : st.top();

    st.push(nums[i]);
}

------------------


Notice something elegant:

    Greater always uses <=.
    Smaller always uses >=.
    Only the scan direction changes.
*/

// =====================================================================
/*
nge
    [1, 2, 3, 4, 5]
    [2, 3, 4, 5,-1]

    [ 5, 4, 3, 2, 1]
    [-1,-1,-1,-1,-1]

    R-L
        because next
    a new larger element makes the prev useless
        while top > curr
            pop
    
*/
vector<int> nge(const vector<int> &nums) {
    stack<int> st;
    int n = nums.size();
    vector<int> ans(n);
    for(int i=n-1; i>=0; i--) {
        while(!st.empty() && nums[i] >= nums[st.top()])
            st.pop();

        ans[i] = st.empty() ? -1 : nums[st.top()];

        st.push(i);
    }
    return ans;
}

/*
nse
    [1, 2, 3, 4, 5]
    [-1,-1,-1,-1,-1]

    [ 5, 4, 3, 2, 1]
    [ 4, 3, 2, 1,-1]

    [ 5, 5, 5]
    [-1,-1,-1]

    next so R-L

    same or larger elements are useless for the future

*/
vector<int> nse(const vector<int> &nums) {
    stack<int> st;
    int n = nums.size();
    vector<int> ans(n);

    for(int i=n-1; i>=0; i--) {
        while(!st.empty() && nums[i] <= nums[st.top()])
            st.pop();

        ans[i] = st.empty() ? -1 : nums[st.top()];

        st.push(i);
    }
    return ans;
}

/*
pge
    [1, 2, 3, 4, 5]
    [-1,-1,-1,-1,-1]

    [ 5, 4, 3, 2, 1]
    [-1, 5, 4, 3, 2]

    [ 5, 5, 5]
    [-1,-1,-1]

    prev so L-R

    smaller or equal elements are useless for the future

*/
vector<int> pge(const vector<int> &nums) {
    stack<int> st;
    int n = nums.size();
    vector<int> ans(n);

    for(int i=0; i<n; i++) {
        while(!st.empty() && nums[st.top()] <= nums[i])
            st.pop();

        ans[i] = st.empty() ? -1 : nums[st.top()];

        st.push(i);
    }
    return ans;
}

/*
pse
    [ 1, 2, 3, 4, 5]
    [-1, 1, 2, 3, 4]

    [ 5, 4, 3, 2, 1]
    [-1,-1,-1,-1,-1]

    [ 5, 5, 5]
    [-1,-1,-1]

    prev so L-R

    greater or equal elements are useless for the future

*/
vector<int> pse(const vector<int> &nums) {
    stack<int> st;
    int n = nums.size();
    vector<int> ans(n);

    for(int i=0; i<n; i++) {
        while(!st.empty() && nums[st.top()] >= nums[i])
            st.pop();

        ans[i] = st.empty() ? -1 : nums[st.top()];

        st.push(i);
    }
    return ans;
}

int main() {
    // print(nge({1,2,3,4,5}));
    // print(nge({5,4,3,2,1}));
    // print(nge({5,5,5,5,5}));

    // print(nse({1,2,3,4,5}));
    // // print(nse({5,4,3,2,1}));
    // print(nse({5,5,5,5,5}));

    // print(pge({1,2,3,4,5}));
    // print(pge({5,4,3,2,1}));
    // print(pge({5,5,5,5,5}));

    print(pse({1,2,3,4,5}));
    print(pse({5,4,3,2,1}));
    print(pse({5,5,5,5,5}));
    return 0;
}