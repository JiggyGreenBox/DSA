#include <iostream>
#include <stdexcept>
using namespace std;

class QueueLinkedList {
private:
    struct Node {
        int data;
        Node *next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    int count = 0;

public:
    QueueLinkedList() {}
    ~QueueLinkedList() {
        while(head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }


    void push(int val) {
        Node *newNode = new Node(val);
        if(count == 0) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void pop() {
        if(isEmpty()) throw std::underflow_error("queue empty");
        Node *temp = head;
        head = head->next;
        delete temp;
        count--;
        if(count == 0) tail = nullptr;
    }
    int front() {
        if(isEmpty()) throw std::underflow_error("queue empty");
        return head->data;
    }

    bool isEmpty() {
        return count == 0;
    }
    int size() {
        return count;
    }

};

int main() {

}