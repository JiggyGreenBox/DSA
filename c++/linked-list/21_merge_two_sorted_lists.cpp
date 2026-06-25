#include <iostream>
#include "helper_ll.h"
using namespace std;

Node* mergeTwoLists(Node* a, Node* b) {
    
    Node dummy(-1);
    Node* tail = &dummy;

    while(a && b) {
        if(a->val <= b->val) {
            tail->next = a;
            a = a->next;
        }
        else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    // one of them will be nullptr
    tail->next = (a) ? a : b;    
    
    return dummy.next;    
}


int main(){
    
    vector<int> v1 ={2, 4, 7, 9, 11};
    vector<int> v2 ={1, 2, 5, 6};
    

    Node* head1 = contruct_ll_vec(v1);
    Node* head2 = contruct_ll_vec(v2);
    printLL(head1);
    printLL(head2);

    Node* head = mergeTwoLists(head1, head2);

    printLL(head);
    cleanup_ll(head);
    return 0;
}

/*
Merge two Sorted Lists

Given the heads of two linked lists, list1 and list2, where each 
linked list has its elements sorted in non-decreasing order, merge 
them into a single sorted linked list and return the head of the 
merged linked list.


Example 1

    Input: list1 = head -> 2 -> 4 -> 7 -> 9, list2 = head -> 1 -> 2 -> 5 
    -> 6

    Output: head -> 1 -> 2 -> 2 -> 4 -> 5 -> 6 ->7 -> 9

    Explanation: head -> 1 -> 2 -> 2 -> 4 -> 5 -> 6 ->7 -> 9, the 
    underlined nodes come from list2, the others come from list1.

Example 2

    Input: list1 = head -> 1 -> 2 -> 3 -> 4, list2 = head -> 5 -> 6 -> 10

    Output: head -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 10

    Explanation: head -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 10, the underlined 
    nodes come from list2, the others come from list1.
*/

/*
Both lists are already sorted.

At every step the smallest remaining element
must be either the head of list A or the head
of list B.

Therefore compare the two heads,
append the smaller one,
and advance that list.

Use a dummy node to avoid handling the head
as a special case.
*/