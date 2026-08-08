#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

TreeNode* dfs(int root_idx, int start, int end,
              const vector<int>& preorder, 
              const vector<int>& inorder) {
    int n = preorder.size();
    if(root_idx >= n) return nullptr;
    if(start > end) return nullptr;
    
    // create node, using root_idx from preorder
    TreeNode* node = new TreeNode(preorder[root_idx]);

    auto it = std::find(inorder.begin(), inorder.end(), preorder[root_idx]);
    if (it == inorder.end()) return nullptr;

    // find node idx in inorder
    int in_idx = distance(inorder.begin(), it);
    if(in_idx < 0) return node;

    // get length of left children
    int left_len = in_idx - start + 1;

    TreeNode* left_child = dfs(root_idx+1, start, in_idx-1, preorder, inorder);
    if(left_child) node->left = left_child;

    TreeNode* right_child = dfs(root_idx+left_len, in_idx+1, end, preorder, inorder);
    if(right_child) node->right = right_child;

    return node;
}

TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
    return dfs(0,0,preorder.size()-1, preorder, inorder);
}

void printLevels(TreeNode* root) {
    if(!root) return;
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int size = q.size();

        cout << "[";

        for(int i=0; i<size; i++) {
            TreeNode* node = q.front();
            q.pop();

            cout << node->data << " ";

            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        cout << "]\n";
    }
}


//================================================================================

TreeNode* build(const vector<int>& preorder, 
                const vector<int>& inorder,
                int preL,
                int inL,
                int inR,
                unordered_map<int, int> &inMap ) {

    if(inL > inR)
        return nullptr;

    TreeNode* root = new TreeNode(preorder[preL]);

    int k = inMap[preorder[preL]];
    int left_size = k - inL;

    root->left = build( preorder,
                        inorder,
                        preL + 1,
                        inL,
                        k-1,
                        inMap);

    root->right = build( preorder,
                        inorder,
                        preL + left_size + 1,
                        k + 1,
                        inR,
                        inMap);

    return root;
}

TreeNode* buildTree_canon(const vector<int>& preorder, const vector<int>& inorder) {
    unordered_map<int, int> inMap; // node to index mapping, for O(1) search
    for(int i=0; i<inorder.size(); i++) {
        inMap[inorder[i]] = i;
    }

    return build(preorder,
                 inorder,
                 0,
                 0,
                 inorder.size() - 1,
                 inMap );
}


//================================================================================

int main() {


    // printLevels(buildTree({3, 9, 20, 15, 7},{9, 3, 15, 20, 7}));

    printLevels(buildTree({3, 4, 5, 6, 2, 9},{5, 4, 6, 3, 2, 9}));
    printLevels(buildTree_canon({3, 4, 5, 6, 2, 9},{5, 4, 6, 3, 2, 9}));

    return 0;
}


/*
derivation

1. Inorder is always the splitter.

    9 [3] 15 20 7

    Left | Root | Right

    leftSize  = pos - inL
    rightSize = inR - pos

    The inorder ranges never change.
        Left  = inL   ... pos-1
        Right = pos+1 ... inR



2. for postorder
    [9, 15, 7, 20, 3]
    Left | Right | Root
                    ^

    remember leftSize, so since 0 index, leftSize-1

    so split for postorder is
        node->left  = postL, (postL + leftSize - 1)
        node->right = (postL + leftSize), (postR - 1)


3. for preorder
    [3, 9, 20, 15, 7]
    Root | Left | Right
    ^
    remember leftSize, root takes +1, leftSize
        +1 to everything in vs post
        -1 to everything postorder

    node->left  = (preL + 1), preL+leftSize
    node->right = (preL+lefSize+1), preR


for inorder
    it will always be
    inL, pos-1
    pos+1, inR

*/