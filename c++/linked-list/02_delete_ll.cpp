#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node* next;
    Node(): data(0), next(nullptr) {}
    Node(int val): data(val), next(nullptr) {}
    Node(int val, Node* n):data(val),next(n) {}
    ~Node() {
        this->next = nullptr;
        cout << "node: " 
             << this->data 
             << " deleted"
             << endl;
    }
};


Node* construct_ll_from_vec(const vector<int> &vec){

    if(vec.empty()) return nullptr;

    Node  dummy(-1);
    Node* tail = &dummy;     

    for(auto x: vec) {        
        tail->next = new Node(x);
        tail = tail->next;
    }    

    return dummy.next;
}

void cleanup_ll(Node* head){
    Node *curr = head;
    while(curr != nullptr){
        Node *del = curr;  // store to delete
        curr = curr->next;          // prepare next node

        del->next = nullptr;
        delete del;        
    }
}

void print_ll(Node* head) {    
    while(head) {
        cout << head->data << " ";
        head = head->next;    
    }
    cout << endl;
}

Node* deleteHead(Node *head) {
    if(!head) return head;
    
    Node* del = head;
    head = head->next;
    
    delete del;
    return head;    
}

Node* deleteTail(Node *head) {

    // 1. empty
    if(!head) return nullptr;

    // 2. single node
    if(!head->next){
        delete head;
        return nullptr;
    }

    // 3. nodes >=2 
    Node *prev = nullptr;
    Node *curr = head;

    // keep tail as last and prev 2nd last
    while(curr->next){
        prev = curr;
        curr = curr->next;
    }
    
    prev->next = nullptr;
    delete curr;       

    return head;         
}


Node* deleteKth(Node* head, int k) {
    // edge cases, kth can be head or tail

    if(!head) return nullptr;

    Node dummy(-1);
    dummy.next = head;

    Node *curr = head;
    Node* prev = &dummy;

    int count = 1;

    while(curr && count < k) {
        prev = curr;
        curr = curr->next;
        count++;
    }

    if(curr) {
        prev->next = curr->next;
        delete curr;
    }

    return dummy.next;
}


Node* delete_value(Node* head, int val){
    Node dummy(-1);
    dummy.next = head;

    Node* prev = &dummy;
    Node* curr = head;

    while(curr && val != curr->data){
        prev = curr;
        curr = curr->next;
    }

    // val not found
    if(!curr){
        cout << "val: "<< val <<" not found in linked list" << endl;
        return head;
    }

    // delete found node
    // can be head as well
    prev->next = curr->next;
    delete curr;

    return dummy.next;    
}
int main() {

    Node* head = construct_ll_from_vec({1,2,3});
    print_ll(head);

    // head = deleteHead(head);
    // head = deleteTail(head);
    // head = deleteKth2(head, 1);
    head = delete_value(head, 1);
    print_ll(head);

    cleanup_ll(head);


    // Node* head2 = construct_ll_from_vec({});    
    // print_ll(head2);
    // head2 = deleteHead(head2);
    // cleanup_ll(head2);

    return 0;
}