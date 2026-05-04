#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _data) : data(_data), left(nullptr), right(nullptr) {}
};

void helper(TreeNode* node, vector<vector<int>>& res) {
    if(!node) return;

    res[0].push_back(node->data);
    helper(node->left, res);
    res[1].push_back(node->data);
    helper(node->right, res);
    res[2].push_back(node->data);
}

// // inorder
// dfs(node)
//     dfs left
//     push node
//     dfs right

// // preorder
// dfs(node)
//     push node
//     dfs left    
//     dfs right

// // postorder
// dfs(node)    
//     dfs left    
//     dfs right
//     push node

vector<vector<int>> treeTraversal(TreeNode* root) {
    vector<vector<int>> res(3);
    helper(root, res);
    return res;
}

void print(const vector<vector<int>>& res){
    cout << "[ ";
    for(auto &vec : res) {
        cout << "[ ";
        for(int x : vec) cout << x << " ";
        cout << "] ";
    }
    cout << "]\n";
}


vector<vector<int>> treeTraversal_iterative(TreeNode* root) {

    vector<vector<int>> res(3);
    if (!root) return res;

    // 0 -> new
    // 1 -> left done
    // 2 -> right done
    stack<pair<TreeNode*, int>> st;
    st.push({root, 0});

    // vector<vector<int>> res(3);

    while(!st.empty()) {
        auto &p = st.top();
        int state = p.second;
        TreeNode* node = p.first;

        // fresh node
        if(state == 0) {
            res[0].push_back(node->data); // preorder
            p.second = 1;
            if(node->left) {
                st.push({node->left, 0});
            }
        }
        // left done
        else if(state == 1) {
            res[1].push_back(node->data); // inorder
            p.second = 2;
            if(node->right) {
                st.push({node->right, 0});
            }
        }
        // both done
        else{            
            res[2].push_back(node->data); // postorder
            st.pop();
        }
    }
    return res;
}

//     1 
//  3     4
// 5 2   7  6

// nodeState = 0 // preorder
// nodeState = 1 // inorder
// nodeState = 2 // postorder



// pre = 1,3,5,2,4,7,6
// in = 5,3,2,1,7,4,6
// post = 5,2,3,7,6,4,1

// [ [5, 3, 2, 1, 7, 4, 6] , [1, 3, 5, 2, 4, 7, 6] , [5, 2, 3, 7, 6, 4, 1] ]

// while !stack.empty()
//     node = st.top()
//     if nodeState == 0 // new node
//         add to pre-order
//         // try left
//     else if nodeState == 1 // left done
//         add to in-order
//         // try right
//     else if nodeState == 2
//         pop  
//         maybe top=++  

int main() {

    // 1, 3, 4, 5, 2, 7, 6 
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(4);
    
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(6);


    print(treeTraversal(root));
    print(treeTraversal_iterative(root));

    return 0;
}