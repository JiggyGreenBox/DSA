#include <iostream>
#include <vector>
#include "helper_ll.h"

Node* sortList(Node* head) {
    if(!head) return nullptr;

    vector<Node*> v0;
    vector<Node*> v1;
    vector<Node*> v2;

    Node* curr = head;
    while(curr){
        Node* stripped_node = curr;
        curr = curr->next;

        stripped_node->next = nullptr;
        int val = stripped_node->val;
        if(val == 0){
            v0.push_back(stripped_node);
        } 
        else if(val == 1){
            v1.push_back(stripped_node);
        }
        else if(val == 2){
            v2.push_back(stripped_node);
        }        
    }

    Node* newHead = nullptr;
    Node* tail = nullptr;

    for(auto x: v0){
        if(!newHead){
            newHead = x;
            tail = x;
        }
        else{
            tail->next = x;
            tail = x;
        }
    }

    for(auto x: v1){
        if(!newHead){
            newHead = x;
            tail = x;
        }
        else{
            tail->next = x;
            tail = x;
        }
    }

    for(auto x: v2){
        if(!newHead){
            newHead = x;
            tail = x;
        }
        else{
            tail->next = x;
            tail = x;
        }
    }

    // unlink last element
    if(tail) tail->next = nullptr;

    return newHead;
}



Node* sortList2(Node* head) {
    if(!head) return nullptr;

    vector<Node*> n_vec[3];

    Node* curr = head;
    while(curr){
        Node* next = curr->next;
        curr->next = nullptr;
        n_vec[curr->val].push_back(curr);
        curr = next;
    }

    Node* newHead = nullptr;
    Node* tail = nullptr;

    for(int i=0; i<3; i++){
        for(auto n : n_vec[i]){
            if(!newHead){
                newHead = n;
                tail = n;
            }
            else{
                tail->next = n;
                tail = n;
            }
        }
    }
    // if(tail) tail->next = nullptr;
    return newHead;
}

Node* sortList3(Node* head) {

    if(!head) return head;

    // 3 heads
    // 3 tails
    Node *h0 =nullptr, *t0 = nullptr;
    Node *h1 =nullptr, *t1 = nullptr;
    Node *h2 =nullptr, *t2 = nullptr;    
    
    Node* curr = head;
    while(curr){
        int val = curr->val;
        Node* node = curr;
        curr = curr->next;
        node->next = nullptr; //delink        

        if(val == 0){
            if(!h0){
                h0 = t0 = node;
            }
            else{
                t0->next = node;
                t0 = node;
            }
        }
        else if(val == 1){
            if(!h1){
                h1 = t1 = node;
            }
            else{
                t1->next = node;
                t1 = node;
            }
        }
        else if(val == 2){
            if(!h2){
                h2 = t2 = node;
            }
            else{
                t2->next = node;
                t2 = node;
            }
        }        
    }    

    // handle missing 1s
    if(t0){
        if(t1) t0->next = h1;
        else if(t2) t0->next = h2;        
    }
    if(t1)t1->next = h2; // can be nullptr    

    if(h0) return h0;
    if(h1) return h1;
    return h2;
}


Node* sortList4(Node* head) {

    if(!head) return head;

    // 3 heads
    // 3 tails
    Node *h[3] = {nullptr, nullptr, nullptr};
    Node *t[3] = {nullptr, nullptr, nullptr};
    
    Node* curr = head;
    while(curr){
        int val = curr->val;
        Node* node = curr;
        curr = curr->next;
        node->next = nullptr; //delink        
        
        if(!h[val]){                
            h[val] = t[val] = node;
        }
        else{
            t[val]->next = node;
            t[val] = node;                
        }              
    }    

    // link 0->1->2
    // handle missing 1s
    if(t[0]){
        // if(t[1]) t[0]->next = h[1];
        // else if(t[2]) t[0]->next = h[2];            
        t[0]->next = (t[1]) ? h[1] : h[2];
    }
    if(t[1]) t[1]->next = h[2]; // can be nullptr    

    if(h[0]) return h[0];
    if(h[1]) return h[1];
    return h[2];
}


Node* sortList5(Node* head) {
    /* If the list is empty or has only one 
    node, return as it is already sorted*/
    if (head == NULL || head->next == NULL)
        return head;

    // Dummy nodes to point to heads of 
    // three lists
    Node* zeroHead = new Node(-1);
    Node* oneHead = new Node(-1);
    Node* twoHead = new Node(-1);

    // Pointers to current last nodes of 
    // three lists
    Node* zero = zeroHead;
    Node* one = oneHead;
    Node* two = twoHead;
    Node* temp = head;

    /* Traverse the original list 
    and distribute the nodes 
    into three lists*/
    while (temp != NULL) {
        if (temp->val == 0) {
            zero->next = temp;
            zero = temp;
        } else if (temp->val == 1) {
            one->next = temp;
            one = temp;
        } else if (temp->val == 2) {
            two->next = temp;
            two = temp;
        }
        temp = temp->next;
    }
    
    // Connect the three lists together
    zero->next = (oneHead->next) ? oneHead->next : twoHead->next;
    one->next = twoHead->next;
    two->next = NULL;

    // New head of the sorted list
    Node* newHead = zeroHead->next;

    // Delete dummy nodes
    delete zeroHead;
    delete oneHead;
    delete twoHead;
    
    return newHead;
}

int main(){
    vector<int> v ={2,2,2,2,2,1,1};
    
    Node* head = contruct_ll_vec(v);
    printLL(head);
    // head = sortList2(head);
    head = sortList5(head);
    printLL(head);
    cleanup_ll(head);
    return 0;
}