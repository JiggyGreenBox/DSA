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
Node* delete_d_ll_head(Node* head){
    if(!head  || !head->next) return nullptr;

    Node* temp = head;

    head = head->next;
    head->prev = nullptr;

    delete temp;
    return head;
}
Node* delete_d_ll_tail(Node* head){

    // edge cases
    if(head == nullptr) return nullptr;
    if(head->next == nullptr){
        delete head;
        return nullptr;
    }

    // at least 2 nodes exist
    Node* curr = head;
    // Node* prev = nullptr;

    while(curr->next != nullptr){
        // prev = curr;
        curr = curr->next;
    }

    // curr to be delete
    // prev new tail
    // prev->next = nullptr;
    // delete curr;

    Node* prev = curr->prev;
    prev->next = curr->prev = nullptr;
    delete curr;
    return head;

    // this code doesnt work if head is nullptr
    // or if ll has only 1 node

    // can use dummy
    // or can check for head and head->next
}
Node* delete_d_ll_kth(Node* head, int k){

    if(k<=0) return head;

    Node* dummy = new Node(-1);
    dummy->next = head;
    if(head) head->prev = dummy;

    // Node* prev = dummy; // dont need prev pointers in double ll
    Node* curr = head;
    int count = 1;

    while(curr != nullptr && count < k){        
        curr = curr->next;
        ++count;
    }

    // k may be too large, or head = nullptr
    if(!curr){
        cout << "k too large or head nullptr" << endl;
        Node* newHead = dummy->next;
        if(newHead) newHead->prev = nullptr; 
        delete dummy;
        return newHead;
    }

    // k is valid, curr is valid
    // delete curr
    Node* prev = curr->prev;
    Node* next = curr->next;

    prev->next = next;
    // next->prev = prev; // null check on next?
    if(next) next->prev = prev;

    curr->next = curr->prev = nullptr;
    delete curr;

    Node* newHead = dummy->next;    
    if(newHead) newHead->prev = nullptr;
    delete dummy;
    return newHead;
}

int main(){
    vector<int> v = {1,2,3,4};
    Node* head = construct_double_LL(v);
    print_double_LL(head);

    // head = delete_d_ll_head(head);
    // head = delete_d_ll_tail(head);
    head = delete_d_ll_kth(head, 1);

    print_double_LL(head);

    cleanup_double_LL(head);
    return 0;
}