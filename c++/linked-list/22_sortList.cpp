#include "helper_ll.h"
using namespace std;


// 5 4 3 2 1
// [5 4 3] [2 1]
// [5 4] [3]    [2] [1]
// [5] [4]    [3]       [2][1]
// merge (5,4)-> [4 5]  merge (2,1)-> [1 2]  
// merge (4,3)-> [3 4 5]
// merge (3,1)-> [1 2 3 4 5]

Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head->next;    

    while(fast && fast->next) {        
        slow = slow->next;
        fast = fast->next->next;
    }    
    return slow;
}

Node* merge(Node* a, Node* b) {
    Node dummy(-1);    
    Node* tail = &dummy;

    while(a && b){
        if(a->val <= b->val) {
            tail->next = a;
            a = a->next;
        }
        else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = (a) ? a: b;    
    
    return dummy.next;
}

Node* sortList(Node* head) {

    if(!head || !head->next) 
        return head;
    
    Node* mid = findMiddle(head);
        
    Node* right = mid->next;
    mid->next = nullptr;

    Node* left = head;

    Node* left = sortList(left);
    Node* right = sortList(right);
    
    return merge(left, right);    
}

int main(){
    vector<int> v ={6, 5, 4, 3, 2, 1};
    
    Node* head = contruct_ll_vec(v);
    printLL(head);
    head = sortList(head);    
    printLL(head);
    cleanup_ll(head);
    return 0;
}

/*
Sort Linked List

Merge Sort

1. Find middle (slow/fast)
2. Split:
       mid->next = nullptr
3. Sort left
4. Sort right
5. Merge two sorted lists

Base:
    0 or 1 node => already sorted

Time:
    O(n log n)

Space:
    O(log n)
*/