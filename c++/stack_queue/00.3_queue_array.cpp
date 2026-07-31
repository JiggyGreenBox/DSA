#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

/*
we have wrap around indices with this DS

lets say count is 10
we move rear ahead with push
we also move front ahead with pop

so both can move ahead
but since we could be under capacity,
we wrap around
    for eg.
    cap = 10
    push, pop 8 times
    count = 0
    front-idx = rear-idx = 7

    if we push and cross idx 9
    we can occupy idx 0 onwards
        by arr[(idx+1) % cap]
*/

class MyQueue {
    private:
        int *arr;
        int count;
        int front_idx;
        int rear_idx;
        int capacity;

        void resize() {
            int new_capacity = 2 * capacity;
            int *new_arr = new int[new_capacity];

            for(int i=0; i<count; i++) {
                new_arr[i] = arr[(front_idx+i) % capacity];
            }
            
            delete[] arr;
            arr = new_arr;

            capacity = new_capacity;
            front_idx = 0;
            rear_idx = count - 1;
        }
    public:
        MyQueue(int n = 4) {
            capacity = n;
            arr = new int[capacity];

            front_idx = 0;
            rear_idx = -1; // we always +1 for push
            count = 0;
        }

        ~MyQueue() {
            delete[] arr;
        }

        void push(int val) {
            if(count == capacity) resize();

            rear_idx = (rear_idx+1) % capacity;
            arr[rear_idx] = val;
            count++;
        }
        void pop() {
            if(count == 0) throw std::underflow_error("queue is empty");
            front_idx = (front_idx + 1) % capacity; // use spots in the front if they exist
            count--;
        }
        int front() const {
            if(count == 0) throw std::underflow_error("queue is empty");
            return arr[front_idx];
        }

        bool isEmpty() const {
            return count == 0;
        }

        int size() const {
            return count;
        }

};

int main() {
    return 0;
}