#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

TreeNode* searchBST_rec(TreeNode* root, int val) {
    if(!root) return nullptr;
    if(val == root->data) return root;

    if(val > root->data) return searchBST_rec(root->right, val);

    if(val < root->data) return searchBST_rec(root->left, val);

    return nullptr;
}

TreeNode* searchBST_iter(TreeNode* root, int val) {
    while(root && root->data != val) {
        root = (val > root->data) ? root->right : root->left;
    }
    return root;
}

int main() {
    return 0;
}