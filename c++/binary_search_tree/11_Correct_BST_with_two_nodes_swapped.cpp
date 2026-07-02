#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include "00_BST_helper.h"
using namespace std;

/*
Correct BST with two nodes swapped

    2 nodes are out of place

    when inorder is done, we get a sortedarray

    brute:
        inorder to get array
        one more pass to overwrite correct answers

    better:
        there are 2 situations
        1 3 2 4 5
          ^ ^    
        1 5 3 4 2
          ^     ^

        swapped nodes are adjacent or not adjacent
        
        compare to prev
            if node < prev

            store both prev and curr

        look for another violation
            if found swap (non-adj)
            if not swap (adj)
*/

void inorder(TreeNode* node, TreeNode* prev, TreeNode* first, TreeNode* last) {
    if(!node)
        return;
    
    inorder(node->left, prev, first, last);

    if(prev && prev->data > node->data) {
        // violation

        // if adjacent, store prev, and curr
        if(!first)
            first = prev;
        
        // if not adjacent, we overwrite last
        last = node;
    }

    prev = node;

    inorder(node->right, prev, first, last);
}

void recoverTree(TreeNode* root) {
    TreeNode* first = nullptr;
    TreeNode* last = nullptr;

    TreeNode *prev = nullptr;

    inorder(root, prev, first, last);

    swap(first->data, last->data);    
}

int main() {
    // TreeNode* root = constructBST({});
    return 0;
}