#include <iostream>
#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *prev;
    ListNode()
    {
        val = 0;
        next = NULL;
        prev = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
        prev = NULL;
    }
    ListNode(int data1, ListNode *next1, ListNode *prev1)
    {
        val = data1;
        next = next1;
        prev = prev1;
    }
};

// Helper function to create a new node
ListNode* newNode(int data) {
    ListNode* node = new ListNode(data);
    return node;
}

/*

Remove duplicates from sorted DLL

curr = head

while(curr) {
    next = curr->next
    if(curr->val == next->val)
        prev = curr->prev
        
        if(prev)
            prev->next = next
        else
            prev = head

        if(next)
            next->prev = prev
    
        delete curr        
    curr = next    
}

*/

ListNode* removeDuplicates(ListNode *head) {

    if(!head || !head->next)
        return head;

    ListNode* curr = head;
    while(curr) {
        ListNode *next = curr->next;

        if(next && curr->val == next->val) {
            ListNode *prev = curr->prev;

            if(prev)
                prev->next = next;
            else
                head = next;

            next->prev = prev;
            
            delete curr;
        }

        curr = next;
    }
    return head;
}

// CODE IS CORRECT BUT NOT CANONICAL

ListNode* removeDuplicates_canon(ListNode* head) {

    if(!head)
        return head;

    ListNode* curr = head;

    while(curr && curr->next) {

        if(curr->val == curr->next->val) {

            ListNode* del = curr->next;

            curr->next = del->next;

            if(del->next)
                del->next->prev = curr;

            delete del;
        }
        else {
            curr = curr->next;
        }
    }

    return head;
}

// Function to print doubly linked list
void printList(ListNode* head) {
    ListNode* temp = head;
    while (temp != NULL) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {

    // Creating doubly linked list
    // Creating a sorted doubly linked list:
    ListNode* head = newNode(1);
    head->next = newNode(2);
    head->next->prev = head;
    head->next->next = newNode(2);
    head->next->next->prev = head->next;
    head->next->next->next = newNode(3);
    head->next->next->next->prev = head->next->next;
    head->next->next->next->next = newNode(4);
    head->next->next->next->next->prev = head->next->next->next;
    head->next->next->next->next->next = newNode(4);
    head->next->next->next->next->next->prev = head->next->next->next->next;
    head->next->next->next->next->next->next = newNode(5);
    head->next->next->next->next->next->next->prev = head->next->next->next->next->next;

    printList(head);
    head = removeDuplicates(head);
    printList(head);

    return 0;
}