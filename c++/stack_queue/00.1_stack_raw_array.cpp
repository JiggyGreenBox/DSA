#include <iostream>
#include <stdexcept>
using namespace std;

class StackArray {
    private:
        int *arr;
        int capacity;
        int topIndex;

        void resize() {
            capacity *= 2;
            int *newArr = new int[capacity];

            for(int i=0; i < topIndex+1; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }

    public:
        StackArray(int n = 4) : capacity(n), topIndex(-1)  {
            arr = new int[capacity];
        }
        ~StackArray() {
            delete[] arr;
        }

        void push(int x) {
            if(capacity == topIndex-1) resize();
            arr[++topIndex] = x;
        }

        int top() const {
            if(isEmpty()) throw std::underflow_error("Stack empty");
            return arr[topIndex];
        }

        bool isEmpty() const {
            return topIndex == -1;
        }

        // void pop() {
        //     if(isEmpty()) throw std::underflow_error("Stack empty");
        //     topIndex--;
        // }
        int pop() {
            if(isEmpty()) throw std::underflow_error("Stack empty");            
            int popped = arr[topIndex];
            topIndex--;
            return popped;            
        }
};

int main() {
    StackArray st;
    // st.push(2);
    // st.push(3);
    cout << st.top() << endl;
    // st.pop();
    // cout << st.top() << endl;
    

    return 0;
}