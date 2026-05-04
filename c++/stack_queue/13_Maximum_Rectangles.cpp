#include <bits/stdc++.h>
using namespace std;

int get_row_area(const vector<int>& heights) {
    int area = 0;
    int n = heights.size();
    stack<int> st;
    for(int i=0; i<=n; i++) {
        int curr_height = (i==n) ? 0 : heights[i];
        while(!st.empty() && curr_height < heights[st.top()]) {
            int mid = st.top();
            st.pop();
            int left = (st.empty()) ? -1 : st.top();
            int width = i - left - 1;
            area = max(area, heights[mid] * width);
        }
        st.push(i);
    }
    return area;
}

int maximalAreaOfSubMatrixOfAll1(const vector<vector<int>> &matrix) {
    int max_area = 0;
    int n = matrix.size(), m = matrix[0].size();
    
    vector<int> heights(m, 0);

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(matrix[i][j] == 1) {
                heights[j] += 1;
            }
            else{
                heights[j] = 0;
            }
        }
        max_area = max(max_area, get_row_area(heights));
    }    
    return max_area;
}

int main() {
    cout << maximalAreaOfSubMatrixOfAll1({{1, 0, 1, 0, 0}, {1, 0, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 1, 0}}) << endl;
    
    return 0;
}