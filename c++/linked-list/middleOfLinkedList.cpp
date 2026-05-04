#include <iostream>
#include <vector>
#include "helper_ll.h"
using namespace std;

Node* middleOfLinkedList(Node* head){
    if(!head) return head;

    Node* slow = head;
    Node* fast = head;

    while(fast && fast->next){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

int main(){
    // vector<int> v = {2, 9, 1, 4, 0, 4};
    // vector<int> v = {3, 8, 7, 1, 3};
    // vector<int> v = {1};
    vector<int> v = {1,2};
    // vector<int> v = {1,2,3};
    
    Node* head = contruct_ll_vec(v);
    printLL(head);
    Node* middle = middleOfLinkedList(head);
    cout << middle->val << endl;
    printLL(head);
    cleanup_ll(head);
    return 0;
}

