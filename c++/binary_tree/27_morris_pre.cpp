#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

vector<int> preorder(TreeNode* root) {
    vector<int> res;
    TreeNode* curr = root;

    while(curr) {
        if(curr->left == nullptr) {
            res.push_back(curr->data);
            curr = curr->right;
        }
        else {
            TreeNode* pred = curr->left;
            while(pred->right && pred->right != curr) {
                pred = pred->right;
            }

            if(pred->right == nullptr) {
                res.push_back(curr->data);  // preorder visit
                pred->right = curr;
                curr = curr->left;
            }
            else {
                pred->right = nullptr;
                curr = curr->right;
            }
        }
    }
    return res;
}
int main() {
    return 0;
}