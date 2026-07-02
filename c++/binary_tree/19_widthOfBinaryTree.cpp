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

int widthOfBinaryTree_canon(TreeNode* root) {

    if(!root)
        return 0;

    long long ans = 0;

    queue<pair<TreeNode*, long long>> q;
    q.push({root, 0});

    while(!q.empty()) {

        int size = q.size();

        // Normalize indices to avoid overflow
        long long minIndex = q.front().second;

        long long first = 0, last = 0;

        for(int i=0; i<size; i++) {

            auto [node, index] = q.front();
            q.pop();

            index -= minIndex;

            if(i == 0)
                first = index;

            if(i == size - 1)
                last = index;

            if(node->left)
                q.push({node->left, 2 * index + 1});

            if(node->right)
                q.push({node->right, 2 * index + 2});
        }

        ans = max(ans, last - first + 1);
    }

    return ans;
}

int main() {
    return 0;
}

/*
heap representation of a complete binary tree
        A
      /   \
     B     C
    / \   / \
   D  E  F   G

store in array:
Index : 0 1 2 3 4 5 6
Value : A B C D E F G

left  = 2*i + 1
right = 2*i + 2
parent = (i-1)/2



now for some tree
        1
      /   \
     2     3
    /       \
   4         5

       1(0)
      /      \
   2(1)      3(2)
   /            \
4(3)            5(6)

last level
    3           6
    width 
        6 - 3 + 1 = 4
*/

/*
Width = distance between leftmost and rightmost positions.

How do we get positions?

Pretend the tree is a complete binary tree.

Use heap indices.

BFS level-order.

Width = lastIndex - firstIndex + 1.
*/