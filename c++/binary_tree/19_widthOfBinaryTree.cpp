#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

long long int widthOfBinaryTree(TreeNode* root) {
    long long int max_width=0;
    if(!root) return max_width;

    // node, index
    queue<pair<TreeNode*, int>> q;
    q.push({root,0});

    // according to the heap indexing system
    // we start at 1 or 0
    // for 1,   left child = 2n
    //          right child = 2n+1
    // for 0,   left child = 2n+1
    //          right child = 2n+2

    // but since we want to normalize each index, row wise
    // we want each level to start at 0,
    // lets mix starting with 0, and having left=2n, right =2n+1
    // hence each level starts with idx=0

    while(!q.empty()) {
        int size = q.size();
        // new level starts here
        // get first node here
        long long start = q.front().second;  // normalize base
        long long first = 0, last = 0;

        for(int i=0; i<size; i++) {
            auto [node, index] = q.front();
            q.pop();

            long long currIndex = index - start;  // normalization
            if(i == 0) first = currIndex;
            if(i == size-1) last = currIndex;
            

            if(node->left) q.push({node->left, 2*index});
            if(node->right) q.push({node->right, (2*index)+1});
        }
        max_width = max(max_width, last-first+1);
    }
    return max_width;
}

int main() {
    return 0;
}