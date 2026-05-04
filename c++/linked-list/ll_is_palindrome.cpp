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
    if(!head || !head->next) return true;


    // fast and slow to find middle

    // 3 2 1 2 3
    // 3 2 1 3 2
    // 1 2 3 3 2 1
    // for odd reverse slow->next
    // for even reverse from slow


    // while slow
    // check with head

    Node* slow = head;
    Node* fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    // 1,2,3,4,5
    //     s
    //         f
    // 1,2,3,4,5,6
    //       s
    //            f

    // for even fast becomes nullptr
    // for odd fast stops at the last node

    Node* halfHead = (fast)? slow->next : slow;

    // Node* reverseHead = nullptr;
    // if(fast) reverseHead = slow->next;
    // else reverseHead = slow;

    // lets not reassign pointers back
    Node* rev = reverseLL(halfHead);

    // reverseHead = reverseLL(reverseHead);
    // slow = reverseHead;   
    Node* p1 = head; 
    Node* p2 = rev;
    while(p2){

        if(p1->val != p2->val){
            reverseLL(rev);
            return false;
        }

        p1 = p1->next;
        p2 = p2->next;
    }
    reverseLL(rev);
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

