#include <iostream>
#include <climits>
#include <sstream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

/*

Check if a tree is a BST or not

for any node
    if largest from left-sub-tree > node
        invalid

    if smallest from rigth_sub_tree < node
        invalid

    inorder pred, succ

*/
bool helper(TreeNode* node, int minv, int maxv) {
    if(!node)
        return true;

    if(node->data <= minv || node->data >= maxv)
        return false;

    return helper(node->left, minv, node->data) && helper(node->right, node->data, maxv);
}

bool isBST(TreeNode* root) {
    return helper(root, INT_MIN, INT_MAX);
}

int main() {
    // TreeNode* root = buildTreeBFS("1,2,null,3,null,");
    
    return 0;
}