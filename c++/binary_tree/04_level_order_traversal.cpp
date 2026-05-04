#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _data) : data(_data), left(nullptr), right(nullptr) {}
};

// level starts at 0
void helper(TreeNode* node, int level, vector<vector<int>>& res) {

    if(!node) return;

    // create empty vector
    if(res.size() == level) {
        res.push_back({});
    }

    res[level].push_back(node->data);
    helper(node->left, level+1, res);
    helper(node->right, level+1, res);
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    helper(root, 0, res);
    return res;
}

void print(const vector<vector<int>>& res) {
    cout << "[ ";
    for(auto &vec : res){
        cout << "[ ";
        for(int x : vec) cout << x << " ";
        cout << "] ";
    }
    cout << "]\n";
}


vector<vector<int>> levelOrder_cannonical(TreeNode* root) {
    vector<vector<int>> res;
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {

        // bit gotcha here with size
        int size = q.size();

        vector<int> level;

        for(int i=0; i<size; i++) {
            TreeNode* node = q.front();
            q.pop();

            level.push_back(node->data);
            
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }

        res.push_back(level);
    }
    return res;
}

int main() {

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    print(levelOrder(root));
    print(levelOrder_cannonical(root));
}