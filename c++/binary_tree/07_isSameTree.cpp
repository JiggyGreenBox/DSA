#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr){}
};

// recursive
bool isSameTree(TreeNode* p, TreeNode* q) {
    if(!p && !q) return true; // both null
    if(!p || !q) return false; // 1 is null
    if(p->data != q->data) return false;

    return isSameTree(p->left, q->left) && 
           isSameTree(p->right, q->right);
}

// iterative
bool isSameTree_iter(TreeNode* a, TreeNode* b) {
    queue<pair<TreeNode*, TreeNode*>> q;
    q.push({a,b});

    while(!q.empty()) {        
        auto [n1, n2] = q.front();
        q.pop();

        if(!n1 && !n2) continue;                // both null
        if(!n1 || !n2) return false;            // 1 null, false
        if(n1->data != n2->data) return false;  // unequal, false

        q.push({n1->left ,n2->left});
        q.push({n1->right ,n2->right});        
    }
    return true;
}

int main() {
    TreeNode* r1 = new TreeNode(1);
    r1->left = new TreeNode(2);
    r1->right = new TreeNode(3);
    
    TreeNode* r2 = new TreeNode(1);    
    r2->left = new TreeNode(2);
    // r2->right = new TreeNode(3);
    r2->right = new TreeNode(4);

    if(isSameTree_iter(r1, r2)) cout << "same" << endl;
    else cout << "no" << endl;
}