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
    if(item.empty()) return nullptr;

    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if(getline(ss, item, ' ')) {
            if(!item.empty() && item != "null") {
                node->left = new TreeNode(stoi(item));
                q.push(node->left);
            }
        }

        if(getline(ss, item, ' ')) {
            if(!item.empty() && item != "null") {
                node->right = new TreeNode(stoi(item));
                q.push(node->right);
            }
        }
    }
    return root;
}


/*
Inorder successor and predecessor in BST

    Given the root node of a binary search tree (BST) and an integer key. 
    Return the Inorder predecessor and successor of the given key from 
    the provided BST.

    Note: key will always present in given BST.

    If predecessor or successor is missing then return -1.
*/

/*
Inorder Successor in BST

Successor = next larger value in inorder traversal.

Case 1:
--------
Target has a right subtree.

        5
         \
          7
         /
        6

Next inorder node is the smallest node in the right subtree.

successor = leftmost(right subtree)

------------------------------------------------------------

Case 2:
--------
Target has no right subtree.

        8
       /
      5
       \
        7

Searching for 7:

8
↓ left   successor = 8

5
↓ right

7

No right subtree.

Answer = last ancestor where we turned LEFT.

Reason:
Every left turn means current node > target.
It is a candidate successor.
We keep updating because a later left turn gives a smaller candidate.

Algorithm:
----------
curr = root

while(curr)

    if(target < curr->data)
        successor = curr
        curr = curr->left

    else if(target > curr->data)
        curr = curr->right

    else
        if(curr->right)
            successor = leftmost(curr->right)
        break
*/

// lets combine both
TreeNode* rightMost(TreeNode* node) {
    while(node->right) {
        node = node->right;
    }
    return node;
}

TreeNode* leftMost(TreeNode* node) {
    while(node->left) {
        node = node->left;
    }
    return node;
}

vector<int> succPredBST(TreeNode* root, int key) {
    int pred = -1, succ = -1;

    TreeNode* curr = root;

    while(curr) {
        if(key < curr->data) {
            pred = curr->data;
            curr = curr->right;
        }
        else if(key > curr->data) {
            succ = curr->data;
            curr = curr->left;
        }
        else {
            // found target

            // pred
            if(curr->left) {
                pred = rightMost(curr->left)->data;
            }

            // succ
            if(curr->right) {
                succ = leftMost(curr->right)->data;
            }
            break;
        }
    }
    return {pred, succ};
}

int main() {
    return 0;
}