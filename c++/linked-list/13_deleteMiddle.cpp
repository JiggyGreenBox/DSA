#include <iostream>
#include <vector>
#include "helper_ll.h"
using namespace std;


// this version uses dummy
// handles single node
Node* deleteMiddle1(Node* head){
    if(!head) 
        return nullptr;

    Node dummy(-1);
    dummy.next = head;

    Node* prev = &dummy;
    Node* slow = head;    
    Node* fast = head;

    while(fast && fast->next){
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    prev->next = slow->next;
    delete slow;

    return dummy.next;    
}

Node* deleteMiddle2(Node* head){
    if(!head) return head;
    if(!head->next) {
        delete head;
        return nullptr;
    }

    Node* prev = nullptr;
    Node* slow = head;
    Node* fast = head;

    while(fast && fast->next){
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = slow->next;
    delete slow;
    return head;
}

int main(){
    // vector<int> v = {1, 2, 3, 4, 5};
    // vector<int> v = {3, 8, 7, 1, 3};
    vector<int> v = {1};
    // vector<int> v = {1,2};
    // vector<int> v = {1,2,3};
    
    Node* head = contruct_ll_vec(v);
    printLL(head);
    head = deleteMiddle2(head);    
    printLL(head);
    cleanup_ll(head);
    return 0;
}

