#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if(!root) return res;

    

    queue<TreeNode*> q;
    q.push(root);
    int c = 0;

    while(!q.empty()) {
        int size = q.size();
        vector<int> level;

        for(int i=0; i<size; i++) {
            TreeNode* node = q.front();
            q.pop();

            level.push_back(node->data);

            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);            
        }
        if(c&1) reverse(level.begin(), level.end());
        c++;
        res.push_back(level);
    }    
    return res;
}


vector<vector<int>> zigzagLevelOrder_cannonical(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;

    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;

    while(!q.empty()) {
        int size = q.size();
        vector<int> level(size);

        for(int i=0; i<size; i++) {
            TreeNode* node = q.front();
            q.pop();

            int idx = (leftToRight) ? i : size-1-i;
            level[i] = node->data;

            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        leftToRight = !leftToRight;
        res.push_back(level);
    }
    return res;
}

void print(const vector<vector<int>>& res) {
    cout << "[ ";
    for(const auto& vec : res) {
        cout << "[ ";
        for(int x : vec) cout << x << " ";
        cout << "] ";
    }
    cout << "]\n";
}

int main() {

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(8);
    root->right->right = new TreeNode(5); // [ [1] , [3, 2], [4, 8, 5] ]

    print(zigzagLevelOrder(root));
    return 0;
}