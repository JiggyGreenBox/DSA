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

Node* contruct_ll_vec(const vector<int> &vec) {
    if(vec.empty()) return nullptr;

    Node dummy(-1);
    Node* curr = &dummy;

    for(auto x : vec) {
        curr->next = new Node(x);
        curr = curr->next;
    }

    return dummy.next;    
}

void printLL(Node* head){
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void cleanup_ll(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    while(curr){
        prev = curr;
        curr = curr->next;
        delete prev;
    }    
}

Node* insert_head(Node* head, int X){
    Node* n = new Node(X);
    n->next = head;
    return n;
}
Node* insert_tail(Node* head, int X) {

    Node *node = new Node(X);
    if(!head) 
        return node;

    Node* curr = head;
    while(curr->next) {
        curr = curr->next;
    }    

    curr->next = node;
    return head;
}
Node* insert_kth(Node* head, int X, int k) {
    // empty head
    // insert first position
    // insert anywhere else
    // if(pos <= 0) return head;  
    // if(head == nullptr && pos==1) return new Node(X);

    Node dummy(-1);
    dummy.next = head;

    Node* prev = &dummy;
    Node* curr = head;

    int pos = 1;

    while(curr && pos < k){
        prev = curr;
        curr = curr->next;
        pos++;
    }

    // k could be very large/negative, need exact match
    if(pos == k) {        
        Node* node = new Node(X);
        prev->next = node;
        node->next = curr;
    }    

    return dummy.next;    
}
Node* insert_before_val(Node* head, int X, int val){
    
    Node dummy(-1);
    dummy.next = head;

    Node* prev = &dummy;
    Node* curr = head;

    while(curr && curr->val != val){
        prev = curr;
        curr = curr->next;
    }
        
    if(curr) {                
        Node* node = new Node(X);
        prev->next = node;
        node->next = curr;
    }

    return dummy.next;    
}

int main(){
    vector<int> v = {1,2,3};
    Node* head = contruct_ll_vec(v);
    printLL(head);

    // head = insert_head(head, 7);
    // head = insert_tail(head, 7);
    // head = insert_kth(head, 7, 5);
    head = insert_before_val(head, 5, 2);
    printLL(head);

    cleanup_ll(head);
    return 0;
}

/*

insert at head
    need to return new head
    edge case list is empty

insert at tail
    return head
    edge case list is empty

insert kth
    kth can be head or tail


insert before value
    pos can be head / tail
    list can be empty



insert at head    
    Node n = new Node(val)
    n->next = head
    return n

insert at tail 
    Node* node = new Node(val)
    if(!head) 
        return node
    
    Node* curr = head    

    while(curr->next)        
        curr = curr->next

    curr->next = node

    return head


insert kth    

    Node dummy(-1)
    dummy.next = head

    Node* curr = head
    Node* prev = &dummy

    int count = 1

    while(curr && count < k) {
        prev = curr
        curr = curr->next
        count++
    }

    if(curr) {
        prev->next = new Node(val)
        prev->next->next = curr
    }

    return dummy.next


insert before value

    Node dummy(-1)
    dummy.next = head

    Node* curr = head
    Node* prev = &dummy
    
    while(curr && curr->val != target)
        prev = curr
        curr = curr->next

    if(curr) 
        prev->next = new Node(val)
        prev->next->next = curr
    
    return dummy.next
*/