#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void print(const vector<int>& res) {
    cout << "[ ";
    for(int n : res) {
        cout << n << " ";
    }
    cout << "]\n";
}

vector<int> nextLargerElement1(const vector<int> arr) {
    // brute force
    int n = arr.size();
    vector<int> ans(n,-1);
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(arr[j] > arr[i]){
                ans[i] = arr[j];
                break;
            }
        }
    }
    return ans;
}

vector<int> nextLargerElement2(const vector<int> arr) {    
    int n = arr.size();
    vector<int> ans(n,-1);

    stack<int> st;

    for(int i=n-1; i>=0; i--) {
        // discard stack values less than curr num
        // aka store numbers in a decreasing order
        while(!st.empty() && arr[i] >= st.top()) {
            st.pop();
        }
        // if the stack is empty, no valid larger elem found
        // else the top of the stack
        // ans[i] = (st.empty()) ? -1 : st.top();
        if(!st.empty()) ans[i] = st.top();

        // push curr num for next iteration
        st.push(arr[i]);
    }
   
    return ans;
}

vector<int> nextLargerElementForward(const vector<int>& arr) {
// st.top() is past elements
// when we find something greater
// assign nge
// and pop it

/*
    [1, 3, 2, 4]
    [3, 4, 4,-1]

    elem[0] = 1
        st = []
        st.push[0]
    elem[1] = 3
        st[0]
            3 > 1 ? next element is greater?
                yes 
                    assign this to st.top == last idx
                val 1, idx=0 will never be used again as we have found val 3, idx=1
            ans[st.top] = arr[i]
            ans[0] = 3
        
        st.push[1]
    
    elem[2] = 2
        st[1]
            2 > 3 ? 
                no, keep looking
            st.push[2]

    elem[3] = 4
        st[2,1]
            4 > 2?
                yes
                    ans[st.top] = arr[i]
                    ans[2] = 4
                    st.pop

            4 > 3?
                yes
                    ans[st.top] = arr[i]
                    ans[1] = 4
                    st.pop
        st.push(3)
    STOP
    [3,4,4,-1]
*/

    int n = arr.size();
    vector<int> ans(n,-1);

    stack<int> st; // store idx instead of val

    for(int i=0; i<n; i++){

        while(!st.empty() && arr[i] > arr[st.top()]){
            ans[st.top()] = arr[i];
            st.pop();
        }

        st.push(i);
    }
    return ans;
}

int main() {
    // print(nextLargerElementForward({5, 5}));
    // print(nextLargerElement1({1, 3, 2, 4}));
    // print(nextLargerElementForward({1, 3, 2, 4}));
    // print(nextLargerElement1({6, 8, 0, 1, 3}));    
    // print(nextLargerElementForward({6, 8, 0, 1, 3}));

    print(nextLargerElement1({3,3,3,4}));    
    return 0;
}