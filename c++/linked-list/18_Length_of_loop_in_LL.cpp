#include <iostream>
#include <vector>
#include "helper_ll.h"
using namespace std;
/*
Length of loop in LL

Given the head of a singly linked list, find the length of the loop 
in the linked list if it exists. Return the length of the loop if it 
exists; otherwise, return 0.

*/

int lengthOfLoop(Node* head) {

    Node* slow = head;
    Node* fast = head;

    while(fast && fast->next) {

        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast) {

            int len = 1;
            Node* curr = slow->next;

            while(curr != slow) {
                len++;
                curr = curr->next;
            }

            return len;
        }
    }

    return 0;
}

int main() {
    return 0;
}