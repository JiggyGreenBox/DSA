#include <iostream>
#include <vector>
#include "helper_ll.h"
using namespace std;

/*
Find the intersection point of Y LL

Given the heads of two linked lists A and B, containing positive 
integers. Find the node at which the two linked lists intersect. If 
they do intersect, return the node at which the intersection begins, 
otherwise return null.


The Linked List will not contain any cycles. The linked lists must 
retain their original structure, given as per the input, after the 
function returns.

*/

/*
Find the intersection point of Y LL

approach 1 
    use a unordered_set<Node*>
        loop L1
        loop L2
            if found return node

approach 2
    get len of list1 and len of list2

    put pointer diff steps ahead
    loop and check if equal

approach 3

    How do we derive the famous:
        p1 = p1 ? p1->next : headB;
        p2 = p2 ? p2->next : headA;

    Start From Approach 2
    I need both pointers to have the same remaining distance.

    A length = 8
    B length = 5
        diff = 3
            So we manually skip 3 nodes.

    Can I equalize their path lengths automatically?
        A = a + c
        B = b + c

            a = unique part of A
            b = unique part of B
            c = common tail

            A: 1 -> 2 -> 3 -> 8 -> 9
                a=3

            B: 4 -> 5 -> 8 -> 9
                b=2

            Common:
                8 -> 9
            c=2

        pointer 1:
            (a+c) + (b+c)
                = a + b + 2c

        pointer 2:
            (b+c) + (a+c)
                = b + a + 2c

         == same distance
*/



// aproach 2
int getLength(Node* head) {

    int len = 0;

    while (head) {
        len++;
        head = head->next;
    }

    return len;
}

Node* getIntersectionNode(Node* headA,
                              Node* headB) {

    int lenA = getLength(headA);
    int lenB = getLength(headB);

    Node* p1 = headA;
    Node* p2 = headB;

    int diff = abs(lenA - lenB);

    if (lenA > lenB) {
        while (diff--)
            p1 = p1->next;
    } else {
        while (diff--)
            p2 = p2->next;
    }

    // if (lenA > lenB) {

    //     int diff = lenA - lenB;

    //     while (diff--) {
    //         p1 = p1->next;
    //     }

    // } else {

    //     int diff = lenB - lenA;

    //     while (diff--) {
    //         p2 = p2->next;
    //     }
    // }

    while (p1 && p2) {

        if (p1 == p2)
            return p1;

        p1 = p1->next;
        p2 = p2->next;
    }

    return nullptr;
}


// approach 3
Node* getIntersectionNode(Node* headA,
                              Node* headB) {

    Node* p1 = headA;
    Node* p2 = headB;

    while (p1 != p2) {

        p1 = p1 ? p1->next : headB;
        p2 = p2 ? p2->next : headA;
    }

    return p1;
}

int main() {
    return 0;
}