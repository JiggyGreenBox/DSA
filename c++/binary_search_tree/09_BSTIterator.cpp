#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}    
};

    //     7
    //    / \
    //   3   15
    //      /  \
    //     9   20	
class BSTIterator{
	private:
		stack<TreeNode*> st;
		void processNode(TreeNode* node) {
			st.push(node);
			while(node->left) {
				st.push(node->left);
				node = node->left;
			}
		}
	public:
		BSTIterator(TreeNode* root) {
			processNode(root);
		}
		
		bool hasNext() {
			return !st.empty();
		}
		
		int next() {

			if(st.empty()) return -1;

			TreeNode* node = st.top();
			st.pop();
			if(node->right) {
				processNode(node->right);
			}			
			return node->data;
		}
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


int main() {
	TreeNode* root = constructTree("7 3 15 null null 9 20");
	//     7
    //    / \
    //   3   15
    //      /  \
    //     9   20
	BSTIterator it(root);

	// inorder(node):
	// 		inorder(node->left)
	// 		visit node
	// 		inorder(node->right)

	// stack recreates this logic
	// push node and node->left till no node
	// then pop
	// check if node->right has left till no node
	

	while(it.hasNext()) {
		cout << it.next() << endl;
	}
	return 0;
}