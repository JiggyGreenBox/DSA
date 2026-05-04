#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int trap1(const vector<int> &height) {
    // 3n pass
    int n = height.size();

    vector<int> left(n, 0);
    vector<int> right(n, 0);
    int left_max = -1;
    int right_max = -1;
    for(int i=0; i<n; i++) {
        left_max = max(left_max, height[i]);
        left[i] = left_max;
    }
    
    for(int i=n-1; i>=0; i--) {
        right_max = max(right_max, height[i]);
        right[i] = right_max;
    }

    int sum = 0;
    for(int i=0; i<n; i++) {
        sum += max(min(left[i], right[i]) - height[i], 0);
    }
    return sum;
}

int trap2(const vector<int> &height) {
    int n = height.size();
    int l = 0, r = n-1;    
    int left_max = 0, right_max = 0;

    int sum = 0;

    while(l<r) {
        left_max    = max(left_max, height[l]);
        right_max   = max(right_max, height[r]);

        if(height[l] <= height[r]) {
            sum += min(left_max, right_max) - height[l];
            l++;
        }
        else{
            sum += min(left_max, right_max) - height[r];
            r--;
        }
    }
    return sum;
}
// use a stack here
/*
instead of using 2 pointer, which calculates bar by bar
we use a stack
this calculates layer by layer
as in vertical layers by layers

[6,0,2,6]
consider layer [6,0,2] the layer is [2,0,2], water = 2
the second layer is [6,0,2,6] 
or another way to think about this is [4,0,0,4] water = 8

think of tracking left, mid and right
we need left > mid < right
    water is [height * width]
        height = min(left,right) - mid
        width = right - left - 1
*/
int trap3(const vector<int>& heights) {
    int n = heights.size();
    stack<int> st;
    int sum = 0;

    for(int i=0; i<n; i++) {
        while(!st.empty() && heights[i] > heights[st.top()]) {
            int mid = st.top();
            st.pop();

            if(st.empty()) break;

            int left = st.top();
            int width = i - left - 1;
            int height = min(heights[left], heights[i]) - heights[mid];

            sum += (width * height);            
        }
        st.push(i);
    }
    return sum;
}

int main() {
    // cout << trap1({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) << endl;
    // cout << trap2({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) << endl;
    // cout << trap1({4, 2, 0, 3, 2, 5}) << endl;
    // cout << trap2({4, 2, 0, 3, 2, 5}) << endl;
    cout << trap2({6,0,2,6}) << endl;
    cout << trap3({6,0,2,6}) << endl;
    return 0;
}
