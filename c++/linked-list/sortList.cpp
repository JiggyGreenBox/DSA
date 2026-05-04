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
    Node* fast = head;
    Node* prev = nullptr; // needed to prevent infinite loop

    while(fast && fast->next){
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if(prev) prev->next = nullptr;
    return slow;
}

Node* merge(Node* left, Node* right){
    Node* dummy = new Node(-1);    
    Node* prev = dummy;

    while(left && right){
        if(left->val < right->val){
            prev->next = left;
            left = left->next;
        }
        else{
            prev->next = right;
            right = right->next;
        }
        prev = prev->next;
    }
    prev->next = (left) ? left: right;    
    
    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}

Node* sortList(Node* head) {

    // 0. recursive end condition
    //      empty and single node lists
    if(!head || !head->next) return head;

    // 1. find middle
    Node* middle = findMiddle(head);
    
    // 2. sort head, sort middle
    //      recursively
    Node* right = sortList(middle);
    Node* left = sortList(head);        

    // 3. return new head
    Node* newHead = merge(left, right);
    return newHead;
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