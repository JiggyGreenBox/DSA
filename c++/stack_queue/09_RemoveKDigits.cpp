#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

string removeKdigits(const string nums, int k) {
    // use a monotonic increasing stack
    stack<int> st;
    int removals = 0;

    for(char c : nums) {
        int num = c - '0';
        while(!st.empty() && removals<k && num < st.top()) {
            st.pop();
            removals++;
        }
        // dont push if stack is empty and number is 0
        // push if stack is not empty or greater than 0
        if(!st.empty() || num > 0) st.push(num);
        // why is this
        // because if we have 100099
        // and we can remove 1
        // then then we pop 1, after first 0
        // st[0,0,0,9,9]
        // those 0s are useless and need to removed later
        // so dont push them
        
    }

    // "12345",2 need to remove from an unpopped stack
    while (!st.empty() && removals < k) {        
        st.pop();
        removals++;
    }
    

    if(st.empty()) return "0";

    string res;
    while(!st.empty()){
        res += st.top()+'0';
        st.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}


// for each num
// push into stack
// if num is greater than top, remove it
    // we can do this max of k times
// reverse the stack
// this is the answer

// edge cases
    // leading zeros
    // 10021, k=2, ans=1
    // 110021, k=2, ans=21
    // 1011021, k=2, ans=1021

int main() {
    cout << removeKdigits("12345", 2) << endl;
    cout << removeKdigits("1002991", 3) << endl;
    // cout << removeKdigits("541892", 2) << endl;
    
    return 0;
}