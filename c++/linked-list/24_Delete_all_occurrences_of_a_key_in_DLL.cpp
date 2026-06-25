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

Delete all occurrences of a key in DLL

curr = head

while(curr) {
    next = curr->next
    if(curr->val == target)
        prev = curr->prev
        

        if(prev)
            prev->next = next
        else
            prev = head

        if(next)
            next->prev = prev
    
        Node del = curr
        delete del
    curr = next    
}

*/

ListNode *deleteAllOccurrences(ListNode* head, int target) {

    if(!head) 
        return head;

    ListNode* curr = head;
    while(curr) {

        ListNode* next = curr->next;
        
        if(curr->val == target) {
            ListNode* prev = curr->prev;

            if(prev)
                prev->next = next;
            else
                head = next;

            if(next)
                next->prev = prev;

            // ListNode* del = curr;
            // delete del;
            delete curr;
        }
        curr = next;
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
    ListNode* head = newNode(1);
    head->next = newNode(2);
    head->next->prev = head;
    head->next->next = newNode(3);
    head->next->next->prev = head->next;
    head->next->next->next = newNode(2);
    head->next->next->next->prev = head->next->next;
    head->next->next->next->next = newNode(4);
    head->next->next->next->next->prev = head->next->next->next;
    head->next->next->next->next->next = newNode(2);
    head->next->next->next->next->next->prev = head->next->next->next->next;
    head->next->next->next->next->next->next = newNode(5);
    head->next->next->next->next->next->next->prev = head->next->next->next->next->next;    

    printList(head);
    head = deleteAllOccurrences(head, 2);
    printList(head);

    return 0;
}