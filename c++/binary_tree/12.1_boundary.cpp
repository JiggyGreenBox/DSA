#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

bool isLeaf(TreeNode* node) {
    return node && !node->left && !node->right;
}

void left_boundary(TreeNode* node, vector<int>& res) {
    while(node) {
        if(!isLeaf(node)) res.push_back(node->data);

        if(node->left) node = node->left;
        else node = node->right;
    }
}

void get_leaves(TreeNode* node, vector<int>& res) {
    if(!node) return;
    if(isLeaf(node)) res.push_back(node->data);
    get_leaves(node->left, res);
    get_leaves(node->right, res);
}

void right_boundary(TreeNode* node, vector<int>& res) {
    vector<int> temp;
    while(node) {
        if(!isLeaf(node)) temp.push_back(node->data);

        if(node->right) node = node->right;
        else node = node->left;
    }

    for(int i=temp.size()-1; i>=0; i--) {
        res.push_back(temp[i]);
    }
}

vector<int> boundary(TreeNode* root) {
    vector<int> res;
    if(!root) return res;

    if(!isLeaf(root)) res.push_back(root->data);

    left_boundary(root->left, res);
    get_leaves(root, res);
    right_boundary(root->right, res);

    return res;
}

void print(const vector<int>& res) {
    cout << "[ ";
    for(auto x : res) cout << x << " ";
    cout << "]\n";
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(8);
    root->left->right->right = new TreeNode(9);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);    

    print(boundary(root));     

    return 0;
}