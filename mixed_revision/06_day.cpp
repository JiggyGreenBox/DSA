// aug 22, 5 days after last revision
// had fever so there was a gap

/*
Mixed Revision — Problem 1

    You are given the head of a linked list where each node contains:

    value
    next
    random

    The random pointer may point to any node in the list or nullptr.

    Create and return a deep copy of the entire linked list.

    The copied list must contain completely new nodes, with both next and 
    random pointers corresponding to the original list.


    Example

        1 → 2 → 3
        ↑   ↓
        └── random relationships

        1.random → 3
        2.random → 1
        3.random → 2

        The returned list must have the same structure, but none of the new 
        nodes may be the original nodes.

    
Brute force:

    if there were no random pointers
    then duplication would be been quite simple

    we could store list values
    in a vector
    and use a map to store random values

    then reconstruct the copy from these datastructures

Observation:

    we can create clones of the nodes in this manner

    1->2->3

    1->1`->2->2`->3->3`

    then
        node->next->random = node->random->next

        this allows copy to link to copy

    then disconnect copy nodes

Invariant:
Algorithm:

    Node* cloneList(Node* head) {

        if(!head)
            return nullptr;

        Node* curr = head;
        
        // create copies inbetween
        while(curr) {
            Node* next = curr->next;
            curr->next = new Node(curr->val);
            curr->next->next = next;
            curr = next;
        }

        // link the copies
        curr = head;
        while(curr) {
            curr->next->random = curr->random->next;
            curr = curr->next->next;
        }

        // disconnect the copies
        curr = head;
        Node* copyHead = head->next;
        Node* copy = copyHead;

        while(curr) {
            curr->next = copy->next;
            curr = curr->next;
            copy->next = curr->next;
            copy = copy->next;
        }

        return copyHead;
    }

Complexity:
    O(n) time
    O(n) for answer, but no DS is used to store the answer
---------------------
Review
    green | revisited problem

---------------------

Problem 2

    You are given a binary tree. Return the lowest common ancestor (LCA) 
    of two given nodes p and q.

    The tree is not necessarily a BST.

    The LCA is the lowest node in the tree that has both p and q as 
    descendants. A node can be a descendant of itself.


        3
       / \
      5   1
     / \ / \
    6  2 0  8
      / \
     7   4

    p = 5
    q = 1
        ans 3

    p = 5
    q = 4
        ans 5

Brute force:
    for each node
        check left subtree and right subtree
            if both are found return lca
        check leftsubtree
        check rightsubtree
Observation:
    p and q are guaranteed to exist in the tree

    so if no nodes found in rightsubtree
    ans will lie in leftsubtree

Invariant:
Algorithm:

    Node* lca(Node* node, Node* p, Node* q) {
        if(!node || node == q || node == p)
            return node;

        Node* left = lca(node->left, p, q);
        Node* right = lca(node->right, p, q);

        if(left && right)
            return node;
        else if(left)
            return left;
        else if(right)
            return right;
        
        return nullptr;
    }

Complexity:
    O(n) every node is visited
    O(h) stack space
    O(n) worst stack space
------------------------
Review
    green
    revisit


------------------------
Problem 3 — Stack / Queue


You are given a string s containing lowercase letters and parentheses.

Remove the minimum number of parentheses so that the resulting string 
is valid.

A valid parentheses string has every opening parenthesis matched with 
a closing parenthesis, and parentheses must close in the correct 
order.

Examples
    s = "lee(t(c)o)de)"
    Output = "lee(t(c)o)de"

    s = "a)b(c)d"
    Output = "ab(c)d"

    s = "))(("
    Output = ""


Brute force:
    normally we would be able to track unmatched brackets
    but we have characters inbetween
    if we call top how do we know which bracket to call?

    if we only track brackets
        then how do we reconstruct the answer?
        where do we put brackets?
Observation:
    erase unmatched closing brackets
Invariant:
Algorithm:
Complexity:
    O(n) time
        worst case O(n^2) for string erase
    O(n) space
*/
#include <iostream>
#include <unordered_set>
#include <stack>
using namespace std;
string removeParantheses(string s) {

    stack<pair<char,int>> st;

    for(int i=0; i<s.size(); i++) {
        
        char ch = s[i];

        // if closing and unmatched, erase
        if(ch == ')') {
            if(!st.empty())
                st.pop();
            else                
                s.erase(i, 1);
        }

        // if open, push
        if(ch == '(')
            st.push({ch, i});
    }

    while(!st.empty()) {
        auto [ch, i] = st.top();
        st.pop();
        s.erase(i, 1);
    }
    return s;
}

/*

Review
-------------


Remove Invalid Parentheses


Recognition: 🟢
Implementation: 🟡
*/

string removeParentheses(string s) {

    stack<int> st;
    unordered_set<int> remove;

    for(int i = 0; i < s.size(); i++) {

        if(s[i] == '(') {
            st.push(i);
        }
        else if(s[i] == ')') {

            if(!st.empty()) {
                st.pop();
            }
            else {
                remove.insert(i);
            }
        }
    }

    // unmatched '('
    while(!st.empty()) {
        remove.insert(st.top());
        st.pop();
    }

    string ans;

    for(int i = 0; i < s.size(); i++) {
        if(!remove.count(i))
            ans += s[i];
    }

    return ans;
}