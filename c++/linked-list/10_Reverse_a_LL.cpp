#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int v) : val(v), next(nullptr) {}
    ListNode(int v, ListNode *n) : val(v), next(n) {}
};

ListNode* reverseList(ListNode* head) {

}

/*
Reverse a LL
    approach 1 
        insert values into vector
        reverse vector
        overwrite values
    
    approach 2
        prev > curr > next

        while(curr)
            next = curr->next

            curr->next = prev            

            curr = next
            prev = curr   
*/

int main() {
    return 0;
}