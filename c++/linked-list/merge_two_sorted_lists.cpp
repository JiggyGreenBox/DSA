#include <iostream>
#include "helper_ll.h"
using namespace std;


Node* mergeTwoLists(Node* list1, Node* list2) {
    
    Node* dummy = new Node(-1);
    Node* curr_merged = dummy;

    Node* curr1 = list1;
    Node* curr2 = list2;

    while(curr1 && curr2) {

        if(curr1->val < curr2->val) {

            curr_merged->next = curr1;
            curr1 = curr1->next;

        }

        else {

            curr_merged->next = curr2;
            curr2 = curr2->next;
        }
        curr_merged = curr_merged->next;
    }

    while(curr1) {
        curr_merged->next = curr1;
        curr1 = curr1->next;
        curr_merged = curr_merged->next;
    }

    while(curr2) {
        curr_merged->next = curr2;
        curr2 = curr2->next;
        curr_merged = curr_merged->next;
    }

    // newHead
    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}

Node* mergeTwoLists2(Node* list1, Node* list2) {
    
    Node* dummy = new Node(-1);
    Node* tail = dummy;

    Node* curr1 = list1;
    Node* curr2 = list2;

    while(curr1 && curr2) {
        if(curr1->val < curr2->val) {
            tail->next = curr1;
            curr1 = curr1->next;
        }
        else {
            tail->next = curr2;
            curr2 = curr2->next;
        }
        tail = tail->next;
    }

    // one of them will be nullptr
    tail->next = (curr1) ? curr1 : curr2;    

    // newHead
    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}


int main(){
    
    vector<int> v1 ={2, 4, 7, 9, 11};
    vector<int> v2 ={1, 2, 5, 6};
    

    Node* head1 = contruct_ll_vec(v1);
    Node* head2 = contruct_ll_vec(v2);
    printLL(head1);
    printLL(head2);

    Node* head = mergeTwoLists2(head1, head2);

    printLL(head);
    cleanup_ll(head);
    return 0;
}