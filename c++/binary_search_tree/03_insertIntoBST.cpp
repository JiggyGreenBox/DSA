#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
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

// O(h) time
// O(1) space
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if(!root) 
        return new TreeNode(val);

    // put val at an appropriate leaf node
    TreeNode* curr = root;

    // less than curr and no left
    // insert return
    // else go left

    // greater than curr and no right
    // insert return
    // else go right
    while(curr) {
        if(curr->data > val) {
            if(!curr->left) {
                curr->left = new TreeNode(val);
                break;
            }
            curr = curr->left;
        }
        else{
            if(!curr->right) {
                curr->right = new TreeNode(val);
                break;
            }
            curr = curr->right;
        }
    }

    return root;
}

// O(h) time
// O(h) space
TreeNode* insert(TreeNode* root, int val) {
    if(!root) 
        return new TreeNode(val);

    if(val < root->data) {
        root->left = insert(root->left, val);
    }
    else {
        root->right = insert(root->right, val);
    }
    return root;
}


// we have simplified null checks
    // if(!curr->left) curr->left = new TreeNode(val);
    // if(!curr->right) curr->right = new TreeNode(val);
    // if(!root) root = new TreeNode(val);

// With the pointer-to-pointer approach, 
// the traversal always points to the pointer 
// that might become the new node:
    // while(*curr)
    // When that pointer becomes nullptr, you simply do:
        // *curr = new TreeNode(val);
// Instead of navigating nodes, we navigate the pointers that connect nodes.
TreeNode* insertIntoBST(TreeNode* root, int val) {
    TreeNode** curr = &root;
    while(*curr) {
        if(val > (*curr)->data) {
            curr = &((*curr)->right);
        }
        else{
            curr = &((*curr)->left);
        }
    }
    *curr = new TreeNode(val);
    return root;
}

int main() {
    // TreeNode* root = constructTree("4 2 7 1 3");
    TreeNode* root = constructTree("4 2 7 1");
    //   4
    //  2 7
    // 1
    
    insertIntoBST(root, 3);
    return 0;
}
