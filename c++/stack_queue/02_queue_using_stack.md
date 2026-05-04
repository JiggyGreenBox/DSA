# queue using stack
##  2 stack, with expensive push
```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <stack>
using namespace std;

class Queue_impl{
private:
    stack<int> st1;
    stack<int> st2;
    int _size;
public:
    Queue_impl() :_size(0) {}
    void push(int x) {
        while(!st1.empty()) {
            st2.push(st1.top());
            st1.pop();
        }
        
        st2.push(x);
        
        while(!st2.empty()) {
            st1.push(st2.top());
            st2.pop();
        }
        _size++;
    }
    
    int front() {
        if(_size > 0) return st1.top();
        return -1;
    }

    int pop() {
        if(_size == 0) return -1;
        
        _size--;
        int popped = st1.top();
        st1.pop();
        return popped;
    }

    int size() {
        return _size;
    }
    
    bool empty() {
        return _size == 0;
    }

    ~Queue_impl() {
        while(!st1.empty()) {
            st1.pop();
        }
    }
};
int main() {
    Queue_impl q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    
    cout << "size: " << q.size() << endl;
    
    while(!q.empty()){
        cout << q.front() << endl;
        q.pop();
    }
    
    
    
    return 0;
}
```
## amortized O(1) operations
```cpp
// Online C++ compiler to run C++ program online
#include <iostream>
#include <stack>
using namespace std;

class Queue_impl{
private:
    stack<int> in;
    stack<int> out;
public:
    Queue_impl() {}
    
    void transfer() { // O(n)
        if(out.empty()){
            while(!in.empty()){
                out.push(in.top());
                in.pop();
            }
        }
    }
    
    void push(int x) {
        in.push(x); // O(1)
    }
    
    int front() {
        transfer(); // moves everything to out
        if(out.empty()) return -1;
        return out.top();
    }

    int pop() {
        transfer(); // moves everything to out
        int popped = out.top();
        out.pop();
        return popped;
    }

    int size() {
        return in.size() + out.size();
    }
    
    bool empty() {
        return in.empty() && out.empty();
    }
};
int main() {
    Queue_impl q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    
    cout << "size: " << q.size() << endl;
    
    while(!q.empty()){
        cout << q.front() << endl;
        q.pop();
    }

    return 0;
}
```

🔍 Why This Is Amortized O(1)
Important invariant

Each element:

is pushed once

is moved from st_in → st_out once

is popped once

➡️ Maximum 3 constant operations per element

No element is ever moved back.

🧠 Interview-Grade Explanation (Say This)

“pop() is worst-case O(n) when st_out is empty, but amortized O(1) because each element is transferred only once across the entire sequence of operations.”

That sentence alone is gold.

⚠️ Compare With Your Earlier Version
Aspect	Your first version	This version
push	O(n)	O(1)
pop	O(1)	amortized O(1)
Total work	O(n²) worst sequences	O(n) total
Interview-preferred	❌	✅