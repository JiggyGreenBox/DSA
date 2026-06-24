#include <iostream>
#include <vector>
using namespace std;

/*
Segregate odd and even nodes in Linked List

    Given the head of a singly linked list. Group all the nodes with odd 
    indices followed by all the nodes with even indices and return the 
    reordered list.

    Consider the 1st node to have index 1 and so on. The relative order 
    of the elements inside the odd and even group must remain the same as 
    the given input.


    Example 1
        Input: linkedList = [1, 2, 3, 4, 5]
        Output: [1, 3, 5, 2, 4]
        Explanation:
        The nodes with odd indices are 1, 3, 5 and the ones with even indices 
        are 2, 4.

    Example 2
        Input: linkedList = [4, 3, 2, 1]
        Output: [4, 2, 3, 1]
        Explanation:
        The nodes with odd indices are 4, 2 and the ones with even indices 
        are 3, 1.

*/

/*

[4, 3, 2, 1]

we skip nodes

odd = head
even = head->next
evenHead = even

[1,2,3,4,5]
odd=1
even=2

while(even && even->next)
    odd->next = even->next [1,3,5]
    odd = odd->next // skip 5

    even->next = odd->next [2,4,nullptr]
    even = even->next [nullptr]

odd->next = evenHead

return head                                             

*/                                                                      

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int v) : val(v), next(nullptr) {}
    ListNode(int v, ListNode *n) : val(v), next(n) {}
};

ListNode* oddEvenList(ListNode* head) {

    if (!head || !head->next)
        return head;

    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* evenHead = even;

    while (even && even->next) {

        odd->next = even->next;
        odd = odd->next;

        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead;

    return head;
}

int main() {
    return 0;
}