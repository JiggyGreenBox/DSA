#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

void dfs(TreeNode* node, int col, map<int,int>& mpp) {
    if(!node) return;

    if(mpp.find(col) == mpp.end()){
        mpp[col] = node->data;
    }

    dfs(node->left, col-1, mpp);
    dfs(node->right, col+1, mpp);
}

void bfs(TreeNode* node, map<int,int>& mpp) {
    if(!node) return;
    queue<pair<TreeNode*,int>> q;
    q.push({node, 0});

    while(!q.empty()) {
        auto [node, col] = q.front();
        q.pop();        

        if(mpp.find(col) == mpp.end())
            mpp[col] = node->data;

        if(node->left) 
            q.push({node->left, col-1});

        if(node->right) 
            q.push({node->right, col+1});
    }
}

vector<int> topView(TreeNode *root) {
    vector<int> res;
    if(!root) return res;

    // we dont track row because, once a col
    // has been tracked, no lower value
    // will be visible from the top

    //  col, val    
    map<int, int> mpp;
    // dfs(root, 0, mpp); // this does not work for some cases
    //     1
    //    / \
    //   2   3
    //    \
    //     4
    //      \
    //       5
    bfs(root, mpp);

    // 3 and not 5 should be the top view
    // so bfs is better

    for(auto& p : mpp) {
        res.push_back(p.second);
    }
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
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7); // [4, 2, 1, 3, 7]

    print(topView(root));
    return 0;
}