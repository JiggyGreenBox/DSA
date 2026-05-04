#include <iostream>
#include "helper_ll.h"
using namespace std;

Node* reverseLL(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// D 1, 2, 3, 4, 5
//  n1

Node* reverse2(Node* first, Node* last) {
    
    // point first node to last
    // point -1 node to newHead
    // reverse every node in the middle    
    Node* prev = last->next;     // 3
    Node* limit = prev;
    Node* curr = first;     // 1

    while(curr != limit){           // 1 != 3, 2!=3
        Node* next = curr->next;    // 2, 3
        curr->next = prev;          // 1->3, 2->1
        prev = curr;                // 1, 2
        curr = next;                // 2, 3
    }

    return prev;
}

Node* reverseKGroup(Node* head, int k) {

    // Node* dummy = new Node(-1, head);

    // dummy->next = reverse2(head, head->next->next);


    // // reverse2(head->next, head->next->next->next);

    // return dummy;


    // need a dummy for smooth operations with head reversal
    Node* dummy = new Node(-1, head);

    Node* prev = dummy;
    Node* curr = head;
    int count = 0;
    while (curr) {
        count++;

        cout << "count: " << count << endl; 
        cout << "CURR: " <<curr->val << endl; 

        if(count == k){
            count = 0;

            Node* first = prev->next;
            Node* last = curr;
            

            cout << "reverse: ";
            cout << first->val;
            cout << " to " << curr->val << endl;

            Node* newHead = reverse2(first, last);


            cout << "prev: " << prev->val << endl;
            cout << "newHead: " << newHead->val << endl;

            prev->next = newHead;

                        

            prev = first;
            curr = first;

            cout << "NOW prev: " << prev->val << endl;
        }            
        curr = curr->next;
        if(curr) cout << "NOW curr: " << curr->val << endl;         
    }
    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}


Node* reverseKGroup2(Node* head, int k) {

    // Node* dummy = new Node(-1, head);

    // dummy->next = reverse2(head, head->next->next);


    // // reverse2(head->next, head->next->next->next);

    // return dummy;


    // need a dummy for smooth operations with head reversal
    Node* dummy = new Node(-1, head);

    Node* prev = dummy;
    Node* curr = head;
    int count = 0;
    while (curr) {
        count++;
        if(count == k){
            count = 0;

            Node* first = prev->next;  // last node after reversal
            Node* last = curr;         // since counter, curr is tail            

            Node* newHead = reverse2(first, last); // returns newhead after reversal            

            prev->next = newHead;       // connect prev to newHead, as old head is now tail

            prev = first; // first is now tail, used for next iteration
            curr = first; // curr is also pointing to new tail, so that curr = curr->next works correctly            
        }            
        curr = curr->next;        
    }

    // get rid of dummy
    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}


// D 1, 2, 3, 4, 5

// D 1, 2, 3, 4, 5
// P
//      C
//            P
//                 C

// rev(P,C)
// P=C
// rev(P,C)


Node* reverse(Node* head){
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

// cannonical solution
Node* reverseKGroup3(Node* head, int k) {
    Node* dummy = new Node(-1, head);

    Node* prev = dummy;    
    Node* end = dummy;

    while(true){
        // move end ahead
        // notice how index starts from zero
        // so we need to be at tail, or dummy for this to work correctly
        // cant have end = tail->next,
        // end = new_tail
        for(int i=0; i<k && end; i++){
            end = end->next;
        }
        if(!end) break;

        Node* start = prev->next;
        Node* next = end->next;

        end->next = nullptr; // to use reverse without any modifications

        prev->next = reverse(start); // now start points to the new_tail

        start->next = next; // reversal complete

        // for next iter
        prev = start;
        end = start; // 0 index loop, for kth node
    }

    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}


int main() {

    vector<int> v ={1, 2, 3, 4, 5};
    int k = 2;

    Node* head = contruct_ll_vec(v);
    printLL(head);

    head = reverseKGroup3(head, k);

    printLL(head);
    cleanup_ll(head);
    return 0;
}
