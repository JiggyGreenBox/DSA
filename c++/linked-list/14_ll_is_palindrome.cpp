#include <iostream>
#include <vector>
#include <stack>
#include "helper_ll.h"
using namespace std;

Node* reverseLL(Node *head){
    Node* prev = nullptr;
    Node* curr = head;
    while(curr){
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;        
        curr = next;
    }
    return prev;
}

bool isPalindrome_vector(Node *head) {

    Node* curr = head;
    vector<int> vals;
    while(curr){
        vals.push_back(curr->val);
        curr = curr->next;
    }

    int i = 0;
    int j = vals.size()-1;
    while(i<j){
        if(vals[i++] != vals[j--]) return false;
    }
    return true;
}


bool isPalindrome_stack(Node *head) {
    std::stack<int> st;
    Node* curr = head;
    while(curr){
        st.push(curr->val);
        curr = curr->next;
    }

    curr = head;
    while(curr){
        if(curr->val != st.top()) return false;
        st.pop();
        curr = curr->next;
    }
    return true;
}

bool isPalindrome_reverse(Node *head){
    if(!head || !head->next) 
        return true;
    
    // find end of half
    Node* slow = head;
    Node* fast = head;
    while(fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    

    // Reverse second half
    Node* prev = nullptr;
    Node* curr = slow->next;

    while(curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // Compare halves
    Node* first = head;
    Node* second = prev;
    
    while(second) {
        if(first->val != second->val)
            return false;

        first = first->next;
        second = second->next;
    }

    // optional, reverse back
    prev = nullptr;
    curr = slow->next;
    while(curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return true;
}

bool isPalindrome(Node* head) {

    if (!head || !head->next)
        return true;

    // 1. Find middle
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // For odd length, skip the middle node
    if (fast)
        slow = slow->next;

    // 2. Reverse second half
    Node* prev = nullptr;
    Node* curr = slow;

    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // prev = head of reversed second half

    // 3. Compare
    Node* left = head;
    Node* right = prev;

    while (right) {
        if (left->val != right->val)
            return false;

        left = left->next;
        right = right->next;
    }

    return true;
}

int main(){
    // vector<int> v = {1, 2, 3, 4, 5};
    // vector<int> v = {3, 8, 7, 1, 3};
    vector<int> v = {1,2,3,2};
    // vector<int> v = {1,2};
    // vector<int> v = {1,2,3};
    
    Node* head = contruct_ll_vec(v);
    printLL(head);
    // bool pal = isPalindrome_vector(head);
    bool pal = isPalindrome_reverse(head);
    

    if(pal) cout << "is palindrome" << endl;
    else  cout << "NOT palindrome" << endl;

    cleanup_ll(head);
    return 0;
}

/*
Approach 1:
    Vector
    O(N) space

Can optimize.

Approach 2:
    Reverse second half
    O(1) space
*/

/*

for a vector we can compare [start++, end--] to find a palindrome

for linked list we dont have access to the back/end

so we find the middle,reverse and check

1,2,2,1         need to reverse [1,2,1,2] and check

1,2,3,2,1       need to reverse [1,2,3,1,2]

different for odd and even
    normal iteration middle node
        while fast && fast->next

        odd
        1 2 3 2 1
            s   f

        even
        1 2 2 1
            s
               f
        for odd standard loop correct, for odd one node ahead

        FIX:
        We stop one iteration earlier.
            standard loop, can i move fast one step ahead
        can i move 2 steps ahead

        while(fast->next && fast->next->next)

        1 2 3 2 1
            s 
                f

        1 2 2 1
          s
            f

        now for both reverse from s->next
    
*/