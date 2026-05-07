#include <iostream>
#include <stdexcept>
#include <stack>
using namespace std;
/*
this is amortized O(1)
because during an elements lifetime
they are in instack once, and outstack once

vs other implementations where we move mulitple times
*/
class QueueUsingStack {
private:
    stack<int> inStack, outStack;

    // inStack has the latest as top
    // outstack has the oldest as top
    // we rely on outstack to be empty for proper transfer

    void transfer() {
        while(!inStack.empty()) {
            outStack.push(inStack.top());
            inStack.pop();
        }
    }
public:
    QueueUsingStack() {}

    void push(int val) {
        inStack.push(val);
        // keep adding here until required
        // only when top or pop is called,
        // will we need the outstack
    }

    void pop() {
        if(empty()) throw std::underflow_error("queue is empty");

        if(outStack.empty()) {
            transfer();
        }
        outStack.pop();
    }

    int front() {
        if(empty()) throw std::underflow_error("queue is empty");

        if(outStack.empty()) {
            transfer();
        }
        return outStack.top();
    }    

    bool empty() {
        return inStack.empty() && outStack.empty();
    }

    int size() {
        return inStack.size() + outStack.size();
    }
};

int main() {

    // inStack used
    // outStack empty until pop/front
    QueueUsingStack q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);

    cout << q.front() << endl;  //instack emptied

    q.pop();                    // remove 1

    cout << q.front() << endl;

    q.push(5);                  // instack 1, wont move until outstack is empty

    q.pop();                    // remove 2
    q.pop();                    // remove 3

    cout << q.front() << endl;  // still unmoved

    q.pop();                    // remove 4, outstack empty                  

    cout << q.front() << endl;  // OS empty, IS moved here


    return 0;
}