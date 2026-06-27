#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _data) : data(_data), left(nullptr), right(nullptr) {}
};


int maxDepth_rec(TreeNode* root) {
    if(!root) 
        return 0;    

    return 1 + max(
        maxDepth_rec(root->left),
        maxDepth_rec(root->right)
    );
}


// Each loop processes one level
int maxDepth_iter(TreeNode* root) {

    if(!root) 
        return 0;

    queue<TreeNode*> q;
    q.push(root);

    int height = 0;

    while(!q.empty()) {

        int size = q.size();        

        while(size--) {
            TreeNode* node = q.front();
            q.pop();

            if(node->left) 
                q.push(node->left);

            if(node->right) 
                q.push(node->right);
        }       

        height++;
    }
    return height;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(6);
    
    cout << maxDepth_rec(root) << endl;
    cout << maxDepth_iter(root) << endl;

    return 0;
}