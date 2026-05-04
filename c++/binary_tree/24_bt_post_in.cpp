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

TreeNode* dfs(int root_idx, 
              int start, 
              int end,
              const vector<int>& postorder) 
{
    if(start > end) return nullptr;

    TreeNode* node = new TreeNode(postorder[root_idx]);
    int in_idx = inMap[postorder[root_idx]]; //1
    int right_len = end - in_idx; //1-1=0
    
    node->left = dfs(root_idx - right_len - 1,
                     start,
                     in_idx-1,
                     postorder);

    node->right = dfs(root_idx-1,
                      in_idx+1,
                      end,
                      postorder);

    return node;
}



TreeNode* buildTree(const vector<int>& inorder, const vector<int>& postorder) {
    // build loop up
    int n = inorder.size();
    for(int i=0; i<n; i++) {
        inMap[inorder[i]] = i;
    }

    // dfs
    return dfs(n-1, 0, n-1, postorder);
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