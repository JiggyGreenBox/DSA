#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

int helper(TreeNode* node) {
    if(!node) return 0;
    return 1 + max(helper(node->left), helper(node->right));
}
// this function is n^2
// this is because at the root we check left and right
// but we also have to check the subtrees
// as the imbalance might be lower down
// so we end up checking nodes muliple times
bool isBalanced_n2(TreeNode *root) {

    if(!root) return true;

    // allowed 0, -1, +1
    int h_left = helper(root->left);
    int h_right = helper(root->right);

    if(abs(h_left - h_right) > 1) return false;

    // check further down recursively
    bool b_left = isBalanced_n2(root->left);
    bool b_right = isBalanced_n2(root->right);

    if(!b_left || !b_right) return false;

    return true;
}

// a better O(n) method is to 
// just check the height once
// if we find an imbalance
// return -1, and exit else return height for next level
// we only reach the root if the tree is balanced at each node
int getHeight(TreeNode* node) {
    if(!node) return 0;

    int lh = getHeight(node->left);
    if(lh == -1) return -1;

    int rh = getHeight(node->right);
    if(rh == -1) return -1;

    if(abs(lh-rh) > 1) return -1;

    return 1 + max(lh, rh);
}
bool isBalanced_n(TreeNode *root) {
    return getHeight(root) != -1;
}


int main() {

    TreeNode* r1 = new TreeNode(1);
    r1->left = new TreeNode(2);
    r1->right = new TreeNode(3);
    
    TreeNode* r2 = new TreeNode(1);    
    r2->left = new TreeNode(2);
    // r2->right = new TreeNode(3);
    r2->left->left = new TreeNode(4);

    if(isBalanced_n(r1)) cout << "balanced" << endl;
    else cout << "no" << endl;

    if(isBalanced_n(r2)) cout << "balanced" << endl;
    else cout << "no" << endl;

    return 0;
}
