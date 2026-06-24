#include <iostream>
#include <vector>
using namespace std;

/*

Add two numbers in Linked List

Given two non-empty linked lists linkedList1 and linkedList2 which 
represent two non-negative integers.

The digits are stored in reverse order with each node storing one 
digit.

Add two numbers and return the sum as a linked list.

The sum Linked List will be in reverse order as well.

The Two given Linked Lists represent numbers without any leading 
zeros, except when the number is zero itself

*/

/*
[9,9]
[1]

if both empty return nullptr
int carry = 0

Node dummy(-1);
Node* tail = &dummy

use a single loop for l1, l2, and carry

int carry = 0

while(l1 || l2 || carry)
    int sum = carry

    if(l1) {
        sum += l1->val
        l1 = l1->next
    }

    if(l2) {
        sum += l2->val
        l2 = l2->next
    }

    carry = sum / 10;

    tail->next = new ListNode(sum % 10);
    tail = tail->next;


return dummy.next
*/

struct ListNode {
    int data;
    ListNode* next;
    ListNode() : data(0), next(nullptr) {}
    ListNode(int v) : data(v), next(nullptr) {}
    ListNode(int v, ListNode *n) : data(v), next(n) {}
};


ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

    ListNode dummy(0);
    ListNode* tail = &dummy;

    int carry = 0;

    while (l1 || l2 || carry) {

        int sum = carry;

        if (l1) {
            sum += l1->data;
            l1 = l1->next;
        }

        if (l2) {
            sum += l2->data;
            l2 = l2->next;
        }

        carry = sum / 10;

        tail->next = new ListNode(sum % 10);
        tail = tail->next;
    }

    return dummy.next;
}

int main() {
    return 0;
}