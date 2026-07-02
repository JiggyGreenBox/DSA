#include <vector>
#include <sstream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int val) {

    if(!root)
        return new TreeNode(val);

    TreeNode* curr = root;

    while(true) {

        if(val < curr->data) {

            if(!curr->left) {
                curr->left = new TreeNode(val);
                break;
            }

            curr = curr->left;
        }
        else {

            if(!curr->right) {
                curr->right = new TreeNode(val);
                break;
            }

            curr = curr->right;
        }
    }

    return root;
}

TreeNode* constructBST(string data) {

    TreeNode* root = nullptr;

    stringstream ss(data);
    int val;

    while(ss >> val) {
        root = insert(root, val);
    }

    return root;
}

TreeNode* constructBST(const vector<int> vals) {

    TreeNode* root = nullptr;

    for(int val : vals)
        root = insert(root, val);    

    return root;
}

/*
Why I changed from getline()
    Your binary tree helper uses:
        getline(ss, item, ' ');
            for null support

For BSTs, every token is just an integer
    int val;
    while(ss >> val)
*/