#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node* next;
    Node():data(0),next(nullptr){}
    Node(int val):data(val),next(nullptr){}
    Node(int val, Node* node):data(val),next(node){}
    ~Node(){
        this->next = nullptr;
        cout << "node: " 
             << this->data 
             << " deleted"
             << endl;
    }
};


Node* construct_ll_from_vec(const vector<int> &vec){

    if(vec.empty()) return nullptr;

    Node* dummy = new Node(-1);
    Node* tail = dummy;     

    for(auto x: vec){        
        tail->next = new Node(x);
        tail = tail->next;
    }

    Node* head = dummy->next;
    dummy->next = nullptr;
    delete dummy;

    return head;
}

void cleanup_ll(Node* head){
    Node *curr = head;
    while(curr != nullptr){
        Node *nodeToDelete = curr;  // store to delete
        curr = curr->next;          // prepare next node

        nodeToDelete->next = nullptr;
        delete nodeToDelete;        
    }
}

void print_ll(Node* head) {    
    while(head != nullptr){
        cout << head->data << " ";    
        head = head->next;    
    }
    cout << endl;
}

Node* deleteHead(Node *head) {
    if(head != nullptr){
        Node* nodeToDelete = head;
        head = head->next;
        nodeToDelete->next = nullptr;
        delete nodeToDelete;
        return head;
    }
    return nullptr;
}

Node* deleteTail(Node *head) {

    // 1. empty
    if(head == nullptr) return nullptr;

    // 2. single node
    if(head->next == nullptr){
        delete head;
        return nullptr;
    }

    // 3. nodes >=2 
    Node *prev = nullptr;
    Node *tail = head;

    // keep tail as last and prev 2nd last
    while(tail->next != nullptr){
        prev = tail;
        tail = tail->next;
    }

    Node *nodeToDelete = tail;      // prepare delete for last node
    prev->next = nullptr;           // unlink 2nd last node    
    delete nodeToDelete;            // delete last node
    return head;                    // return head
}


Node* deleteKth(Node* head, int k){
    // empty?
    // delete head?
    // delete tail?
    // delete middle

    // run A, handle each case separately
    if(head == nullptr) return nullptr;
    // head
    if(k==1){
        Node* newHead = head->next;
        head->next = nullptr;
        delete head;
        return newHead;
    }
    int count = 1;
    Node* prev = nullptr;
    Node* tail = head;
    while (tail != nullptr) {
        prev = tail;
        tail = tail->next;
        ++count;
        if(count == k){
            // time to delete            
            if(tail->next != nullptr){
                prev->next = tail->next;
                tail->next = nullptr;
                delete tail;     
                           
            }
            else{
                prev->next = nullptr;
                delete tail;                
            }
            return head;
        }
    }
    return head;
    
}



Node* deleteKth2(Node* head, int k){

    if(k<=0){
        cout << "invalid k" << endl;
        return head;
    }

    // use dummy to reduce cases
    Node* dummy = new Node(-1);
    dummy->next = head;

    // head could be nullptr
    // delete 1st or last should be same
    // need access to the previous and current
    // need to return head
    // handle deleting of head

    Node* prev = dummy;
    Node* tail = head;    
    int count = 1;

    // move tail by k places
    while(tail != nullptr && count<k) {
        prev = tail;
        tail = tail->next;
        ++count;
    }

    // k too large
    if(tail == nullptr){
        cout << "k larger than linked list" << endl;
        dummy->next = nullptr;
        delete dummy;
        return head;
    }

    // skip tail
    prev->next = tail->next;

    // delete tail
    tail->next = nullptr;
    delete tail;

    // return head
    // return head;
    // return prev;
    Node* newHead = dummy->next;
    dummy->next = nullptr;
    delete dummy;
    return newHead;
}


Node* deleteKth3(Node* head, int k){
    if(k<=0) return head;

    Node* dummy= new Node(-1);
    dummy->next = head;
    
    Node* prev = dummy;
    Node* tail = head;
    int count = 1;

    while(tail != nullptr && count < k){
        prev = tail;
        tail = tail->next;
        ++count;
    }

    // k too big
    if(tail == nullptr){
        delete dummy;
        return head;
    }

    // delete valid node
    prev->next = tail->next;
    delete tail;

    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}


Node* delete_value(Node* head, int val){
    Node* dummy = new Node(-1);
    dummy->next = head;

    Node* prev = dummy;
    Node* curr = head;

    while(curr != nullptr && val != curr->data){
        prev = curr;
        curr = curr->next;
    }

    // val not found
    if(curr == nullptr){
        cout << "val: "<< val <<" not found in linked list" << endl;
        return head;
    }

    // delete found node
    // can be head as well
    prev->next = curr->next;
    delete curr;

    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
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