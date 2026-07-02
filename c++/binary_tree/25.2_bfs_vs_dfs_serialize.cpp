#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

// =======================================================
// deserialize for dfs vs bfs
TreeNode* buildTreeBFS(string data) {
    stringstream ss(data);
    string token;
    
    
    getline(ss, token, ',');
    if(token.empty()) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(stoi(token));
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if(getline(ss, token, ',') && !token.empty() && token != "null") {
            node->left = new TreeNode(stoi(token));
            q.push(node->left);
        }

        if(getline(ss, token, ',') && !token.empty() && token != "null") {
            node->right = new TreeNode(stoi(token));
            q.push(node->right);
        }
    }
    return root;
}


TreeNode* dfs_build(const vector<string> &nodes, int &idx) {
    if(nodes[idx] == "null") {
        idx++;
        return nullptr;
    }

    TreeNode* root = new TreeNode(stoi(nodes[idx++]));
    root->left = dfs_build(nodes, idx);
    root->right = dfs_build(nodes, idx);

    return root;
}
TreeNode* buildTreeDFS(string data) {
    vector<string> nodes;
    stringstream ss(data);
    string token;

    while(getline(ss, token, ',')) {
        if(!token.empty()) {
            nodes.push_back(token);
        }
    }
    int idx=0;
    return dfs_build(nodes, idx);
}
// =======================================================
// serialize dfs vs bfs
void dfs_ser(TreeNode* node, string& s) {

    if(!node) {
        // s += "#,";
        s += "null,";
        return;
    }

    s += to_string(node->data) + ",";

    dfs_ser(node->left, s);
    dfs_ser(node->right, s);
}

string serialize_dfs(TreeNode* root) {

    string s;
    dfs_ser(root, s);
    return s;
}


string serialize_bfs(TreeNode* root) {

    if(!root)
        return "";

    string s;

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {

        TreeNode* node = q.front();
        q.pop();

        if(node == nullptr) {

            s += "null,";
            continue;
        }

        s += to_string(node->data) + ",";

        q.push(node->left);
        q.push(node->right);
    }

    // optional trim
    // --------------------------------
    vector<string> nodes;
    string token;
    stringstream ss(s);
    while (getline(ss, token, ',') && !token.empty()) {
        nodes.push_back(token);
    }
    while(!nodes.empty() && nodes.back() == "null") {
        nodes.pop_back();
    }

    s = "";
    for(auto &t : nodes)
        s += t + ",";
    // --------------------------------    

    return s;
}


int main() {
    // TreeNode* root = buildTreeBFS("1,2,null,3,null,");
    TreeNode* root = buildTreeBFS("1,2,null,3,");
    cout << serialize_bfs(root) << endl;
    

    TreeNode* root2 = buildTreeDFS("1,2,null,3,null,null,null,");
    cout << serialize_dfs(root2) << endl;
    int x = 5;
    return 0;
}