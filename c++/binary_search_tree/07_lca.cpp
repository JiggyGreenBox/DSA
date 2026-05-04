#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}    
};

TreeNode* constructTree(string data) {
    stringstream ss(data);
    string item;
    getline(ss, item, ' ');

    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if(getline(ss, item, ' ')) {
            if(item != "null" && !item.empty()) {
                node->left = new TreeNode(stoi(item));
                q.push(node->left);
            }
        }

        if(getline(ss, item, ' ')) {
            if(item != "null" && !item.empty()) {
                node->right = new TreeNode(stoi(item));
                q.push(node->right);
            }
        }
    }
    return root;
}

void print(TreeNode* node) {
    if(node) cout << node->data << endl;
    else cout << "NULL" << endl;
}

TreeNode* lca(TreeNode* root, int p, int q) {
    // lca will be the node where
    // p < node < q

    if(!root) return nullptr;

    // answer in left subtree
    if(root->data > p && root->data > q) {
        return lca(root->left, p, q);
    }

    // answer in right subtree
    if(root->data < p && root->data < q) {
        return lca(root->right, p, q);
    }
    
    // answer is current node
    return root;    
}

int main() {
    TreeNode* root = nullptr;

    root = constructTree("5 3 6 2 4 null 7");
    print(lca(root, 2, 4));

    root = constructTree("5 3 6 2 4 null 7");
    print(lca(root, 2, 7));

    root = constructTree("10 5 14 1 9 11 19");
    print(lca(root, 1, 11));
    
    return 0;
}