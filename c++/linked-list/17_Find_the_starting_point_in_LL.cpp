#include <iostream>
#include <vector>
#include "helper_ll.h"
using ListNode = Node;
using namespace std;

/*
Find the starting point in LL

    Given the head of a singly linked list, the task is to find the 
    starting point of a loop in the linked list if it exists. Return the 
    starting node if a loop exists; otherwise, return null.

    A loop exists in a linked list if some node in the list can be 
    reached again by continuously following the next pointer. Internally, 
    pos denotes the index (0-based) of the node from where the loop 
    starts.
*/

/*
Find the starting point in LL
1 → 2 → 3
    ↑   ↓
    7   4
    ↑   ↓
    6 ← 5

we know fast and slow pointers
    fast 2 steps
    slow 1 step

    they will meet at n % n*2 == 0?
    so keep a track of total steps - n?

    n %n*2 == 0 will be true only for the loop section not the total section
*/

/*
Derivation

    1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
              ^                   |
              |___________________|

    x = distance from head to cycle start
    y = distance from cycle start to meeting point
    L = cycle length


    x = 2   (1->2->3)        head -> cycle start
    y = 3   (3->4->5->6)     cycle start -> meeting point
    L = 5   (3,4,5,6,7)

    after moving fast and slow, they meet at 6
        slow steps = S
        fast steps = 2S

    fast has taken more than or 1 loop to reach
        2S = S + nL
            for n >= 1

        S = nL   ...(1)

    slow 
        has travelled x + y + mL
        S = x + y + mL  ...(2)

    using (1) and (2)
        nL = x + y + mL
        x + y = (m-n)L   ...(k=m-n)

        x + y = kL

        x = kL - y        

        x = kL - y
        = (k-1)L + (L-y)   [some complete loops, and a partial L-y distance]

        L-y is the distance from the meeting point
        to the cycle start.

        Therefore x steps from the meeting point
        consists of:

            some complete loops
            + distance to cycle start

        Place:

            p1 at head
            p2 at meeting point

        Move both one step at a time.

        After x steps:

            p1 reaches cycle start

            p2 has traversed complete loops
            and also reaches cycle start

        Hence they meet at the start of the cycle.


        distance(head,start)
        ≡
        distance(meeting,start)
        (mod cycle length)


    1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
              ^                   |
              |___________________|

    distance is edges or next operations
    x = 2
    y = 3 (to 6 meeting point)
    L = 5

    x + y = nL
    2 + 3 = 1*5

    x = 2
    L-y = 2, k=1
        but k can be greater than 1


    another example
        x = 12
        L = 5
        y = 3

    x = nL - y
    12  = n*5 - 3
        n = 3
    
*/

/*

x = kL - y
(x % L) = (kL % L) - (y % L)

x % L = 0 - y % L
x % L = - y % L

    y < L so -y%L = L-y


so
x%L = L-y

Therefore after x steps:

- the pointer from head reaches the cycle start
  (by definition of x)

- the pointer from the meeting point (y) moves
  x mod L = L-y positions around the cycle,
  which lands it at the cycle start (L)

Hence both pointers meet at the cycle start.

    3 -> 4 -> 5 -> 6 -> 7
    ^                   |
    |___________________|

    cycle start = 3
    meeting = 6

    L = 5
    y = 3
    -----------
    L-y = 2
        6 -> 7 -> 3 from (y,6)

*/

ListNode *findStartingPoint(ListNode *head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast) {
            slow = head;
            while(slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return nullptr; // no cycle
}

int main() {
    return 0;
}