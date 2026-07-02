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

// ======================================================
void inorder(TreeNode* node, int &k, int& ans) {
    if(!node || k==0)
        return;

    inorder(node->left, k, ans);

    if(--k == 0) {
        ans = node->data;
        return;
    }

    inorder(node->right, k, ans);        
}
int kSmallest_canon(TreeNode* root, int k) {
    int ans = -1;
    inorder(root, k, ans);
    return ans;
}

// we want an inverted inorder
// right-root-left
void reverseInorder(TreeNode* node, int &k, int& ans) {
    if(!node || k == 0)
        return;

    reverseInorder(node->right, k, ans);

    if(--k == 0) {
        ans = node->data;
        return;
    }

    reverseInorder(node->left, k, ans);
}
int kLargest_canon(TreeNode* root, int k) {    
    int ans = -1;
    reverseInorder(root, k, ans);
    return ans;
}

vector<int> kLargesSmall(TreeNode* root, int k) {

    int small = kSmallest_canon(root, k);

    int large = kLargest_canon(root, k);
    
    return {small, large};        
}

// ======================================================




void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

int kSmallest(TreeNode* root, int k, int& counter) {
    
    if(!root) return -1;

    int left = kSmallest(root->left, k, counter);
    if(left != -1) return left;
    
    counter++; // increment when going to a larger element
    if(counter == k) return root->data;    
    
    return kSmallest(root->right, k, counter);    
}

// we want an inverted inorder
// right-root-left
int kLargest(TreeNode* root, int k, int& counter) {
    
    if(!root) return -1;

    int left = kLargest(root->right, k, counter);
    if(left != -1) return left;
    
    counter++; // increment when going to a smaller element
    if(counter == k) return root->data;    
    
    return kLargest(root->left, k, counter);    
}

vector<int> kLargesSmall(TreeNode* root, int k) {        
    int counter = 0;
    int smallest = kSmallest(root, k, counter);

    counter = 0;
    int largest = kLargest(root, k, counter);    
    
    return {smallest, largest};
}

int main() {
    int k=0;
    TreeNode* root = nullptr;

    root = constructTree("3 1 4 null 2"); k = 1;
    print(kLargesSmall(root, k));

    root = constructTree("5 3 6 2 null null null 1"); k = 3;
    print(kLargesSmall(root, k));

    root = constructTree("10 5 14 1 9 11 19"); k = 2;
    print(kLargesSmall(root, k));
        
    return 0;
}