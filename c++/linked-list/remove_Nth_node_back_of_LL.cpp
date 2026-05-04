#include <iostream>
#include <vector>
#include "helper_ll.h"


Node* removeNthFromEnd(Node* head, int n) {
    if(!head) return head;

    // get count of nodes
    Node* curr = head;
    int count = 0;
    while (curr) {
        count++;
        // cout << curr->val << endl;
        curr = curr->next;        
    }

    int remove_idx = count - n;

    // reset count to zero
    Node* dummy = new Node(-1);
    dummy->next = head;
    count = 0;
    curr = head;
    Node* prev = dummy;
    while(curr){
        if(count == remove_idx){
            prev->next = curr->next;
            delete curr;
            break;
        }
        count++;
        prev = curr;
        curr = curr->next;
    }
    
    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}


Node* removeNthFromEnd2(Node* head, int n) {
    // use fast and slow pointers
    Node* slow = head;
    Node* fast = head;

    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }    

    // if n is size of the list, fast will be nullptr
    if(fast == nullptr){
        Node* delnode = head;
        head = head->next;
        delete delnode;
        return head;
    }

    while(fast->next){
        fast = fast->next;
        slow = slow->next;
    }    
    Node* delnode = slow->next;    
    slow->next = slow->next->next;
    delete delnode;
    return head;
}

int main(){
    // vector<int> v ={1, 2, 3, 4, 5};
    // int n = 2;
    vector<int> v ={5, 4, 3, 2, 1};
    int n = 5;
    
    Node* head = contruct_ll_vec(v);
    printLL(head);
    // head = sortList2(head);
    head = removeNthFromEnd2(head, n);
    printLL(head);
    cleanup_ll(head);
    return 0;
}
