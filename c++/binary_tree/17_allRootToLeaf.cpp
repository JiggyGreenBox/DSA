#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

void dfs(TreeNode* node, vector<int>& curr, vector<vector<int>>& res) {
    if(!node) return;
    
    curr.push_back(node->data);
    if(!node->left && !node->right) {
        res.push_back(curr);
    }
    dfs(node->left, curr, res);
    dfs(node->right, curr, res);
    curr.pop_back();
}

vector<vector<int>> allRootToLeaf(TreeNode* root) {
    vector<vector<int>> res;
    if(!root) return res;
    
    vector<int> curr;
    dfs(root, curr, res);

    return res;
}

void print(const vector<vector<int>>& res) {
    cout << "[ ";
    for(const auto& v : res) {
        cout << "[ ";
        for(int x : v) cout << x << " ";
        cout << "] ";
    }
    cout << "]\n";
}

int main() {
    // root = [1, 2, 3, null, 5, null, 4]
    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(2);
    // root->right = new TreeNode(3);
    // root->left->right = new TreeNode(5);
    // root->right->right = new TreeNode(4); //  [ [1, 2, 5] , [1, 3, 4] ]


    // Input : root = [1, 2, 3, 4, 5]
    // Output : [ [1, 2, 4] , [1, 2, 5] , [1, 3] ]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5); //  [ [1, 2, 4] , [1, 2, 5] , [1, 3] ]

    print(allRootToLeaf(root));
    return 0;
}