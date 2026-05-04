#include <bits/stdc++.h>
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

//  [5, 3, 6, 2, 4, null, 7] , k = 9
//     5
//   3   6
//  2 4   7 

bool helper(TreeNode* node, int k, unordered_set<int>& diff_set) {
    if(!node) return false;

    // check if current node completes 2 sum
    if(!diff_set.empty() && diff_set.count(node->data) > 0) return true;

    diff_set.insert(k - node->data);

    bool left = helper(node->left, k, diff_set);
    if(left) return left;
    return helper(node->right, k, diff_set);
}
// O(n) time
// O(n) space
bool twoSumBST(TreeNode* root, int k) {
    unordered_set<int> diff_set;
    return helper(root, k, diff_set);
}

class BSTiterator {
    private:
        stack<TreeNode*> st;
        bool reverse;
        void processNode(TreeNode* node) {
            if(!node) return;
            while(node) {
                st.push(node);
                node = (reverse) ? node->right : node->left;
            }
        }
    public:
        BSTiterator(TreeNode* root, bool _reverse) {
            reverse = _reverse;
            processNode(root);
        }

        bool hasNext() {
            return !st.empty();
        }

        int next() {
            if(st.empty()) return -1;

            TreeNode* node = st.top();
            st.pop();

            if(reverse) processNode(node->left);
            else processNode(node->right);

            return node->data;
        }
};

bool twoSumBST_cannonical(TreeNode* root, int k) {
    BSTiterator l(root, false);
    BSTiterator r(root, true);

    
    int i = l.next();
    int j = r.next();

    // two pointer
    while(i < j) {
        if(i+j == k) return true;

        else if(i + j < k) i = l.next();
        else j = r.next();
    }
    return false;
}

int main() {
    TreeNode* root = constructTree("6 5 7 4 null null 10");

    if(twoSumBST_cannonical(root, 12)) cout << "true" << endl;
    else cout << "false" << endl;

    root = constructTree("5 3 6 2 4 null 7");

    if(twoSumBST_cannonical(root, 9)) cout << "true" << endl;
    else cout << "false" << endl;

    if(twoSumBST_cannonical(root, 14)) cout << "true" << endl;
    else cout << "false" << endl;

    return 0;
}