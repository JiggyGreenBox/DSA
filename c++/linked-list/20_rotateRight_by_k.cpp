#include <iostream>
#include "helper_ll.h"
using namespace std;

Node* rotateRight(Node* head, int k) {

    if(!head || !head->next || k == 0)
        return head;

    // 1. Find length and tail
    int n = 1;
    Node* tail = head;

    while(tail->next) {
        tail = tail->next;
        n++;
    }

    // 2. Normalize k
    k = k % n;

    if(k == 0)
        return head;

    // 3. Make circular
    tail->next = head;

    // 4. Find new tail
    // new tail position = n-k-1 from head
    int steps = n - k;

    while(steps--) {
        tail = tail->next;
    }

    // 5. Break cycle
    Node* newHead = tail->next;
    tail->next = nullptr;

    return newHead;
}

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    int k = 2;

    Node* head = contruct_ll_vec(v);
    printLL(head);

    head = rotateRight(head, k);

    printLL(head);
    cleanup_ll(head);
    return 0;
}

/*
Rotate a LL

Given the head of a singly linked list containing integers, shift the 
elements of the linked list to the right by k places and return the 
head of the modified list. Do not change the values of the nodes, 
only change the links between nodes.

Example 1
    Input:  head -> 1 -> 2 -> 3 -> 4 -> 5, k = 2
    Output: head -> 4 -> 5 -> 1 -> 2 -> 3
    Explanation:
    List after 1 shift to right: head -> 5 -> 1 -> 2 -> 3 -> 4.
    List after 2 shift to right: head -> 4 -> 5 -> 1 -> 2 -> 3.

Example 2
    Input:  head -> 1 -> 2 -> 3 -> 4 -> 5, k = 4
    Output: head -> 2 -> 3 -> 4 -> 5 -> 1
    Explanation:
    List after 1 shift to right: head -> 5 -> 1 -> 2 -> 3 -> 4.
    List after 2 shift to right: head -> 4 -> 5 -> 1 -> 2 -> 3.
    List after 3 shift to right: head -> 3 -> 4 -> 5 -> 1 -> 2.
    List after 4 shift to right: head -> 2 -> 3 -> 4 -> 5 -> 1.
*/


/*
Rotate Right by k

1. Find n and tail
2. k %= n
3. Make circle
4. New tail = node (n-k-1)
5. New head = newTail->next
6. Break circle
*/