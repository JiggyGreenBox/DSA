#include <iostream>
#include <vector>
#include "helper_ll.h"

Node* addOne1(Node* head){
    if(!head) return head;
    
    // 1. reverse LL
    // 2. add one to last and carry forward carry
    // 3. reverse LL

    // 0. reverse Lambda
    auto reverse = [](Node* h){
        Node *prev = nullptr;
        Node *curr = h;
        while(curr){
            Node *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    };

    // 1. reverse LL
    head = reverse(head);

    // 2. add one to last and carry forward carry
    Node* curr = head;
    Node* prev = nullptr; // this is needed if theres a remaining carry
    // int carry=0;
    int carry = 1;
    while(curr) {
        // this logic adds 1 to each node
        // we only want to add for the first node
        // use carry to add the first 1

        // int sum = curr->val + 1;
        // curr->val = (sum + carry)%10;
        // carry = sum/10;

        int sum = curr->val + carry;        
        curr->val = sum%10;
        carry = sum/10;

        prev = curr;
        curr = curr->next;
    }

    if(carry>0){
        prev->next = new Node(carry);
    }

    // 3. reverse LL
    head = reverse(head);

    return head;
}

void recursive_add(Node* node, int& carry){
    if(!node) return;    

    recursive_add(node->next, carry);

    int sum = node->val + carry;
    node->val = sum%10;
    carry = sum/10;
}

Node* addOne2(Node* head){
    // recursive
    int carry = 1; // first add
    recursive_add(head, carry);
    if(carry > 0){
        Node* newHead = new Node(carry);
        newHead->next = head;
        return newHead;
    }
    return head;
}

// rightmost non 9
// least amounf of work
// 2 pass without reverse
Node* addOne3(Node* head){
    if(!head) return head;
    // 1,2,9,9,9
    // 1,3,0,0,0
    // find rightmost non-9 number
    // incement, make every element to the right = 0

    Node* right_most_non_9 = nullptr;
    Node* curr = head;

    while(curr){
        if(curr->val != 9){
            right_most_non_9 = curr;
        }
        curr = curr->next;
    }

    // edge case
    if(right_most_non_9 == nullptr){
        Node* newHead = new Node(1);
        newHead->next = head;

        head = newHead;     // for return
        curr = head->next;  // for 0 assignment
    }
    else{
        right_most_non_9->val += 1;
        curr = right_most_non_9->next;  // for 0 assignment
    }
    
    
    while(curr) {
        curr->val = 0;
        curr = curr->next;
    }
    return head;
}

// lets use for loops
// instead of while loops
Node* addOne4(Node* head){
    if(!head) return head;

    Node* lastNonNine = nullptr;

    // find last (rightmost) nonNine
    for(Node* n = head; n; n = n->next) {
        if(n->val != 9) lastNonNine = n;
    }

    if(lastNonNine == nullptr){
        Node* newHead = new Node(1, head);        
        for(Node* n = head; n; n = n->next) n->val = 0;        
        return newHead;
    }
    
    lastNonNine->val += 1;
    for(Node* n = lastNonNine->next; n; n = n->next) n->val = 0;        
    return head;
}

int main(){
    vector<int> v ={9,9};
    // vector<int> v ={0};
    // vector<int> v ={9,9,9,9,9};
    // vector<int> v ={1,2,3};
    
    Node* head = contruct_ll_vec(v);
    printLL(head);
    head = addOne4(head);    
    printLL(head);
    cleanup_ll(head);
    return 0;
}