#include <iostream>
#include <vector>
#include "helper_ll.h"
using namespace std;
using ListNode = Node;

/*

Detect a loop in LL

approach 1 
    we can use unordered_set to store pointers
        if we find any repeat pointer before nullptr
            loop found
approach 2
    fast and slow pointer
        make fast move 2 places, slow 1 place
        they will meet

    whats the math for fast meeting slow?
*/

bool hasCycle(ListNode* head) {

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {

        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}

int main() {
    return 0;
}