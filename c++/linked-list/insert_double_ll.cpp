#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int val;
    Node* next;
    Node* prev;
    Node(int val):val(val),next(nullptr),prev(nullptr){}
    virtual ~Node(){
        cout << "destroy : " 
             << this->val 
             << endl;
    }
};

Node* construct_double_LL(const vector<int> &v){
    if(v.empty()) return nullptr;
    Node* dummy = new Node(-1);    

    Node* prev = dummy;
    Node* curr = nullptr;    

    for(auto x:v){
        
        curr = new Node(x);
        curr->prev = prev;
        prev->next = curr;
        prev = curr;
    }

    
    Node* newHead = dummy->next;
    // newHead->prev = nullptr;
    if (newHead) newHead->prev = nullptr;    
    delete dummy;
    return newHead;
}

void print_double_LL(Node* head){
    while(head != nullptr){
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void cleanup_double_LL(Node* head){     
    while(head != nullptr){

        // head->prev = nullptr;   // unlink prev
        // gpt said unneccessary

        Node* temp = head;      // copy for delete
        head = head->next;      // traverse ahead
        delete temp;            // delete
    }
}


Node* insert_before_head(Node* head, int X){
    if(!head) return new Node(X);
    
    Node* newHead = new Node(X);
    newHead->next = head;
    head->prev = newHead;
    return newHead;
}

Node* insert_before_tail(Node* head, int X){
    // no head
    if(!head) return new Node(X);

    // head and tail are the same?
    Node* dummy = new Node(-1);
    dummy->next = head;
    head->prev = dummy;

    // 2 nodes
    Node* curr = head;
    while(curr->next != nullptr){
        curr = curr->next;
    }

    Node* newNode = new Node(X);
    Node* prev = curr->prev;

    prev->next = newNode;
    newNode->next = curr;
    newNode->prev = prev;
    curr->prev = newNode;

    Node* newHead = dummy->next;
    newHead->prev = nullptr;
    delete dummy;
    return newHead;    
}

Node* insert_before_tail_no_dummy(Node* head, int X){
    if(!head) return new Node(X);

    Node* tail = head;

    while(tail->next){
        tail = tail->next;
    }

    // tail is def last element
    // if we have more than 2, then we know what to do
    // insert new node inbetween them
    // but if we only have 1 node then its an edge case that 
    // needs to be handled
    if(!tail->next){
        Node* newHead = new Node(X);
        newHead->next = tail;
        tail->prev = newHead;
        return newHead;
    }

    // def more than 2 nodes
    Node* prev = tail->prev;
    Node* newNode = new Node(X);

    prev->next = newNode;
    newNode->prev = prev;
    newNode->next = tail;    
    tail->prev = newNode;
    return head;
}

Node* insert_before_kth(Node* head, int X, int k){

    // since before kth
    // minimum 1 node is required

    // if(!head) return nullptr;
    // if(k<=0) return nullptr;

    // if(!head || k<=0) return nullptr;

    if(k<=0) return nullptr;
    if(!head && k==1) return new Node(X);
    if(!head) return nullptr; // k > 1

    // create dummy for single node condition
    Node* dummy = new Node(-1);
    dummy->next = head;
    head->prev = dummy;
    
    // keep tail at kth or end
    Node* tail = head;
    int count = 1;
    while(tail && count < k){
        tail = tail->next;
        ++count;
    }

    if(tail == nullptr){
        cout << "k too large" << endl;

        Node* newHead = dummy->next;
        newHead->prev = nullptr;
        delete dummy;
        return newHead;
    }

    // valid k and tail
    Node* prev = tail->prev;
    Node* newNode = new Node(X);
    prev->next = newNode;    
    newNode->prev = prev;
    newNode->next = tail;
    tail->prev = newNode;
    
    Node* newHead = dummy->next;
    newHead->prev = nullptr;
    delete dummy;
    return newHead;

}
// Node* insert_before_given(Node* head, int X){}

// guaranteed not head
void insertBeforeGivenNode(Node* node, int X) {
    Node* prev = node->prev;
    Node* newNode = new Node(X);

    prev->next = newNode;
    newNode->prev = prev;
    newNode->next = node;
    node->prev = newNode;
}

Node* insertBeforeGivenNode2(Node* node, int X) {
    if(node == nullptr){
        return nullptr;
    }
    Node* prev = node->prev;        // prev could be null
    Node* newNode = new Node(X);

    if(prev) prev->next = newNode;    
    newNode->prev = prev;
    newNode->next = node;
    node->prev = newNode;

    // return head
    while(node->prev){
        node = node->prev;
    }
    return node;
}


int main(){
    vector<int> v = {1,2,3,4};
    // vector<int> v = {};
    Node* head = construct_double_LL(v);
    print_double_LL(head);

    // head = insert_before_head(head, 99);
    // head = insert_before_tail(head, 99);
    head = insert_before_kth(head, 99, 2);

    Node* p = head->next;
    head = insertBeforeGivenNode2(p, 299);
    

    print_double_LL(head);

    cleanup_double_LL(head);
    return 0;
}