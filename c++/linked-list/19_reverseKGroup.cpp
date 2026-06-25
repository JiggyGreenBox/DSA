#include <iostream>
#include <vector>
#include "helper_ll.h"
using namespace std;
using ListNode = Node;

/*
Reverse K Group

Dummy node

Invariant:
    groupPrev -> [k nodes] -> groupNext

Find:
    kth = last node of current group
    groupNext = kth->next

Reverse:
    [groupPrev->next ... kth]

    prev = groupNext
    curr = groupPrev->next

    while(curr != groupNext)
        reverse pointers

Reconnect:
    oldStart = groupPrev->next   // becomes new tail

    groupPrev->next = kth        // new head
    groupPrev = oldStart         // next group's prev

Picture:

Before:
    groupPrev -> 1 -> 2 -> 3 -> groupNext
                   ^         ^
                start       kth

After:
    groupPrev -> 3 -> 2 -> 1 -> groupNext

    oldStart = 1
    groupPrev = 1
*/

ListNode* reverseKGroup(ListNode* head, int k) {

    ListNode dummy(0);
    dummy.next = head;

    ListNode* groupPrev = &dummy;

    while (true) {

        // Find kth node from groupPrev
        ListNode* kth = groupPrev;
        for (int i = 0; i < k; i++) {
            kth = kth->next;
            if (!kth)
                return dummy.next;
        }

        ListNode* groupNext = kth->next;

        // Reverse current group
        ListNode* prev = groupNext;
        ListNode* curr = groupPrev->next;

        while (curr != groupNext) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // Reconnect
        ListNode* oldStart = groupPrev->next;

        groupPrev->next = kth;
        groupPrev = oldStart;
    }
}


int main() {
    ListNode *head = contruct_ll_vec({1,2,3,4,5});
    printLL(head);
    head = reverseKGroup(head, 2);
    printLL(head);
    cleanup_ll(head);
    return 0;
}
