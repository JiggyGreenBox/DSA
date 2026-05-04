#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};
// we have 2 options
// my first approach idea
// was the get path from root to node p, then path from root to node q
// [root,1,2,3,p]
// [root,1,2,3,4,5,6,q]
// then LCA would be last common node = 3
// O(2N) time, and O(2N) space

// cannonical solution
// uses recursion
    // At each node:

    // If node == p or node == q → return node

    // Recursively search left

    // Recursively search right

    // Now consider cases:

    // 1. Left returns non-null AND right returns non-null
    // → current node is LCA

    // 2. Only one side returns non-null
    // → propagate that upward

    // 3. Both null
    // → return null

    // That’s the core idea.

// my thinking
// for each node, see if left has node in its path, and right has node in its path
// if top down, this is very complicated, have to check children
// for a bottom up approach LeftRightRoot is better
// when we see left and right have the required nodes return
// worst case is root returns the answer

// node dfs(node, a, b)
//     if(!node) return nullptr
//     if node == a || node == b
//         return node

//     node left = dfs(node->left, a, b)
//     node right = dfs(node->right, a, b)

//     if(left && right) return node
//     return nullptr

TreeNode* dfs(TreeNode* node, TreeNode* a, TreeNode* b) {
    if(!node) return nullptr;        
    if(node == a || node == b) return node;

    TreeNode* left = dfs(node->left, a, b);
    TreeNode* right = dfs(node->right, a, b);    
    
    // if both found return the node, LCA
    if(left && right) return node;
    // if only one found, tell the parent we found a child
    if(left) return left; 
    if(right) return right;
    return nullptr; // nothing found
}

TreeNode* lowestCommonAncestor_mine(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root || !p || !q) return nullptr;
    return dfs(root, p, q);
}

// cannonical
// uses the same functon
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root || root == p || root==q ) {
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if(left && right) return root;
    return (left)? left : right;
}


int main() {
    //  [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4] , p = 5, q = 1
    TreeNode* root = new TreeNode(3);
    root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    // auto node = lowestCommonAncestor(root, root->left, root->right);
    // cout << node->data << endl;

    auto node2 = lowestCommonAncestor(root, root->left, root->left->right->right);
    cout << node2->data << endl;
    return 0;
}