/*
Merge k Sorted Lists
    [https://leetcode.com/problems/merge-k-sorted-lists/description/]


You are given an array of k linked-lists lists, each linked-list is 
sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

 

Example 1:

    Input: lists = [[1,4,5],[1,3,4],[2,6]]
    Output: [1,1,2,3,4,4,5,6]
    Explanation: The linked-lists are:
    [
    1->4->5,
    1->3->4,
    2->6
    ]
    merging them into one sorted linked list:
    1->1->2->3->4->4->5->6

Example 2:

    Input: lists = []
    Output: []
    Example 3:

    Input: lists = [[]]
    Output: []
*/

/*

we take head of all and push into heap
    then we pop
        and append till all nodes are nullptr?

do i have to disconnect the nodes or copy values to a new list?
*/

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* contruct_ll_vec(const vector<int> &vec){
    if(vec.empty()) return nullptr;

    ListNode dummy(-1);    
    ListNode* curr = &dummy;

    for(auto x : vec){
        curr->next = new ListNode(x);
        curr = curr->next;
    }

    return dummy.next;    
}

void printLL(ListNode* head){
    while(head){
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {

    auto cmp = [](const auto &a, const auto &b) {
        return a->val > b->val;
    };

    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

    for(auto node : lists) {
        if (node)
            pq.push(node);
    }

    ListNode dummy(-1);
    ListNode* curr = &dummy;
    while(!pq.empty()) {
        ListNode* node = pq.top();
        pq.pop();

        if(node->next)
            pq.push(node->next);

        //node->next = nullptr;
        curr->next = node;
        curr = node;
    }
    return dummy.next;
}

int main() {

    vector<ListNode*> lists = {contruct_ll_vec({1,4,5}),contruct_ll_vec({1,3,4}),contruct_ll_vec({2,6})};


    printLL(mergeKLists(lists));

    return 0;
}