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

int helper(TreeNode* node) {
    if(!node) return 0;
    int left_h = 1 + helper(node->left);
    int right_h = 1 + helper(node->right);
    return max(left_h, right_h);
}

int maxDepth_rec(TreeNode* root) {
    if(!root) return 0;    
    return helper(root);
}

// we need a dfs search
// compare left and right at each state
int maxDepth_iter_stack(TreeNode* root) {
    if(!root) return 0;

    int max_depth = 0;
    // at each node, get max_left, max_right
    stack<pair<TreeNode*, int>> st;
    st.push({root, 1});

    while(!st.empty()) {
        auto [node, depth] = st.top();
        st.pop();

        max_depth = max(max_depth, depth);
        

        if(node->left) {
            st.push({node->left, depth + 1});
        }

        if(node->right) {
            st.push({node->right, depth + 1});
        }
    }
    return max_depth;
}

int maxDepth_rec_cannonical(TreeNode* root) {
    if(!root) return 0;
    return 1 + max(maxDepth_rec_cannonical(root->left), maxDepth_rec_cannonical(root->right));
}

// Each loop processes one level
int maxDepth_iter_queue(TreeNode* root) {
    if(!root) return 0;

    queue<TreeNode*> q;
    q.push(root);
    int depth = 0;

    while(!q.empty()) {

        int size = q.size();
        depth++;

        for(int i=0; i<size; i++) {
            TreeNode* node = q.front();
            q.pop();

            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }        
    }
    return depth;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(6);
    cout << maxDepth_rec(root) << endl;
    cout << maxDepth_iter_stack(root) << endl;

    cout << maxDepth_rec_cannonical(root) << endl;
    cout << maxDepth_iter_queue(root) << endl;
    return 0;
}