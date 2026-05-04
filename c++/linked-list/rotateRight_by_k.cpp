#include <iostream>
#include "helper_ll.h"
using namespace std;

Node* rotateRight(Node* head, int k) {

    // 0. we need more than 2 nodes
    if(!head || !head->next) return head;

    // 1. get length and connect tail to head
    int n = 1;
    Node* curr = head;
    while(curr->next){
        ++n;
        curr = curr->next;
    }

    // 2. handle edge case here
    k = k%n;
    if(k==0) return head;
    curr->next= head; // only perform this if k!=0

    
    // 3. return new head at the right position
    curr = head;
    Node* prev = nullptr;
    for(int i=0; i<n-k; i++){
        prev = curr;
        curr = curr->next;
    }    
    prev->next = nullptr;
    return curr;
}

Node* rotateRight2(Node* head, int k) {

    // 0. we need more than 2 nodes
    if(!head || !head->next || k==0) return head;

    // 1. get length and connect tail to head
    int n = 1;
    Node* curr = head;
    while(curr->next){
        ++n;
        curr = curr->next;
    }    
    curr->next= head;
    k = k%n;

    
    // 3. return new head at the right position    
    // curr is at last node    
    for(int i=0; i<n-k; i++){        
        curr = curr->next;
    }    
    // curr now at tail
    head = curr->next;      // new head
    curr->next = nullptr;   // new tail     
    return head;
}

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    int k = 2;

    Node* head = contruct_ll_vec(v);
    printLL(head);

    head = rotateRight2(head, k);

    printLL(head);
    cleanup_ll(head);
    return 0;
}