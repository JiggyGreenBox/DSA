#include <iostream>
#include <vector>
#include "helper_ll.h"


Node* reverseList(Node* head, int left, int right) {
    if (!head || left == right)
        return head;

    Node dummy(-1);
    dummy.next = head;

    // 1. Find the node immediately before position left.
    Node* before = &dummy;

    for (int i = 1; i < left; i++) {
        before = before->next;
    }

    // 2. Reverse the sublist, connecting its tail
    //    directly to the suffix.
    Node* curr = before->next;
    Node* prev = nullptr;

    Node* sublist_tail = curr;

    for (int i = 0; i < right - left + 1; i++) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // 3. Reconnect the prefix and suffix.
    before->next = prev;
    sublist_tail->next = curr;

    return dummy.next;
}

Node* reverseList(Node* head, int left, int right) {
    Node dummy(-1);
    dummy.next = head;

    Node* left_node = &dummy;
    Node* right_node = &dummy;

    int counter = 0;
    while(left_node && right_node) {
        counter++;
        if(counter < left)
            left_node = left_node->next;

        if(counter <= right)
            right_node = right_node->next;
        else
            break;
    }
    
    // reverse every node from
    // [left->next to right]
    // 1-> 2,3,4 -> 5
    // 1-> 4,3,2 -> 5

    // Reverse current group
    // ListNode* prev = groupNext;
    // ListNode* curr = groupPrev->next;


    Node* groupNext = right_node->next;
    Node* prev = groupNext;
    Node* curr = left_node->next;
    

    while(curr != groupNext) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }   
    
    // reconnect
    left_node->next = prev;
    
    return dummy.next;
}