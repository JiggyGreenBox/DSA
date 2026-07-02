#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

int getHeight(TreeNode* node, bool isLeft) {
    int res = 0;
    while(node) {
        if(isLeft) node = node->left;
        else node = node->right;        
        res++;
    }
    return res;
}

int countNodes(TreeNode* root) {
    if(!root) return 0;

    int lh = getHeight(root, true);
    int rh = getHeight(root, false);

    if(lh == rh) {
        return (1 << lh) - 1;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// --------------------------------------------
int leftHeight(TreeNode* node) {
    int h = 0;

    while(node) {
        h++;
        node = node->left;
    }

    return h;
}

int rightHeight(TreeNode* node) {
    int h = 0;

    while(node) {
        h++;
        node = node->right;
    }

    return h;
}

int countNodes_canon(TreeNode* root) {

    if(!root)
        return 0;

    int lh = leftHeight(root);
    int rh = rightHeight(root);

    // Perfect binary tree
    if(lh == rh)
        return (1 << lh) - 1;

    return 1 + countNodes(root->left) + countNodes(root->right);
}
// --------------------------------------------
int main() {
    
    return 0;
}