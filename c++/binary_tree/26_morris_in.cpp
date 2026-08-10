#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};
    /*
       1
     3   99
    4 2
    */ 
//   [ 4 2 3 99 1 ]
vector<int> getInorder(TreeNode* root) {
    vector<int> res;        
    TreeNode* curr = root;

    while(curr) {
        
        // case 1: no left child
        if(curr->left == nullptr) {
            // LrootR
            res.push_back(curr->data);
            curr = curr->right;
        }

        // case 2: left child exists
        else {            
            TreeNode* pred = curr->left;

            // find predecessor
            while(pred->right && pred->right != curr) { // check curr to avoid infinite loops
                pred = pred->right;
            }

            // first time visiting
            if(pred->right == nullptr) {
                pred->right = curr; // create thread
                curr = curr->left;
            }

            // second time visiting
            else {
                pred->right = nullptr;
                res.push_back(curr->data);
                curr = curr->right;
            }
        }
    }

    return res;
}

int main() {
    // 2 pass

    

    return 0;
}

/*
Morris inorder
    inorder is L-N-R
    visit node when creating the thread for preorder
    for inorder we visit node when deleting the thread


    without rec-stack or stack
        need a way to come back to N after L

        we create threads

    curr = root

    while curr
        if left null
            visit curr
            go right
        else
            pred = left
            while pred->left and != curr
                pred = pred->right

            if pred->right == nullptr
                first visit
                pred->right = curr
                curr = curr->left
            else
                second visit
                pred->right = nullptr
                visit(curr)
                curr = curr->right
*/

/*
Morris Traversal

Time  : O(N)
Space : O(1)

Why O(N)?

Every thread
    created once
    removed once

Each right edge
    traversed at most twice

Each node is processed at most twice

Node with left child:
    processed twice

Node without left child:
    processed once

⇒ Every node is processed at most twice.


even for the worst case scenario with all left-children tree
    every node except the last is visited twice

    2N-1 visits

    so TC is <2N


*/