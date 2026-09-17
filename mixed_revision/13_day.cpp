/*
sep 10
    last sep 7
=====================================
Session 1 — Older mixed
    Binary Search
    Linked List
    Tree/BST
-------
Problem 1 — Binary Search

You are given a sorted array of integers nums in ascending order and 
an integer target.

Return the index of the first occurrence of target in nums. If target 
does not exist, return -1.


    nums = [1, 2, 2, 2, 4, 5]
    target = 2

    Output: 1

Brute force
    linear scan
    O(n) time O(1) space
observation
    since the array is sorted we can discard half at each step
invariant
    perform binary search to find the answer
    if target found look for a earlier occurance of target    

    
algorithm
    int lowerBound(vector<int> &nums, int target) {
        int n = nums.size();
        int l = 0;
        int h = n;

        1 2 3 3 4 5 6
        m = 3

        while(l < h) {
            int m = l + (h-l)/2;
            if(nums[m] >= target) {
                h = m;
            }
            else {
                l = m + 1;
            }
        }
        return nums[l]  == target? l : -1;
    }
complexity
    O(logn) time
    O(1) space

Review
    green/green
----------

Problem 2 — Linked List

Given the head of a singly linked list, reverse the list in groups of 
k nodes.

If the number of nodes remaining is less than k, leave those nodes 
unchanged.

Return the new head.


Brute force
    copy node vals into vector and then perform rotations
    then copy back
observation
    we can use pointers combined with reversals
invariant
    we want 
        groupPrev -> k nodes -> groupNext
        we want to reverse the k nodes
        groupPrev -> reversed k Nodes -> groupNext

    
algorithm
    Node* reverseKGroups(Node* head, int k) {
    if(!head || k == 0)
        return head;

    Node dummy(-1);
    dummy.next = head;
    Node* groupPrev = &dummy;

    while(true) {

        Node* kth = groupPrev;

        for(int i=0; i<k; i++) {

            kth = kth->next;

            if(!kth)
                return dummy.next;
        }

        // reverse the k nodes
        Node* groupNext = kth->next;
        Node* curr = groupPrev->next;
        Node* newPrev = curr; // better way to reattach?
        Node* prev = groupNext;

        while(curr != groupNext) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // reconnect
        groupPrev->next = kth;
        groupPrev = newPrev;
    }

    return dummy.next;
}

complexity
    O(n) time
    O(1) space

green/green

----------------------
Problem 3 — Binary Tree

Given the root of a binary tree, return the maximum width of the tree.

The width of a level is defined as the distance between the leftmost 
and rightmost non-null nodes, including the null positions between 
them.

Brute force:
    use the heap indexing 
        left-child = 2*i + 1
        right-child = 2*i + 2

    store the max right-left
Observation:
    we can see that at each level the indexing will double
    but we dont need level to level comparisons
    we will normalize for each level
Invariant:
    starting from level 0
        left = 2*i+1
        right = 2*i+1

    store first and last per level
        for each
            idx -= first
        add their children

    for each level
        right - left + 1
        
Algorithm:
int max_width(Node* root) {
    if(!root)
        return 0;

    queue<pair<Node*, int>> q;
    q.push({root, 0});

    int max_width = 0;

    while(!q.empty()) {

        int size = q.size();

        int first = q.front().second;
        int last = first;

        for(int i=0; i < size; i++) {
            
            auto [node, idx] = q.front();
            q.pop();

            idx -= first;

            if(i == size-1)
                last = idx;

            if(node->left)
                q.push({node->left, 2*idx+1});

            if(node->right)
                q.push({node->right, 2*idx+2});
        }

        max_width = max(max_width, last+1);

    }
    return max_width;
}
Complexity:
    O(n) time
    O(n) space

*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;




// 1 2 3 -- 4 5 6 -- 7 8
//    gP       k    gN

// 1 2 3 -- 6 5 4 -- 7 8
//    gP    k       gN



int main() {
    return 0;
}