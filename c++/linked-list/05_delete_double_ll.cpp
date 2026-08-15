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

Node* construct_DLL(const vector<int> &v){
    // if(v.empty()) return nullptr;
    // Node* dummy = new Node(-1);    

    // Node* prev = dummy;
    // Node* curr = nullptr;    

    // for(auto x:v){
        
    //     curr = new Node(x);
    //     curr->prev = prev;
    //     prev->next = curr;
    //     prev = curr;
    // }

    
    // Node* newHead = dummy->next;
    // // newHead->prev = nullptr;
    // if (newHead) newHead->prev = nullptr;    
    // delete dummy;
    // return newHead;

    if(v.empty())
        return nullptr;

    Node* head = new Node(v[0]);
    Node* prev = head;

    for(int i=1; i<v.size(); i++) {
        Node *curr = new Node(v[i]);

        prev->next = curr;
        curr->prev = prev;

        prev = curr;
    }

    return head;
}

void print_DLL(Node* head){
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void cleanup_DLL(Node* head){     
    while(head) {

        // head->prev = nullptr;   // unlink prev
        // gpt said unneccessary

        Node* temp = head;      // copy for delete
        head = head->next;      // traverse ahead
        delete temp;            // delete
    }
}

Node* delete_DLL_head(Node* head) {

    if(!head || !head->next) 
        return nullptr;

    Node* temp = head;

    head = head->next;
    head->prev = nullptr;

    delete temp;
    return head;
}

Node* delete_DLL_tail(Node* head) {

    // edge cases
    if(head == nullptr) 
        return nullptr;

    if(head->next == nullptr) {
        delete head;
        return nullptr;
    }

    // at least 2 nodes exist
    Node* curr = head;

    while(curr->next != nullptr) {        
        curr = curr->next;
    }    

    Node* prev = curr->prev;
    prev->next = curr->prev = nullptr;
    delete curr;
    return head;
}


Node* delete_DLL_kth(Node* head, int k) {
    // instead of thinking head, middle, tail
    // think
    // prev <-> curr <-> next

    if(!head || k<=0) return head;

    Node* curr = head;
    int pos = 1;

    while(curr && pos < k) {
        curr = curr->next;
    }

    if(!curr) return head; // k was too large

    Node *prev = curr->prev;
    Node *next = curr->next;

    if(prev) 
        prev->next = next;
    else
        head = next; // curr == head

    if(next)
        next->prev = prev;

    delete curr;
    
    return head;
}

int main() {
    vector<int> v = {1,2,3,4};
    Node* head = construct_DLL(v);
    print_DLL(head);

    // head = delete_DLL_head(head);
    // head = delete_DLL_tail(head);
    head = delete_DLL_kth(head, 1);

    print_DLL(head);

    cleanup_DLL(head);
    return 0;
}