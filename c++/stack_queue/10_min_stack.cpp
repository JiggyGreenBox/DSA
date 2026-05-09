#include <iostream>
#include <vector>
#include <stdexcept>
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

class MinStackNoPair {
    private:
        stack<long long> st;
        long long min_val;
        // stack<int> st;
        // int min_val;
    public:

        void push(int val) {
            if(st.empty()) {
                st.push(val);
                min_val = val;
            }
            else if(val < min_val) {
                
                long long encoded = 2*val - min_val;
                st.push(encoded);
                min_val = val;
                // val < min_val
                // val+val < min_val + val
                // 2val - min_val < val
                // we want encoded < val
            }
            else {
                st.push(val);
            }
        }
        void pop() {
            // top value is encoded
            // recover prev_min
            if(st.top() < min_val) {
                // int encoded = 2*val - min_val;
                // top = 2*min - prev_min
                // prev_min = 2*min-top
                long long prev_min = 2*min_val - st.top();
                min_val = prev_min;
                st.pop();
            }
            // top value is unencoded
            else{
                st.pop();
            }
        }

        int top() {
            if(st.empty()) throw std::underflow_error("min stack is empty");
            if(min_val < st.top()) return min_val;
            return st.top();
        }
        int getMin() {
            if(st.empty()) throw std::underflow_error("min stack is empty");
            return min_val;
        }
        int size() {
            return st.size();
        }
        bool isEmpty() {
            return st.empty();
        }      
};


class MinStackPair {
    private:
        stack<pair<int,int>> st;
    public:
        void push(int val) {
            if(st.empty()) {
                st.push({val, val});
            }
            else{
                int minVal = min(val, st.top().second);
                st.push({val, minVal});
            }
        }
        void pop() {
            if(st.empty()) throw std::underflow_error("min stack is empty");

            st.pop();
        }
        int top() {
            if(st.empty()) throw std::underflow_error("min stack is empty");

            return st.top().first;
        }
        int getMin() {
            if(st.empty()) throw std::underflow_error("min stack is empty");

            return st.top().second;
        }
        int size() {
            return st.size();
        }
        bool isEmpty() {
            return st.empty();
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

/*
whats the thinking behind this single stack algorithm?
    consider: [1,2,3,4,-1, 3,-5, 5]
        min: [1,1,1,1,-1,-1,-5,-5]


    stack store val, min at each step

    we store a global min
    when a new min comes along we must encode old min
    otherwise we maintain unencoded values
        the encoded value is in the stack not in min_val
    
    how to know if a value is encoded?
        st.top < cur_min

    st[5]
    min = 5
    new = 2

        min needs to be updated
        old_min needs to be encoded
            encoded = 2*newval - oldmin
                    = 2*2 - 5
                    = -1
    st[5,2]
    min = -1

    if we now call top
        if top < min return top
        return min
    
    pop
        if top < min return top

        encoded = 2*newval - oldmin
        cur_min = 2*top - oldmin
        oldmin = 2*top - curmin
               = 2*2 - (-1)
               = 5

    
    
    




*/


