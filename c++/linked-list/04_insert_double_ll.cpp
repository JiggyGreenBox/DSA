#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int val;
    Node* next;
    Node* prev;
    Node(int v) : val(v), next(nullptr), prev(nullptr) {}
    virtual ~Node(){
        cout << "destroy : " 
             << this->val 
             << endl;
    }
};

Node* construct_DLL(const vector<int> &v){
    if(v.empty()) return nullptr;
    Node dummy(-1);    

    Node* prev = &dummy;
    Node* curr = nullptr;    

    for(auto x:v) {
        
        curr = new Node(x);
        curr->prev = prev;
        prev->next = curr;
        prev = curr;
    }

    dummy.next->prev = nullptr;
    
    return dummy.next;    
}

Node* construct_DLL_canon(const vector<int> &v){

    if(v.empty()) 
        return nullptr;

    Node* head = new Node(v[0]);
    Node* prev = head;      

    for (int i=1; i<v.size(); i++) {

        Node *curr = new Node(v[i]);

        curr->prev = prev;
        prev->next = curr;

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


Node* insert_before_head(Node* head, int X){

    Node* node = new Node(X);

    if(!head) return node;
    
    node->next = head;
    head->prev = node;
    return node;
}


Node* insert_before_tail(Node* head, int X) {

    Node *node = new Node(X);

    if(!head) return node;

    if(!head->next) {
        head->prev = node;
        node->next = head;
        return node;
    }

    Node* tail = head;

    while(tail->next){
        tail = tail->next;
    }

    // prev, node, tail
    Node* prev = tail->prev;
    prev->next = node;

    node->prev = prev;
    node->next = tail;

    tail->prev = node;
    return head;
}

Node* insert_before_kth(Node* head, int X, int k) { 
    // no dummy nodes in double
    // handle insertion before head sep

    if(k == 1) {
        Node *node = new Node(X);
        node->next = head;
        if(!head) return node;

        head->prev = node;
        return node;
    }

    Node* curr = head;
    int count = 1;
    while(curr && count < k) {
        curr = curr->next;
        count++;
    }

    if(!curr) return head; // count too large

    Node *node = new Node(X);

    Node *prev = curr->prev;

    prev->next = node;
    node->prev = prev;

    node->next = curr;
    curr->prev = node;
    
    return head;
}
// Node* insert_before_given(Node* head, int X){}



Node* insertBeforeGivenNode(Node* node, int X) {

    if(!node)
        return nullptr;
    
    Node* prev = node->prev;        // prev could be null
    Node* newNode = new Node(X);

    if(prev) 
        prev->next = newNode;    

    newNode->prev = prev;
    newNode->next = node;

    node->prev = newNode;

    // return head
    while(newNode->prev){
        newNode = newNode->prev;
    }
    return newNode;
}

Node* insertBeforeNode2(Node* head, Node* target, int x) {

    Node* node = new Node(x);

    if (target == head) {
        node->next = head;
        head->prev = node;
        return node;
    }

    Node* prev = target->prev;

    prev->next = node;
    node->prev = prev;

    node->next = target;
    target->prev = node;

    return head;
}


int main(){
    vector<int> v = {1,2,3,4};
    // vector<int> v = {};
    Node* head = construct_DLL(v);
    print_DLL(head);

    // head = insert_before_head(head, 99);
    // head = insert_before_tail(head, 99);
    head = insert_before_kth(head, 99, 2);

    Node* p = head->next;
    head = insertBeforeGivenNode(p, 299);
    

    print_DLL(head);

    cleanup_DLL(head);
    return 0;
}