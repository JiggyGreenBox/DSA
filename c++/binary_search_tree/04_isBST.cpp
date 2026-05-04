#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <stack>
#include <climits>
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

    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if(getline(ss, item, ' ')) {
            if(item != "null" && !item.empty()) {
                node->left = new TreeNode(stoi(item));
                q.push(node->left);
            }
        }

        if(getline(ss, item, ' ')) {
            if(item != "null" && !item.empty()) {
                node->right = new TreeNode(stoi(item));
                q.push(node->right);
            }
        }
    }
    return root;
}

// this code is wrong because
// the tree must have global state
// not just children == left < node < right
// for eg
    //   10
    //   /  \
    //  5    15
    //      /
    //     6
    // this code will return true
    // but 6 is right of 10, invalid
    // we need to propogate 10 down the right side as min
    // and 10 down the left side as max
bool isBST_wrong(TreeNode* root) {
    // foreach node, check if left < node < right
    if(!root) return true;

    if(root->left && root->left->data > root->data) return false;
    if(root->right && root->right->data < root->data) return false;

    return isBST_wrong(root->left) && isBST_wrong(root->right);
}

bool helper(TreeNode* node, int min_val, int max_val) {
    if(!node) return true;

    if(node->data <= min_val || node->data >= max_val) return false;

    return helper(node->left, min_val, node->data) && helper(node->right, node->data, max_val);
}

bool isBST(TreeNode* root) {
    return helper(root, INT_MIN, INT_MAX);
}


// inorder BT
// dfs(node)
//     if(!node) return
//     dfs(node->left)
//     print(node)
//     dfs(node->right)

// If you want a tiny exercise (good test)
// Try to mentally simulate the inorder validation for:
//       8
//      / \
//     3   10
//    / \
//   1   6
//      / \
//     4   7
//     Track:
//         prev
//         current


// 8
//     L(3)
//         L(1) visit(1) prev=null, curr=1
//         visit(3) prev=1, curr=3
//         R(6)
//             L(4) visit(4) prev=3, curr=4
//             visit(6) prev=4, curr=6
//             R(7) visit(7) prev=6, curr=7
//     visit(8) prev=7, curr=8
//     R(10) visit(10) prev=8, curr=10
    

bool isBST_inorder(TreeNode* node, TreeNode*& prev) {
    if(!node) return true;

    if(!isBST_inorder(node->left, prev)) return false;

    if(prev && node->data <= prev->data) return false;

    prev = node;

    // if(!isBST_inorder(node->right, prev)) return false;
    // return true;
    
    return isBST_inorder(node->right, prev);    
}


bool isBST_iterative(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;
    TreeNode* prev = nullptr;

    while(curr || !st.empty()) {
        // dfs(node)
        //      dfs(node->left)
        //      visit(node)
        //      dfs(node->right)

        // dfs(node)
        //      dfs(node->left) 
        //            need node on stack, for right access later
        //      visit(node)
        //            compare with prev
        //            update prev here
        //      dfs(node->right)

        // keep going left
        while(curr) {
            st.push(curr);
            curr = curr->left;
        }

        curr = st.top();
        st.pop();

        if(prev && curr->data <= prev->data) return false;
        prev = curr;

        // go right
        curr = curr->right;
    }
    return true; // all nodes passed test
}


bool isBST_morris(TreeNode* root) {
    /*
    Morris logic

    while(curr)
        if no left
            visit(curr)
            go right
        else
            find inorder pred

            
            if pred->right == nullptr
                thread it
                go left
            else
                remove thread
                visit
                go right
    
    */

    TreeNode* curr = root;
    TreeNode* prev = nullptr;
    while(curr) {        
        if(!curr->left) {
            if(prev && prev->data >= curr->data) return false;
            prev = curr;
            curr = curr->right;
        }
        else {
            TreeNode* pred = curr->left;            
            while(pred->right && pred->right != curr) { // check curr to avoid infinite loops
                pred = pred->right;
            }

            if(pred->right == nullptr) {
                pred->right = curr;  
                curr = curr->left;              
            }
            else{
                pred->right = nullptr;
                if(prev && prev->data >= curr->data) return false;
                prev = curr;
                curr = curr->right;
            }
        }
    }
    return true;
}

int main() {
    
    TreeNode* root = constructTree("5 3 6 2 4 null 7");
    // TreeNode* root = constructTree("5 3 6 4 2 null 7");
    
    //    5
    //  3  6
    // 2 4  7
    TreeNode* prev = nullptr;
    // bool result = isBST_inorder(root, prev);
    bool result = isBST_morris(root);    

    if(result) cout << "isBST" << endl;
    else cout << "is NOT BST" << endl;
    return 0;
}