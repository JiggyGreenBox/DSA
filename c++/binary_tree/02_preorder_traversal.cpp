#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _data): data(_data), left(nullptr), right(nullptr) {}
};

void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

void helper(TreeNode* node, vector<int>& res) {
    if(node == nullptr) return;

    // preorder means the root at the start
    res.push_back(node->data);
    helper(node->left, res);    
    helper(node->right, res);
}

vector<int> preorder(TreeNode* root) {
    vector<int> res;
    helper(root, res);
    return res;
}

// inorder means the root is in the middle
vector<int> preorder_iterative(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    TreeNode* node = root;
    while(true) {
        if(node) {
            st.push(node);
            res.push_back(node->data); // push curr
            node = node->left; // go left till nullptr
        }
        else{
            if(st.empty()) break;
            node = st.top(); 
            st.pop(); // curr from the stack, means no left children
            node = node->right; // try right
        }
    }
    return res;
}
int main() {
    /*
       1
     3
    4 2
    */ 
// 1 3 4 2
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(2);

    /*
     1
       2
      3
    */
    // TreeNode* root = new TreeNode(1);
    // root->right = new TreeNode(2);    
    // root->right->left = new TreeNode(3);

    print(preorder(root));
    print(preorder_iterative(root));
    return 0;
}