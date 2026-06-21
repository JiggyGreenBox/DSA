#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int val;
    Node* next;

    Node() : val(0), next(nullptr) {}
    Node(int v): val(v), next(nullptr) {}
    Node(int v, Node* n): val(v), next(n){}
    ~Node(){
        cout << "node: " 
             << this->val 
             << " deleted"
             << endl;
    }
};

Node* contruct_ll_vec(const vector<int> &vec){
    if(vec.empty()) return nullptr;

    Node dummy(-1);    
    Node* curr = &dummy;

    for(auto x : vec){
        curr->next = new Node(x);
        curr = curr->next;
    }

    return dummy.next;    
}

void printLL(Node* head){
    while(head){
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void cleanup_ll(Node* head){
    Node* prev = nullptr;
    Node* curr = head;
    while(curr){
        prev = curr;
        curr = curr->next;
        delete prev;
    }    
}