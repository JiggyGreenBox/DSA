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

    // inorder means the root is in the middle
    helper(node->left, res);
    res.push_back(node->data);
    helper(node->right, res);
}

vector<int> inorder(TreeNode* root) {
    vector<int> res;
    helper(root, res);
    return res;
}

// inorder means the root is in the middle
vector<int> inorder_iterative(TreeNode* root) {
    vector<int> res;
    // replace stack of recursion 
    // with an actual stack
    stack<TreeNode*> st;

    // keep pushing left
    // if no left, add node, then push right
    // end when no right and stack empty
    TreeNode* node = root;    
    while (true) {

        // dfs(node)
        //     dfs(node.left)
        //     visit(node)
        //     dfs(node.right)
            
        
        if(node) {  // validate curr node
            st.push(node);
            node = node->left; // push left if it exists
        }
        else{
            // no ancestors, END
            if(st.empty()) break;

            // process ancestors from stack
            node = st.top();
            st.pop();
            res.push_back(node->data);

            // push right, we have gone left and processed root as well
            node = node->right; 
        }
    }
    return res;    
}
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(2);    

    // TreeNode* root = new TreeNode(1);
    // root->right = new TreeNode(2);    
    // root->right->left = new TreeNode(3);

    print(inorder(root));
    print(inorder_iterative(root));
    return 0;
}