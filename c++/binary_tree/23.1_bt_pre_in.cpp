#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

// keeping this global to avoid args
// earlier search was O(n^2) because of O(n) find inside each call
// need a unordered_map to make this O(1)
// val, idx
unordered_map<int, int> inorder_map;

TreeNode* dfs(int root_idx, int start, int end, const vector<int>& preorder) {
    if(start > end) return nullptr;

    TreeNode* node = new TreeNode(preorder[root_idx]);

    int in_idx = inorder_map[preorder[root_idx]];
    int left_len = in_idx - start; // len of children to the left

    node->left  = dfs(root_idx + 1, 
                      start, 
                      in_idx - 1, 
                      preorder);

    node->right = dfs(root_idx + left_len + 1, 
                      in_idx + 1, 
                      end, 
                      preorder);

    return node;
}

// for inorder, LrootR
// and for preorder rootLR
//  first we have the node, node+1 is left-child, node+len-left-children+1 is right child

// we can get left children len from inorder because LrootR
//      inorder-idx - start = len-left-children

TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
    // earlier search was O(n^2) because of O(n) find inside each call
    // need a unordered_map to make this O(1)

    // val, idx
    int n = inorder.size();
    for(int i=0; i<n; i++) {
        inorder_map[inorder[i]] = i;
    }
    return dfs(0, 0, n-1, preorder);
}

void printLevels(TreeNode* root) {
    if(!root) return;
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int size = q.size();

        cout << "[";

        for(int i=0; i<size; i++) {
            TreeNode* node = q.front();
            q.pop();

            cout << node->data << " ";

            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        cout << "]\n";
    }
}


int main() {


    // printLevels(buildTree({3, 9, 20, 15, 7},{9, 3, 15, 20, 7}));

    printLevels(buildTree({3, 4, 5, 6, 2, 9},{5, 4, 6, 3, 2, 9}));

    return 0;
}