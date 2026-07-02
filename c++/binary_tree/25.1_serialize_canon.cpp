#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _data): data(_data), left(nullptr), right(nullptr) {}
};

void dfs(TreeNode* node, string &s) {
    if(!node) {
        s += "#,";
        return;
    }

    s += to_string(node->data) + ",";

    dfs(node->left, s);
    dfs(node->right, s);        
}

string serialize(TreeNode* root) {
    string s;
    dfs(root, s);
    return s;
}

TreeNode* build(vector<string> nodes, int& idx) {
    if(nodes[idx] == "#") {
        idx++;
        return nullptr;
    }

    TreeNode* root = new TreeNode(stoi(nodes[idx++]));
    root->left = build(nodes, idx);
    root->right = build(nodes, idx);    

    return root;
}
TreeNode* deserialize(string data) {

    vector<string> nodes;

    string token;
    stringstream ss(data);

    while(getline(ss, token, ',')) {
        if(!token.empty()) {
            nodes.push_back(token);
        }        
    }
    int idx = 0;
    return build(nodes, idx);
}


int main() {
    string s = "1,2,#,#,3,4,#,#,#,";
    TreeNode* root = deserialize(s);

    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(2);
    // root->right = new TreeNode(3);
    // root->right->left = new TreeNode(4);

    cout << serialize(root) << endl;
    return 0;
}