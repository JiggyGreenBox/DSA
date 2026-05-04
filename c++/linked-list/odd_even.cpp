#include <iostream>
#include <vector>
#include "helper_ll.h"
using namespace std;


void print(std::string s, Node* p){
    if(!p){
       cout << s << " is nullptr" << endl;     
    }
    else{
        cout << s << " : " << p->val << endl;
    }    
}

Node* oddEvenList2(Node* head) {
    // nullptr and single node list
    if(!head || !head->next) return head;
    

    Node* next = nullptr;
    Node* prev = nullptr;
    Node* curr = head;
    Node* even_head = head->next;
    int count=1;

    print("head", head);

    while(curr->next != nullptr){

        print("curr", curr);
        next = curr->next; // can be nullptr
        print("next", next);

        print("--01_curr->next", curr->next);    
        if(next){
            curr->next = next->next;
            print("--02_curr->next", curr->next);   
        }
        else{
            curr->next = nullptr;            
        }

        
        prev = curr; 
        curr = next;        
        print("curr", next);
        ++count;        
    }

    print("curr", curr);
    cout << "count " <<count << endl;    

    if(count%2==0){
        prev->next = even_head;
    }
    else{
        curr->next = even_head;
    }

    
    return head;
}

Node* oddEvenList(Node* head) {
    // nullptr and single node list
    if(!head || !head->next) return head;
    

    // >=2 nodes
    Node* odd_tail = head;
    Node* even_head = head->next;
    Node* even_tail = even_head;

    // 1,2,3,4
    while(even_tail && even_tail->next){
        

        print("01 odd_tail", odd_tail);
        // skip for odd (1->3)
        odd_tail->next = even_tail->next;

        // move odd ahead, will skip now
        odd_tail = odd_tail->next;
        print("02 odd_tail", odd_tail);

        // skip for even (2->4)
        even_tail->next = odd_tail->next;   // could be nullptr

        print("03 even_tail", even_tail);

        // move even ahead, will skip
        even_tail = even_tail->next;        // could be nullptr

        print("04 even_tail", even_tail);
    }
    // figure out the assignments for pointers
    // then go backwards to find the nullptr checks
        // here the entry nodes are not null guarenteed
        // even is 1 ahead of odd
        // so we can skip checks for odd
        // even and even->next can be nullptr        
        
    print("05 odd_tail", odd_tail);
    odd_tail->next = even_head;
    return head;
}


int main(){
    // vector<int> v ={1, 2, 3, 4, 5};
    vector<int> v ={4, 3, 2, 1};
    
    Node* head = contruct_ll_vec(v);
    printLL(head);
    head = oddEvenList(head);
    printLL(head);
    cleanup_ll(head);
    return 0;
}
