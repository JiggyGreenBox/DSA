#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node
{
    int val;
    Node *next;
    Node *random;
    Node()
    {
        val = 0;
        next = NULL;
        random = NULL;
    }
    Node(int data1)
    {
        val = data1;
        next = NULL;
        random = NULL;
    }
    Node(int data1, Node *next1, Node* r)
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

Node* copyRandomList(Node* head) {

    if (!head)
        return nullptr;

    // Pass 1: Insert copy nodes
    Node* curr = head;

    while (curr) {
        Node* copy = new Node(curr->val);

        copy->next = curr->next;
        curr->next = copy;

        curr = copy->next;
    }

    // Pass 2: Random pointers
    curr = head;

    while (curr) {
        if (curr->random)
            curr->next->random = curr->random->next;

        curr = curr->next->next;
    }

    // Pass 3: Separate lists
    curr = head;
    Node* copyHead = head->next;

    while (curr) {
        Node* copy = curr->next;

        curr->next = copy->next;

        if (copy->next)
            copy->next = copy->next->next;

        curr = curr->next;
    }

    return copyHead;
}

Node* copyRandomList(Node* head) {

    if (!head)
        return nullptr;

    unordered_map<Node*, Node*> mp;

    // Pass 1: Create clone nodes
    Node* curr = head;

    while (curr) {
        mp[curr] = new Node(curr->val);
        curr = curr->next;
    }

    // Pass 2: Connect next and random
    curr = head;

    while (curr) {

        mp[curr]->next =
            curr->next ? mp[curr->next] : nullptr;

        mp[curr]->random =
            curr->random ? mp[curr->random] : nullptr;

        curr = curr->next;
    }

    return mp[head];
}


int main() {
    return 0;
}