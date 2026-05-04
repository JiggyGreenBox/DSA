#include <iostream>
#include <climits>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d),left(nullptr), right(nullptr) {}
};

int getSum(TreeNode* node, int& max_sum) {
    if(!node) return 0;

    // if ls/rs is negative, ignore branch
    // int ls = getSum(node->left, max_sum);
    // int rs = getSum(node->right, max_sum);

    int ls = max(0, getSum(node->left, max_sum));
    int rs = max(0, getSum(node->right, max_sum));

    max_sum = max(max_sum, (node->data + ls + rs));

    return node->data + max(ls, rs);
}

int maxPathSum(TreeNode* root) {
    // int max_sum = 0; // all nodes can be negative
    int max_sum = INT_MIN;
    getSum(root, max_sum);
    return max_sum;
}

int main() {
    // [20, 9, -10, null, null, 15, 7]
    // TreeNode* root = new TreeNode(20);
    // root->left = new TreeNode(9);
    // root->right = new TreeNode(-10);
    // root->right->left = new TreeNode(15);
    // root->right->right = new TreeNode(7); // 34

    // [-10, 9, 20, null, null, 15, 7]
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7); // 42

    cout << maxPathSum(root) << endl;
    return 0;
}