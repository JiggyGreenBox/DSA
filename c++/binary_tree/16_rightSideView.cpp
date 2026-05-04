#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

vector<int> rightSideView(TreeNode* root) {
    vector<int> res;
    if(!root) return res;

    map<int, pair<int, int>> mpp;

    // node, pair<X,Y>
    queue<pair<TreeNode*, pair<int,int>>> q;
    q.push({root, {0,0}});

    while(!q.empty()) {
        auto front = q.front();
        q.pop();

        TreeNode* node = front.first;
        int row = front.second.first;
        int col = front.second.second;

        // no entry, or newer col is more right
        if( (mpp.find(row) == mpp.end()) || 
            (mpp[row].first < col) )
        {
            mpp[row] = {col, node->data};
        }        
        
        if(node->left) q.push({node->left, {row+1, col-1}});
        if(node->right) q.push({node->right, {row+1, col+1}});
    }

    for(auto& [row, pair] : mpp) {
        res.push_back(pair.second);
    }

    return res;
}

// earlier solution was too over-engineered
// we dont need to track nodes column-wise
// we only process at each level
vector<int> rightSideView_cannonical(TreeNode* root) {
    vector<int> res;
    if(!root) return res;

    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int size = q.size();
        
        for(int i=0; i<size; i++){
            TreeNode* node = q.front();
            q.pop();

            // node is last of the level
            if(i == size-1) {
                res.push_back(node->data);
            }

            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
    }
    return res;
}

void dfs(TreeNode* node, int level, vector<int>& res) {
    if(!node) return;

    if(res.size() == level) {
        res.push_back(node->data);
    }    
    dfs(node->right, level+1, res);
    dfs(node->left, level+1, res);
}

vector<int> rightSideView_cannonical_dfs(TreeNode* root) {
    vector<int> res;
    if(!root) return res;

    dfs(root, 0, res);
    return res;
}

void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4); // [1, 3, 4]

    print(rightSideView(root));
    print(rightSideView_cannonical_dfs(root));
    
    return 0;
}