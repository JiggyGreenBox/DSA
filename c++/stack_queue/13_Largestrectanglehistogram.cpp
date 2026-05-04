#include <iostream>
#include <vector>
#include <stack>
using namespace std;


/*
max histogram rectangle
heights = [2, 1, 5, 6, 2, 3]
    largest rectangle 

    for any rectangle we calculate the height * width
    height will be min of all bars

    so for any bar left boundary and right boundary will be elements lesser than cur

    we can keep track by having a stack
    [1,2,3,4,1]
        for bar 2 -> left 1 is invalid and right 1 is invalid, rest is a valid combo

    st = [1]
    st = [1,2]
    st = [1,2,3,4]
    1 > 4
        4 = pop
        height = 4-3
        len = idx[4] - idx[3] + 1
*/

int largestRectangleArea1(const vector<int> &heights) {
    int n = heights.size();
    stack<int> st;
    int area = 0;

    vector<int> pse(n, -1);
    vector<int> nse(n, n);

    // find pse
    for(int i=0; i<n; i++) {
        // [1,2,3,4,5]
        // [-1,1,2,3,4]

        // [5,4,3,2,1]
        // [-1,-1,-1,-1,-1]
        while(!st.empty() && heights[i] <= heights[st.top()]) {
            st.pop();
        }
        if(!st.empty()){
            // pse[i] = heights[st.top()];      
            pse[i] = st.top();
        }
        st.push(i);
    }

    st = {};

    // find nse
    for(int i=0; i<n; i++) {
        // [1,2,3,4,5]
        // [-1,-1,-1,-1,-1]

        // [5,4,3,2,1]
        // [4,3,2,1,-1]
        while(!st.empty() && heights[i] < heights[st.top()]) {            
            // nse[st.top()] = heights[i];               
            nse[st.top()] = i;
            st.pop();
        }        
        st.push(i);
    }
    // area = height * len
    // len = nse - pse - 1
        // -1 because the len is bounded between them
        // 1,7,5
        // 0,1,2
        // 2-0-1 = 1 for [7]

        // h   = [1,7,5]
        // pse = [-1,0,0]   |-1
        // nse = [3,2,3]    |n

        // 1 -> 3 - (-1) -1 = 3 * 1
        // 7 -> 2 - 0 - 1   = 1 * 7
        // 5 -> 3 - 0 - 1   = 2 * 5
    for(int i=0; i<n; i++) {
        // the boundaries are non inclusive
        int height = heights[i];
        int width = nse[i] - pse[i] - 1;
        area = max(area, height*width);        
    }

    return area;
}


// like other stack problems
// here we find our answer is bounded between 2 boundaries
// the largest rect for [7,5,9] is 5-5-5 = 15
// we use -1 and n as the boundaries if the entire array is valid
// for any bar, we can extend left or right as long as these bars
// are >= to the curr bar
// when we find a bar < curr bar we cant extend further
// if we have previous smaller and next smaller
// we have our boundaries
// since we dont include these b's len = right-left-1
//      h   = [1,5,1]
//      pse = [-1,0,-1]
//      nse = [3,2,3]
//      w   = [3,1,3]
int largestRectangleArea2(const vector<int> &heights) {
    int n = heights.size();
    stack<int> st;
    int area = 0;

    // h = [1,7,5,9]
    // s = [1]

    for(int i=0; i<n; i++) {

        // only store increasing heights
        // we a decrease is found, time to calculate
        // calculate for st.top
        while(!st.empty() && heights[i] <= heights[st.top()]) {
            // r, l, and mid
            // r is incoming
            // mid is top
            // access left after pop

            int right = i;
            int mid = st.top();
            st.pop();

            int left = (st.empty()) ? -1 : st.top();

            int len = right - left - 1;

            area = max(area, len * heights[mid]);
        }

        st.push(i); // store and process idx later
    }

    // if we only have increasing elements
    // we will not have an empty stack
    // [1,2,3]
    
    while(!st.empty()) {
        int mid = st.top();
        st.pop();
        int left = (st.empty()) ? -1 : st.top();
        int len = n - left - 1;
        area = max(area, len * heights[mid]);        
    }    

    return area;
}


int largestRectangleArea_cannonical(const vector<int> &heights) {
    int n = heights.size();
    stack<int> st;
    int max_area = 0;

    // iterate till n
    // to clean up the stack
    for(int i=0; i<=n; i++) {
        int curr_height = (i==n) ? 0 : heights[i];

        while(!st.empty() && curr_height < heights[st.top()]) {
            int mid = st.top();
            st.pop();

            int left = (st.empty()) ? -1 : st.top();
            int width = i - left - 1;

            max_area = max(max_area, heights[mid] * width);
        }
        st.push(i);
    }
    return max_area;
}

int main() {
    cout << largestRectangleArea1({2, 1, 5, 6, 2, 3}) << endl;
    cout << largestRectangleArea2({2, 1, 5, 6, 2, 3}) << endl;
    cout << largestRectangleArea_cannonical({2, 1, 5, 6, 2, 3}) << endl;
    
    cout << largestRectangleArea1({3, 5, 1, 7, 5, 9}) << endl;
    cout << largestRectangleArea2({3, 5, 1, 7, 5, 9}) << endl;    
    cout << largestRectangleArea_cannonical({3, 5, 1, 7, 5, 9}) << endl;
         

    // cout << largestRectangleArea({1,2,3,4,5}) << endl;
    // cout << largestRectangleArea({5,4,3,2,1}) << endl;
    return 0;
}