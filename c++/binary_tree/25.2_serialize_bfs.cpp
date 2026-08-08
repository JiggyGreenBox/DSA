#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _data): data(_data), left(nullptr), right(nullptr) {}
};

//--------------------------------------------------
// Serialize
//--------------------------------------------------

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

            s += "#,";
            continue;
        }

        s += to_string(node->data) + ",";

        q.push(node->left);
        q.push(node->right);
    }

    return s;
}

//--------------------------------------------------
// Deserialize
//--------------------------------------------------

TreeNode* deserialize_bfs(string data) {

    if (data.empty())
        return nullptr;

    stringstream ss(data);
    string token;

    getline(ss, token, ',');

    TreeNode* root = new TreeNode(stoi(token));

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {

        TreeNode* node = q.front();
        q.pop();

        if (getline(ss, token, ',') &&
            token != "#" &&
            !token.empty()) {

            node->left = new TreeNode(stoi(token));
            q.push(node->left);
        }

        if (getline(ss, token, ',') &&
            token != "#" &&
            !token.empty()) {

            node->right = new TreeNode(stoi(token));
            q.push(node->right);
        }
    }

    return root;
}

int main() {
    string s = "1,2,#,#,3,4,#,#,#,";
    TreeNode* root = deserialize_bfs(s);

    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(2);
    // root->right = new TreeNode(3);
    // root->right->left = new TreeNode(4);

    cout << serialize_bfs(root) << endl;
    return 0;
}