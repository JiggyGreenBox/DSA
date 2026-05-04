#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
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

vector<int> floorCeilOfBST(TreeNode* root, int key) {
    int floor = -1, ceil = -1;

    while (root) {
        // decide left or right
        // floor < target < ceil

        if(root->data == key) {
            return {key, key};
        }
        // check larger values of tree
        if(root->data < key) {
            // go right            
            floor = root->data;
            root = root->right;
        }
        // check smaller values of tree
        else {
            // go left
            ceil = root->data;
            root = root->left;
        }
    }
    return {floor, ceil};
}

vector<int> floorCeilOfBST_high_performance(TreeNode* root, int key) {
    int floor = -1, ceil = -1;

    while (root) {
        // decide left or right
        // floor < target < ceil

        if(root->data <= key) {
            floor = root->data;
            if(root->data == key) {
                ceil = root->data;
                break;
            }
            root = root->right;
        }
        // check smaller values of tree
        else {            
            ceil = root->data;
            root = root->left;
        }
    }
    return {floor, ceil};
}

void print(const vector<int>& vec) {
    cout << "[ ";
    for(auto x : vec) cout << x << " ";
    cout << "]\n";
}

int main() {
    TreeNode* root = constructTree("8 4 12 2 6 10 14");    
    
    print(floorCeilOfBST(root, 15));
    return 0;
}