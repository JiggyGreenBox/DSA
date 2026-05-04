
# implement stack using queue
For 2 queues, Which is better?
* **Expensive Push**: Better if you pop more often than you push. (The stack is always "ready" to pop).
    - Top Cost: O(1)
* **Expensive Pop**: Better if you push much more often than you pop. (Adding data is instant).
    - Top Cost: O(n)
## Expensive Push
```sh
# q1 is a reverse queue
# q2 is a temp queue

#1
    Q1 5, 4, 3, 2, 1
    Q2 6

#2
    Q1 
    Q2 6, 5, 4, 3, 2, 1

#3
    Q1 6, 5, 4, 3, 2, 1
    Q1 
```

```cpp
// q1 is a reverse queue
// q2 is a temp queue

void push(int x){
    q2.push(x);
    
    // copy q1 to q2
    while(!q1.empty()) {
        q2.push(q1.front());
        q1.pop();
    }
        
    // q1 = q2;
    // q2.clear();

    // Instead of: q1 = q2; q2.clear(); O(n)
    // Use swap: It's O(1) and leaves q2 empty automatically
    std::swap(q1, q2);
}
```

## Rotate stack
```cpp
// [3,2,1]
// x=4

// s=3
// [3,2,1,4]
// for(3x)
//     [2,1,4,3]
//     [1,4,3,2]
//     [4,3,2,1]
void push(int x) {
    int s = q.size();
    q.push(x);

    for(int i=0; i<s; i++) {
        q.push(q.front());
        q.pop();
    }
}
```

## Expensive Pop
```cpp
#include <iostream>
#include <queue>

class StackExpensivePop {
private:
    std::queue<int> q1;
    std::queue<int> q2;

public:
    // O(1) - Very fast
    void push(int x) {
        q1.push(x);
    }

    // O(n) - Expensive
    int pop() {
        if (q1.empty()) return -1;

        // Move size-1 elements to q2
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }

        // The remaining element is the stack top
        int topValue = q1.front();
        q1.pop(); // Remove it from the stack

        // Swap q1 and q2 to reset for next operation
        std::swap(q1, q2);

        return topValue;
    }

    int top() {
        if (q1.empty()) return -1;
        // Similar to pop, but we push the last element to q2 as well
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        int topValue = q1.front();
        q2.push(topValue); // Keep it!
        q1.pop();
        std::swap(q1, q2);
        return topValue;
    }
};
```