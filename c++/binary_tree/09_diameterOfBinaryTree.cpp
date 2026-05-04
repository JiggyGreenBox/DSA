#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

int getHeight(TreeNode* node, int& max_diameter) {
    if(!node) return 0;
    int lh = getHeight(node->left, max_diameter);
    int rh = getHeight(node->right, max_diameter);

    max_diameter = max(max_diameter, (lh+rh));

    return 1 + max(lh, rh);
}

int diameterOfBinaryTree(TreeNode* root) {
    // we want to find the longest path by any node in the tree
    // can we say we want max-depth-left + max-depth-right, for each node?
    // since we are calculating number of edges, we take (max-l + max-r)
    // if we were calculating number of nodes, (max-l + max-r + 1)
    int max_diameter = 0;
    getHeight(root, max_diameter);
    return max_diameter;
}

int main() {
    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(2);
    // root->left->left = new TreeNode(2);
    // root->left->right = new TreeNode(2);
    // root->right = new TreeNode(3); // max_diameter = 3

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);    
    root->left->right = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(2);  // max_diameter = 4


    cout << diameterOfBinaryTree(root) << endl;
    return 0;
}