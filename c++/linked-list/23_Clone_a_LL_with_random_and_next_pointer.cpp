#include <iostream>
#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *random;
    ListNode()
    {
        val = 0;
        next = NULL;
        random = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
        random = NULL;
    }
    ListNode(int data1, ListNode *next1, ListNode* r)
    {
        val = data1;
        next = next1;
        random = r;
    }
};

/*
Clone a LL with random and next pointer

Given the head of a special linked list of n nodes where each node 
contains an additional pointer called 'random' which can point to any 
node in the list or null.

Construct a deep copy of the linked list where,

    n new nodes are created with corresponding values as original linked 
    list.
    The random pointers point to the corresponding new nodes as per their 
    arrangement in the original list.
    Return the head of the newly constructed linked list.

*/    

/*
how to clone a normal linked list?

f(head):
    curr = head
    prev = dummy

    while(curr)
        copy = new Node(curr->val)
        prev->next = copy
        curr = curr->next
    return dummy.next

now that we have random pointers, how do we construct them?


What prevents me from setting random?
    I don't know which copied node corresponds
    to a given original node.

    original node -> copied node
    copy->random = ?

        unordered_map<Original*, Copy*>

    2 pass
    1st
        Clone nodes and store mapping.
    2nd
        copy->random = map[original->random];
*/


int main() {
    return 0;
}