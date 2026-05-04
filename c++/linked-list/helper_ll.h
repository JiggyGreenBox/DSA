#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int val;
    Node* next;

    Node():val(0),next(nullptr){}
    Node(int val):val(val),next(nullptr){}
    Node(int val, Node* next):val(val),next(next){}
    ~Node(){
        cout << "node: " 
             << this->val 
             << " deleted"
             << endl;
    }
};

Node* contruct_ll_vec(const vector<int> &vec){
    if(vec.empty()) return nullptr;

    Node* dummy = new Node(-1);
    Node* curr = dummy;

    for(auto x : vec){
        curr->next = new Node(x);
        curr = curr->next;
    }

    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}

void printLL(Node* head){
    while(head != nullptr){
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void cleanup_ll(Node* head){
    Node* prev = nullptr;
    Node* curr = head;
    while(curr != nullptr){
        prev = curr;
        curr = curr->next;
        delete prev;
    }    
}