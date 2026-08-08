#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

unordered_map<int, int> inMap;


TreeNode* build(const vector<int>& inorder,
                int inL,
                int inR,
                const vector<int>& postorder,
                int postL,
                int postR)
{
    if (inL > inR || postL > postR)
        return nullptr;

    TreeNode* root = new TreeNode(postorder[postR]);

    int pos = inMap[root->data];

    int leftSize = pos - inL;

    root->left = build(inorder,
                        inL,
                        pos - 1,
                        postorder,
                        postL,
                        postL + leftSize - 1);

    root->right = build(inorder,
                        pos + 1,
                        inR,
                        postorder,
                        postL + leftSize,
                        postR - 1);

    return root;
}


TreeNode* buildTree(const vector<int>& inorder, const vector<int>& postorder) {
    // build loop up
    int n = inorder.size();

    for(int i=0; i<n; i++) {
        inMap[inorder[i]] = i;
    }

    return build(inorder,
                     0,
                     inorder.size() - 1,
                     postorder,
                     0,
                     postorder.size() - 1);
}

void printInorder(TreeNode* node) {
    if(!node) return;
    printInorder(node->left);
    cout << node->data << ",";
    printInorder(node->right);
}

int main() {
    printInorder(buildTree({9, 3, 15, 20, 7}, {9, 15, 7, 20, 3}));
    return 0;
}