#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;    
    TreeNode(int _data): data(_data), left(nullptr), right(nullptr) {}
};

void print(const vector<int>& v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]\n";
}

void helper(TreeNode* node, vector<int>& res) {
    if(node == nullptr) return;

    // postorder means the root at the end
    helper(node->left, res);    
    helper(node->right, res);
    res.push_back(node->data);
}

vector<int> postorder(TreeNode* root) {
    vector<int> res;
    helper(root, res);
    return res;
}

vector<int> postorder_iterative(TreeNode* root) {
    

    // dfs node                    st.push node
    //     if not node return      pop node for parents, or EXIT
    //     dfs(node->left)         push node.left
    //     dfs(node->right)        push node.right
    //     print(node)             print node after right, done

    vector<int> res;
    stack<TreeNode*> st;
    TreeNode* node = root;
    TreeNode* last = nullptr;
    while(true) {
        if(node) {
            st.push(node);
            node = node->left; // try left
        }
        else{
            if(st.empty()) break; // no ancestors to process, EXIT

            node = st.top();

            // go right only once
            if(node->right && last != node->right) {
                node = node->right;
            }
            else{
                last = node;
                res.push_back(node->data); // no right or already visited
                st.pop();
                node = nullptr; // look for ancestors
            }
        }
    }
    return res;
}


/*
postorder is LeftRightRoot
    reverse of that is RootRightLeft
    so modified preorder
        which is simple because of a stack
    in preorder
        we have a stack and vector
    but we want reverse of this order
        so we have a second stack instead of the vector


    The second stack is not replacing the vector - it's replacing the 
    final reverse() operation.
*/
vector<int> postorder_iterative_2_st(TreeNode* root) {
    vector<int> res;

    if (!root)
        return res;

    stack<TreeNode*> st1;
    stack<TreeNode*> st2;

    st1.push(root);

    while (!st1.empty()) {
        TreeNode* node = st1.top();
        st1.pop();

        // st2 will reverse this processing order
        st2.push(node);

        // Push left first, then right.
        // Since stack is LIFO, right gets processed first.
        if (node->left)
            st1.push(node->left);

        if (node->right)
            st1.push(node->right);
    }

    // Reverse the order by popping st2
    while (!st2.empty()) {
        res.push_back(st2.top()->data);
        st2.pop();
    }

    return res;
}

vector<int> postorder_iter_canon(TreeNode* root) {

    vector<int> res;
    // if(!root) 
    //     return res;

    stack<TreeNode*> st;
    TreeNode* curr = root;
    TreeNode* lastVisited = nullptr;

    while(curr || !st.empty()) {

        // Go as far left as possible
        while(curr) {
            st.push(curr);
            curr = curr->left;
        }
        
        // this vs inorder
        // we cant reuse the curr variable
        // because after we visit left and right
        // while(curr) will still run
        // either use node, or make curr = nullptr
        // after processing
        TreeNode* node = st.top();

        // Need to process the right subtree first
        if(node->right &&
            lastVisited != node->right) {

            curr = node->right;
        }
        else {
            // If right subtree doesn't exist or is already processed                
            res.push_back(node->data);

            lastVisited = node;

            st.pop();
            // curr = nullptr; if using curr
        }
        
    }
    return res;
}

int main() {
    /*
       1
     3   99
    4 2
    */ 
//   [ 4 2 3 99 1 ]
    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(3);
    // root->right = new TreeNode(99);
    // root->left->left = new TreeNode(4);
    // root->left->right = new TreeNode(2);

    /*
     1
       2
      3
    */
    // TreeNode* root = new TreeNode(1);
    // root->right = new TreeNode(2);    
    // root->right->left = new TreeNode(3);
    TreeNode* root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);


    print(postorder(root));
    print(postorder_iterative(root));
    return 0;
}