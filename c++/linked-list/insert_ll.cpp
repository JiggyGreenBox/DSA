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

Node* insert_head(Node* head, int X){
    Node* newNode = new Node(X);
    newNode->next = head;
    return newNode;
}
Node* insert_tail(Node* head, int X){

    if(head == nullptr) {
        return new Node(X);
    }

    Node* curr = head;
    while(curr->next != nullptr){
        curr = curr->next;
    }    

    curr->next = new Node(X);
    return head;
}
Node* insert_kth(Node* head, int X, int pos){
    // empty head
    // insert first position
    // insert anywhere else
    if(pos <= 0) return head;  
    if(head == nullptr && pos==1) return new Node(X);

    Node* dummy = new Node(-1);
    dummy->next = head;

    Node* prev = dummy;
    Node* curr = head;
    int count = 1;

    while(curr != nullptr && count < pos){
        prev = curr;
        curr = curr->next;
        ++count;
    }

    // // pos too large
    // // or pos is the last index after
    // if(curr == nullptr){ // edge case, head==nullptr, pos=1, would need to insert

    //     // index after last
    //     if(count != pos){
    //         delete dummy;
    //         return head;
    //     }
    //     // else, continue to bottom
    //     // steps will be the same        
    // }

    if(curr == nullptr && count != pos){
        // pos is too big
        // we reached the end before pos
        // when count == k
        // [1,2,3] k = 4
        // is handled below
        delete dummy;
        return head;    
    }

    prev->next = new Node(X);
    prev->next->next = curr;

    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}
Node* insert_before_val(Node* head, int X, int val){
    // head null
    // val not found
        // insert nothing

    Node* dummy = new Node(-1);
    dummy->next = head;

    Node* prev = dummy;
    Node* curr = head;

    while(curr != nullptr && curr->val != val){
        prev = curr;
        curr = curr->next;
    }
    
    // if no match
    if(curr == nullptr){
        delete dummy;
        return head;
    }

    // match
    // Node* newNode = new Node(X);
    // prev->next = newNode;
    // newNode->next = curr;
    prev->next = new Node(X, curr);    

    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
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