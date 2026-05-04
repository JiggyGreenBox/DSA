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