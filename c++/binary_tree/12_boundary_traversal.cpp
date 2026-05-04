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

void left_boundary(TreeNode* node, vector<int>& res) {
    // if a node has a left, or a right
    // it is a non leaf node
    if(node->left) {
        res.push_back(node->data);
        left_boundary(node->left, res);
    }
    else if(node->right) {
        res.push_back(node->data);
        left_boundary(node->right, res);
    }
}

void right_boundary(TreeNode* node, vector<int>& res) {
    // if a node has a left, or a right
    // it is a non leaf node
    if(node->right) {        
        right_boundary(node->right, res);
        res.push_back(node->data);
    }
    else if(node->left) {        
        right_boundary(node->left, res);
        res.push_back(node->data);
    }
}

// this is not correct
// because the order is not correct
// void get_leaves(TreeNode* root, vector<int>& res) {
//     queue<TreeNode*> q;
//     q.push(root);
//     while(!q.empty()) {
//         int size = q.size();
//         for(int i=0; i<size; i++) {
//             TreeNode* node = q.front();
//             q.pop();

//             if(!node->left && !node->right) res.push_back(node->data);

//             if(node->left) q.push(node->left);
//             if(node->right) q.push(node->right);
//         }   
//     }
// }

void get_leaves(TreeNode* node, vector<int>& res) {
    if(!node) return;
    if(!node->left && !node->right) res.push_back(node->data);
    get_leaves(node->left, res);
    get_leaves(node->right, res);
}

vector<int> boundary(TreeNode* root) {
    vector<int> res;
    if(!root) return res;

    res.push_back(root->data);
    
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