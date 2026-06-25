#include <iostream>
#include <vector>
using namespace std;

/*
Flattening of LL

Given a special linked list containing n head nodes where every node 
in the linked list contains two pointers:

‘Next’ points to the next node in the list
‘Child’ pointer to a linked list where the current node is the 
head
Each of these child linked lists is in sorted order and connected by 
a 'child' pointer.

Flatten this linked list such that all nodes appear in a single 
sorted layer connected by the 'child' pointer and return the head of 
the modified list.
*/

/*
we can merge the sorted lists into 1 list
l →  l → l
↓    ↓   ↓ 
c    c   c
↓    ↓   ↓ 
c    c   c

head = ...
while(l->next)
    merge2lists(l, l-next)

return head
*/

/*
merge code
    merge(a, b)        

flatten 
    if no head or single node
        return head

    head->next = flatten(head->next); recursively return a single list list

    return merge(head, head->next) merge it
*/

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *child;
    ListNode()
    {
        val = 0;
        next = NULL;
        child = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
        child = NULL;
    }
    ListNode(int data1, ListNode *next1, ListNode* next2)
    {
        val = data1;
        next = next1;
        child = next1;
    }
};

ListNode* merge(ListNode* a, ListNode* b) {

    ListNode dummy(-1);
    ListNode* tail = &dummy;

    while(a && b) {

        if(a->val <= b->val) {
            tail->child = a;
            a = a->child;
        }
        else {
            tail->child = b;
            b = b->child;
        }

        tail = tail->child;
        tail->next = nullptr;
    }

    tail->child = a ? a : b;

    return dummy.child;
}


ListNode* flatten(ListNode* head) {

    if(!head || !head->next)
        return head;

    head->next = flatten(head->next);

    return merge(head, head->next);
}

int main() {
    return 0;
}