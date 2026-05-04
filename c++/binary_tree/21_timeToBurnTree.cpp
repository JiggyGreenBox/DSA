#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

TreeNode* dfs(TreeNode* node, int start) {
    if(!node) return nullptr;
    if(node->data == start) return node;
    
    TreeNode* left = dfs(node->left, start);
    if(left) return left;

    TreeNode* right = dfs(node->right, start);
    if(right) return right;

    return nullptr;
}

int timeToBurnTree(TreeNode* root, int start) {
    if(!root || !start) return 0;
    int time = 0;
    // 1. need parent mapping
    unordered_map<TreeNode*, TreeNode*> mpp;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if(node->left) {
            mpp[node->left] = node;
            q.push(node->left);
        }
        if(node->right) {
            mpp[node->right] = node;
            q.push(node->right);
        }
    }

    // 2. find start node, from start val
    TreeNode* start_node = dfs(root, start);

    // 2. move radially from the start node
    unordered_set<TreeNode*> visited;
    q.push(start_node);
    visited.insert(start_node);

    while(!q.empty()) {

        int size = q.size();
        bool burned = false;

        for(int i=0; i<size; i++) {
            TreeNode* node = q.front();
            q.pop();

            if(node->left && !visited.count(node->left)) {
                visited.insert(node->left);
                q.push(node->left);
                burned = true;
            }
            if(node->right && !visited.count(node->right)) {
                visited.insert(node->right);
                q.push(node->right);
                burned = true;
            }
            if(mpp.count(node) && !visited.count(mpp[node])) {
                visited.insert(mpp[node]);
                q.push(mpp[node]);
                burned = true;
            }
        }
        if(burned) time++;
    }
    return time;
}

int main() {
    // root = [1, 2, 3, 4, null, 5, 6, null, 7]. target = 1
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->left->left->right = new TreeNode(7);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(6);
    root->right->left = new TreeNode(5);

    cout << timeToBurnTree(root, 1) << endl;
    return 0;
}