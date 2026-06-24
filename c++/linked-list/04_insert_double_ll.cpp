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

Node* construct_double_LL(const vector<int> &v){
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

    
    return dummy.next;    
}

void print_double_LL(Node* head){
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void cleanup_double_LL(Node* head){     
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

Node* insertBeforeNode3(Node* head, Node* target, int x) {

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

Node* insertBeforeNode4(Node* target, int X) {

    if (!target) return nullptr;

    Node* node = new Node(X);

    // target is at head
    if (!target->prev) {
        node->next = target;
        target->prev = node;
        return node; // node is new head
    }

    Node* prev = target->prev;

    prev->next = node;
    node->prev = prev;

    node->next = target;
    target->prev = node;

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