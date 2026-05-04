#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class MinStack{
private:
    int _size;
    int _min;
    stack<int> st;
public:
    MinStack() {
        _size = 0;
        _min = -1;
    }

    void push(int x) {
        if(st.empty()) {
            _min = x;
            st.push(x);
        }
        else if(x < _min) {
            // update min
            // push prev_min into stack
            int calc = (2*x) - _min;
            st.push(calc);
            _min = x;
        }
        else{
            st.push(x);
        }
    }

    int pop() {
        if(st.top() < _min) {
            // calculate prev min from st.top
            int prev_min = (2*_min) - st.top();
            _min = prev_min;
        }
        st.pop();
        return (st.empty()) ? -1 : st.top();
    }

    int top() {        
        if(st.top() < _min) return _min;
        return st.top();
    }

    bool empty() {
        return _size == 0;
    }

    int size() {
        return _size;
    }

    int min() {
        return _min;
    }
};

int main() {
    MinStack st;
    st.push(10);
    st.push(15);
    cout << st.top() << endl;
    cout << st.min() << endl;
    st.push(8);
    cout << st.top() << endl;
    cout << st.min() << endl;
    st.pop();
    cout << st.top() << endl;
    cout << st.min() << endl;

    return 0;
}


// MIN-STACK
// need to encode the min and curr element information 
// into a single element, and keep min

// min = 1,1,1,-1,-5
// ele = 1,2,3,-1,-5


// store min
// if we get a new min
    // then encode the stack val
    // update new min

// when we call top, now
// the min is the element we want
// if we pop,
    // we get back min from the modified value
        // mod_val = 2*curr - prev_min
        // prev_val is the only unknow
        // prev_min = 2*min - mod_val (st.top()) 
        // min = prev_min
        // st.pop()


