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

// pre
// 3, 9, 20, 15, 7

// in
// 9, 3, 15, 20, 7




// node
//     if left not null
//         node->left = new Node()
//     if right not null
//         node->right = new Node()
//     return new node(val)

// construct_rec
//     // 0, 1,  2,  3, 4
//     // 3, 9, 20, 15, 7
//     root = pre[0]  // 3

//     if start == end no children possible

//     // 9, 3, 15, 20, 7
//     left-children = in[root] - in[0]
//     // [9]
//     // 0,0

//     right-children = in[end] - in[root]
//     // [15, 20, 7]
//     // 2,4

//     return new Node(pre[start])


//        1
//      2   3
//     4 5
// pre
// 1, 2, 4, 5, 3
// in
// 4, 2, 5, 1, 3
// 0, 1, 2, 3, 4

// dfs(0,0,4)

// dfs(root, start, end) {
//     node_val = pre[root] 2

//     node = new node(node_val)

//     if start == end, no children return

//     in_index = in.find(root) 1
//     left-len = in_idx - start + 1

//     left_child = dfs(root+1, start, in_index-1) 0,3
//     if(left_child)
//         node->left = left_child
//     right_child = dfs(root+left-len, in_index+len, end)
//     if(right_child)
//         node->right = right_child

//     return node;
// }

//    1
//  2   3
// 4 5   6

// pre  root-L-R
// in   L-root-R

// pre
//     124536
// in
//     425136

// dfs 1 0 2
//   1 right pending 0,0,5
//  2 
// 4 5

// 0,0,5
// 4,4,5
// dfs(root, start, end) {
//     node_val = pre[root] 3

//     node = new node(node_val)

//     if start == end, no children return

//     in_index = in.find(root) 4
//     left-len = in_idx - start + 1   1

//     left_child = dfs(root+1, start, in_index-1) 5,4,3
//     if(left_child)
//         node->left = left_child
//     right_child = dfs(root+left-len, in_index+len, end) 3,7,5
//     right_child = dfs(root+left-len, in_index+1, end) 5,5,5
//     if(right_child)
//         node->right = right_child

//     return node;
// }

