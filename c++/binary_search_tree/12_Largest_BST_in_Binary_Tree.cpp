#include <iostream>
#include <vector>
#include "00_BST_helper.h"
using namespace std;

/*

Largest BST in Binary Tree

    Given a root of Binary Tree, where the nodes have integer values. 
    Return the size of the largest subtree of the binary tree which is 
    also a BST.

    A binary search tree (BST) is a binary tree data structure which has 
    the following properties.

    The left subtree of a node contains only nodes with data less than 
    the node’s data.

    The right subtree of a node contains only nodes with data greater 
    than the node’s data.

    Both the left and right subtrees must also be binary search trees.

      3
     1 2
    4 

    count valid nodes
        node is valid if
            left exits and is smaller than node

            right exits and is greater than node

    dfs(node)
        if not node
            0
        count = 1

        if valid left
            count += dfs(left)

        if valid right
            count += dfs(right)
            
        return count
*/

int helper(TreeNode* node) {
    if(!node) 
        return 0;

    int count = 1;

    if(node->left && node->left->data < node->data) {
        count += helper(node->left);
    } 
    if(node->right && node->right->data > node->data) {
        count += helper(node->right);
    }

    return count;
}

int largestBST(TreeNode* root){
    if(!root) return 0;

    return helper(root);
}

int main() {
    return 0;
}