#include <iostream>
#include <vector>
#include <sstream>
#include <climits>
#include <queue>
#include <stack>
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

// root-Left-Right
TreeNode* helper(const vector<int>& preorder,
                 int& idx,
                 int min_val,
                 int max_val)
{
    if(idx >= preorder.size()) return nullptr;

    if(preorder[idx] <= min_val || preorder[idx] >= max_val) return nullptr;

    TreeNode* node = new TreeNode(preorder[idx]);
    idx++;
    
    node->left = helper(preorder, idx, min_val, node->data);
    node->right = helper(preorder, idx, node->data, max_val);

    return node;
}

TreeNode* bstFromPreorder(const vector<int>& preorder) {
    int n = preorder.size();
    if(n == 0) return nullptr;

    // we use ranges
    // similar to isBST    
    int idx=0;    
    return helper(preorder, idx, INT_MIN, INT_MAX);
}


// 8, 5, 1, 7, 10, 12
//   8
//  5
// 1

TreeNode* monotonic_stackBST(const vector<int>& preorder) {
    if(preorder.empty()) return nullptr;
    TreeNode* root = new TreeNode(preorder[0]);
    stack<TreeNode*> st;
    st.push(root);
    int n = preorder.size();

    for(int i=1; i<n; i++) {
        TreeNode* node = new TreeNode(preorder[i]);
        if(st.top()->data > node->data) {
            st.top()->left = node;
        }
        else {
            TreeNode* parent = nullptr;
            while(!st.empty() && st.top()->data < preorder[i]) {
                parent = st.top();
                st.pop();
            }
            parent->right = node;
        }
        st.push(node);
    }
    return root;
}

int main() {
    TreeNode* root = nullptr;

    
    // root = bstFromPreorder({8 ,5 ,1 ,7 ,10, 12});
    root = monotonic_stackBST({8 ,5 ,1 ,7 ,10, 12});
    int x = 5;
    return 0;
}

