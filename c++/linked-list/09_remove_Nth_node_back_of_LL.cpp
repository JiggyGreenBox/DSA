#include <iostream>
#include <vector>
#include "helper_ll.h"


Node* removeNthFromEnd(Node* head, int n) {
    if(!head) return head;

    // get count of nodes
    Node* curr = head;
    int len = 0;
    while (curr) {
        
        // cout << curr->val << endl;
        curr = curr->next;        
        len++;
    }

    int remove_pos = len - n + 1;

    // reset count to zero
    Node dummy (-1);
    dummy.next = head;
    len = 0;
    curr = head;
    Node* prev = &dummy;
    while(curr) {
        len++;
        if(len == remove_pos){
            prev->next = curr->next;
            delete curr;
            break;
        }        
        prev = curr;
        curr = curr->next;
    }
    
    return dummy.next;    
}


Node* removeNthFromEnd2(Node* head, int n) {

    Node dummy(-1);
    dummy.next = head;

    // use fast and slow pointers
    Node* slow = &dummy;
    Node* fast = &dummy;

    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }    

    while(fast->next) {
        slow = slow->next;
        fast = fast->next;        
    }    
    Node* del = slow->next;    
    slow->next = del->next;
    delete del;

    return dummy.next;
}

int main(){
    // vector<int> v ={1, 2, 3, 4, 5};
    // int n = 6;
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

/*
Remove Nth node from the back of the LL

we dont know the size
we can move backwards

approach 1
    iterate thru list to get size
    then iterate till length + 1 - n

    [1,2,3] nth = 1
    [1,2]

approach 2
    fast and slow pointer
    move fast ahead by n spots
    then move both slow and fast
    del = slow->next
    slow->next = del->next
    delete del
*/