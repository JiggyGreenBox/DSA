#include <iostream>
#include <stack>
#include <optional>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _data): data(_data), left(nullptr), right(nullptr) {}
};
TreeNode* buildTree(const vector<optional<int>> &arr) {
    if(arr.empty() || !arr[0].has_value())
        return nullptr;

    TreeNode* root = new TreeNode(arr[0].value());
    queue<TreeNode*> q;
    q.push(root);

    int i = 1; // used to access arr indx

    while(!q.empty() && i<arr.size()) {
        TreeNode* curr = q.front();
        q.pop();

        // left child
        if(i<arr.size() && arr[i].has_value()) {
            curr->left = new TreeNode(arr[i].value());
            q.push(curr->left);
        }
        i++;

        // right child
        if(i<arr.size() && arr[i].has_value()) {
            curr->right = new TreeNode(arr[i].value());
            q.push(curr->right);
        }
        i++;
    }
    return root;
}


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

vector<int> inorder_iterative_canon(TreeNode* root) {
    vector<int> ans;    
    stack<TreeNode*> st;
    TreeNode* curr = root;

    while(curr || !st.empty()) {

        while(curr) {
            st.push(curr);
            curr = curr->left;
        }

        curr = st.top();
        st.pop();

        ans.push_back(curr->data);

        curr = curr->right;
    }
    return ans;
}

int main() {
    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(3);
    // root->left->left = new TreeNode(4);
    // root->left->right = new TreeNode(2);

    vector<optional<int>> v = {1, 3, nullopt, 4, 2};
    TreeNode* root = buildTree(v);

    // TreeNode* root = new TreeNode(1);
    // root->right = new TreeNode(2);    
    // root->right->left = new TreeNode(3);

    print(inorder(root));
    print(inorder_iterative_canon(root));
    
    return 0;
}

/*
INORDER
dfs(node)
    if(!node) return
    dfs(node->left)
    visit()
    dfs(node->right)

dfs(node)
    store and go left

    get from storage
    visit
    try right subtree
  
    stack st
    curr = root
    while (curr and stack)
        while curr
            store
            curr = left
        
        curr = st
        curr = right
------------------------------
PREORDER
N-L-R
dfs(node)
    if(!node) return
    visit()
    dfs(node->left)    
    dfs(node->right)

    
    stack st
    st.push root

    while st
        node = top
        pop
        visit

        if right
            st right

        if left
            st left

------------------------------
POSTORDER

L-R-N
    notice preorder is N-L-R
    we make N-R-L
    then reverse is postorder

    stack st
    st push root

    while st
        node = top
        ans.push

        if left
            st push left
        if right
            st push right
    reverse ans


POSTORDER single stack
left tree
right tree
visit

curr = root
while curr and stack
    if(curr)
        push(curr)
        curr = curr->left

    else
        get parent from stack

        if right subtree and not processed:
            go right
        else
            visit node
            mark visited
            pop


Inorder
    Keep going left.
    Pop one node and visit it.
    Explore its right subtree.

Preorder
    same as inorder but visit before going left
*/