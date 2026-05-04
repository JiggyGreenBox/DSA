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

// we need access to the parent 
// we need to recursively find the node and delete in the same call
// to have access to the parent
TreeNode* deleteNode(TreeNode* root, int key) {
    if(!root) return nullptr;

    if(key > root->data) {
        root->right = deleteNode(root->right, key);        
    }
    else if(key < root->data) {
        root->left = deleteNode(root->left, key);        
    }
    else {
        // delete cases
        // 0,1,2 children
        if(!root->left && !root->right) {
            // 0 child
            delete root;
            return nullptr;
        }
        else if(!root->left || !root->right) {
            // 1 child
            TreeNode* copy = (root->left) ? root->left : root->right;
            delete root;
            return copy;
        }
        else{
            // 2 children
            TreeNode* pred = root->right;
            while(pred->left) pred = pred->left;

            // pred must be moved into root position
            // then successor must be deleted
            root->data = pred->data;
            root->right = deleteNode(root->right, pred->data);
        }
    }  
    return root;  
}

TreeNode* deleteNode_cannon(TreeNode* root, int key) {
    if(!root) return nullptr;
    if(key < root->data) {
        root->left = deleteNode_cannon(root->left, key);
    }
    else if(key > root->data) {
        root->right = deleteNode_cannon(root->right, key);
    }
    else {
        // node found

        // no L/R child case also handles 0 children case
        // important that the return prevents further checks

        // 1. no left child
        if(!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }

        // 2. no right child
        if(!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // 3. both children exist
        TreeNode* succ = root->right;
        while(succ->left) succ = succ->left;

        root->data = succ->data;
        root->right = deleteNode_cannon(root->right, succ->data);
    }
    return root;
}


int main() {
    TreeNode* root = constructTree("5 3 6 2 4 null 7");
    // root = deleteNode(root, 0);
    root = deleteNode(root, 3);
    int x = 5;
    return 0;
}