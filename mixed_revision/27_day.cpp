/*
============================================
oct 21
    last oct 10
============================================
Linked List revision
============================================

Problem 1 — Remove Nth Node From End of List
Given the head of a singly linked list, remove the n-th node from 
the end and return the head.

approach
    we want nth from the back to be deleted
    so we look for the n-1th node
    then the next node will be deleted

    we can use a slow and fast pointer
    keep fast n-1 places ahead of first node

complexity
    O(n) time
    O(1) space 

Node* removeNth(Node* head, int k) {

    if(!head || k <= 0)
        return head;

    Node dummy(-1);
    dummy.next = head;

    Node* slow = &dummy;
    Node* fast = &dummy;

    for(int i=0; i<k; i++) {
        fast = fast->next;
        if(!fast)
            return head; // k was too large
    }

    while(fast->next) {
        slow = slow->next;
        fast = fast->next;
    }

    Node* del = slow->next;
    slow->next = del->next;
    delete del;

    return dummy.next;
}
=============================================

Reverse Linked List II — LeetCode 92
Problem statement

Given the head of a singly linked list and two integers, left and 
right, where left <= right, reverse the nodes of the list from 
position left to position right, inclusive, and return the reversed 
list.

Positions are 1-indexed.

Input:  head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]


Approach 
    use the given idx to find reversal nodes
    then perform the reversal

Node* reverseList(Node* head, int left, int right) {
    Node dummy(-1);
    dummy.next = head;

    Node* left_node = &dummy;
    Node* right_node = &dummy;

    int counter = 0;
    while(left_node && right_node) {
        counter++;
        if(counter < left)
            left_node = left_node->next;

        if(counter <= right)
            right_node = right_node->next;
        else
            break;
    }
    
    // reverse every node from
    // [left->next to right]
    // 1-> 2,3,4 -> 5
    // 1-> 4,3,2 -> 5

    // Reverse current group
    // ListNode* prev = groupNext;
    // ListNode* curr = groupPrev->next;


    Node* groupNext = right_node->next;
    Node* prev = groupNext;
    Node* curr = left_node->next;
    

    while(curr != groupNext) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }   
    
    // reconnect
    left_node->next = prev;
    
    return dummy.next;
}

=================================================

Linked List Cycle II

Transfer / derivation

Return the node where a cycle begins, not merely whether a cycle 
exists. Explain why the two-pointer method finds that node.

approach 
    we use a 2 pointer method
    f 2 moves
    s 1 moves

    if a cycle exists
        they meet

    let x be the dist travelled before the cycle start
    y be the cycle start till meeting point

    then

    2*slow = fast
    fast has travelled nL where n>=1

    S = F
    F = nl
    S = nL

    s is also at the meeting point
    x+y = S

    x + y = nL

    x = nL - y
    x = (n-1)L + L-y

    if we place a pointer at x/head
    and another at y
    if we move them ahead by x places
    they will meet at the meeting point

*/
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node *next;
    Node(int n) :val(n), next(nullptr) {}
};

Node* cycle(Node* head) {
    if(!head)
        return head;

    Node* slow = head;
    Node* fast = head;

    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        // cycle found
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


Node* constructLL(const vector<int> &nums) {
    if(nums.empty())    
        return nullptr;

    Node* head = new Node(nums[0]);
    Node* tail = head;

    for(int i=1; i<nums.size(); i++) {
        tail->next = new Node(nums[i]);
        tail = tail->next;
    }
    return head;
}

Node* getNode(Node* head, int k) {
    Node dummy(-1);
    dummy.next = head;
    Node* curr = &dummy;

    int i = 0 ;
    while(curr && i<k) {
        i++;
        curr = curr->next;
    }
    return curr;
}


int main() {

    Node* head = constructLL({1,2,3,4,5});    
    Node* n1 = getNode(head, 3);
    Node* n2 = getNode(head, 5);
    n2->next = n1; // create cycle
    Node* cycleStart = cycle(head);

    return 0;
}

