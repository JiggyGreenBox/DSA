#include <iostream>
#include <stdexcept>
using namespace std;

class ListStack {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val, Node* n) : data(val), next(n) {}
    };

    Node *head = nullptr;
    int stackSize = 0;

public:
    ListStack() {}
    ~ListStack() {
        while(head) {
            while(!isEmpty()) pop();
        }
    }

    bool isEmpty() {
        return head == nullptr;
    }

    // size_t size() const { return stackSize; }
    int size() const { return stackSize; }

    void pop() {
        if(!head) throw std::underflow_error("stack empty");

        Node* temp = head;
        head = head->next;
        delete temp;
        stackSize--;        
    }

    void push(int val) {
        head = new Node(val, head);
        stackSize++;
    }

    int top() {
        if(!head) throw std::underflow_error("stack empty");
        return head->data;
    }
};

int main() {
    ListStack st;

    // st.push(5);
    // st.push(6);

    // cout << st.top() << endl;

    st.pop();

    // cout << st.top() << endl;

    return 0;
}