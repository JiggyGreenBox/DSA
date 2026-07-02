#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

void left_boundary(TreeNode* node, vector<int>& res) {
    // if a node has a left, or a right
    // it is a non leaf node
    if(node->left) {
        res.push_back(node->data);
        left_boundary(node->left, res);
    }
    else if(node->right) {
        res.push_back(node->data);
        left_boundary(node->right, res);
    }
}

void right_boundary(TreeNode* node, vector<int>& res) {
    // if a node has a left, or a right
    // it is a non leaf node
    if(node->right) {        
        right_boundary(node->right, res);
        res.push_back(node->data);
    }
    else if(node->left) {        
        right_boundary(node->left, res);
        res.push_back(node->data);
    }
}

// this is not correct
// because the order is not correct
// void get_leaves(TreeNode* root, vector<int>& res) {
//     queue<TreeNode*> q;
//     q.push(root);
//     while(!q.empty()) {
//         int size = q.size();
//         for(int i=0; i<size; i++) {
//             TreeNode* node = q.front();
//             q.pop();

//             if(!node->left && !node->right) res.push_back(node->data);

//             if(node->left) q.push(node->left);
//             if(node->right) q.push(node->right);
//         }   
//     }
// }

void get_leaves(TreeNode* node, vector<int>& res) {
    if(!node) 
        return;

    if(!node->left && !node->right) 
        res.push_back(node->data);

    get_leaves(node->left, res);
    get_leaves(node->right, res);
}

vector<int> boundary(TreeNode* root) {
    
    if(!root) 
        return {};

    if(!root->left && !root->right) 
        return {root->data};


    vector<int> res;
    
    res.push_back(root->data);
    
    left_boundary(root->left, res);

    get_leaves(root, res);
    
    right_boundary(root->right, res);    
    return res;    
}

void print(const vector<int>& res) {
    cout << "[ ";
    for(auto x : res) cout << x << " ";
    cout << "]\n";
}

/*
canonical iterative solution
----------------------------------------------------------
*/
bool isLeaf(TreeNode* node) {
    return node && !node->left && !node->right;
}
void addLeftBoundary(TreeNode* node, vector<int>& ans) {
    while(node) {
        if(!isLeaf(node))
            ans.push_back(node->data);

        if(node->left)
            node = node->left;
        else
            node = node->right;
    }
}
void addLeaves(TreeNode* node, vector<int>& ans) {
    if(!node)
        return;

    if(isLeaf(node)) {
        ans.push_back(node->data);
        return;
    }

    addLeaves(node->left, ans);
    addLeaves(node->right, ans);
}
void addRightBoundary(TreeNode* node, vector<int>& ans) {
    vector<int> temp;

    while(node) {
        if(!isLeaf(node))
            temp.push_back(node->data);

        if(node->right)
            node = node->right;
        else
            node = node->left;
    }

    reverse(temp.begin(), temp.end());

    ans.insert(ans.end(), temp.begin(), temp.end());
}
vector<int> boundaryTraversal(TreeNode* root) {

    vector<int> ans;

    if(!root)
        return ans;

    if(!isLeaf(root))
        ans.push_back(root->data);

    addLeftBoundary(root->left, ans);
    addLeaves(root, ans);
    addRightBoundary(root->right, ans);

    return ans;
}
// ----------------------------------------------------------

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(8);
    root->left->right->right = new TreeNode(9);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);    

    print(boundary(root));     

    return 0;
}