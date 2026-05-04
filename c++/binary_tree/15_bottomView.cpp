#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

vector<int> bottomView(TreeNode *root) {
    vector<int> res;
    if(!root) return res;

    // col,  val
    map<int, int> mpp;
    
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    while(!q.empty()) {
        auto [node, col] = q.front();
        q.pop();

        mpp[col] = node->data; // always overwrite
        if(node->left) q.push({node->left, col-1});
        if(node->right) q.push({node->right, col+1});
    }

    for(auto& [col, val] : mpp) {
        res.push_back(val);
    }
    return res;
}

void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

int main() {

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7); // [4, 2, 1, 3, 7]

    print(bottomView(root));
    return 0;
}