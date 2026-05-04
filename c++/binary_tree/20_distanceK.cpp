#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    vector<int> ans;
    if(!root || !target || k==0) return ans;

    // turn tree into graph
    // by allowing child-parent mapping    
    unordered_map<TreeNode*, TreeNode*> mpp;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        auto node = q.front();
        q.pop();        

        if(node->left) {
            mpp[node->left] = node;
            q.push(node->left);
        } 
        if(node->right) {
            mpp[node->right] = node;
            q.push(node->right);
        }
    }

    // we have a target given
    // push into queue
    // push into visited    
    unordered_set<TreeNode*> visited;
    int dist=0;
    q.push(target);
    visited.insert(target);

    while(dist<k) {
        int size = q.size();
        dist++;

        for(int i=0; i<size; i++) {
            TreeNode* node = q.front();
            q.pop();

            if(node->left && visited.count(node->left) == 0) {
                q.push(node->left);
                visited.insert(node->left);
            } 
            if(node->right && visited.count(node->right) == 0) {
                q.push(node->right);
                visited.insert(node->right);                
            }
            if(mpp[node] && visited.count(mpp[node]) == 0) {
                q.push(mpp[node]);
                visited.insert(mpp[node]);
            }
        }        
    }

    while(!q.empty()) {
        ans.push_back(q.front()->data);
        q.pop();
    }

    return ans;
}

void print(const vector<int>& res) {
    cout << "[ ";
    for(int x : res) cout << x << " ";
    cout << "]\n";
}

int main() {

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);    


    print(distanceK(root, root->left, 2));
    return 0;
}