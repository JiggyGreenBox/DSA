#include <iostream>
#include <algorithm>
#include <climits>
#include <map>
#include <set>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;


struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

void traverse(TreeNode* node, int X, int Y, vector<pair<pair<int, int>, int>>& nodes) {
    if(!node) return;

    nodes.push_back({{X,Y}, node->data});

    traverse(node->left, X-1, Y+1, nodes);
    traverse(node->right, X+1, Y+1, nodes);
}

bool mysort(const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
    if(a.first.first == b.first.first){
        if(a.first.second == b.first.second){
            return a.second < b.second;
        }
        return a.first.second < b.first.second;
    }
    return a.first.first < b.first.first;
}

// <<x,y>, val>
// sort X
//     then sort Y
vector<vector<int>> verticalTraversal_old(TreeNode* root) {
    // x -> horizontal
    // y -> vertical
    // root -> 0,0

    vector<vector<int>> res;
    if(!root) return res;
    //                 X,   Y,  val
    vector<pair<pair<int, int>, int>> nodes;

    traverse(root, 0, 0, nodes);   // O(n)
    sort(nodes.begin(), nodes.end(), mysort); // O(nlogn)
    int last_X = INT_MIN;
    for(auto &pp : nodes) {
        auto &p = pp.first;
        int X = p.first;        
        int val = pp.second;

        if(X != last_X){
            last_X = X;
            res.push_back({});            
        }
        res.back().push_back(val);
    }
    return res;
}

void traverse(TreeNode* node, int X, int Y, vector<tuple<int,int,int>>& nodes) {
    if(!node) return;
    nodes.push_back({X,Y, node->data});
    traverse(node->left, X-1, Y+1, nodes);
    traverse(node->right, X+1, Y+1, nodes);
}

// use a tuple instead of pair<pair<int,int>,int>
vector<vector<int>> verticalTraversal_cannonical1(TreeNode* root) {
    vector<vector<int>> res;
    if(!root) return res;

    // X,Y,val
    vector<tuple<int,int,int>> nodes;

    traverse(root, 0, 0, nodes);

    sort(nodes.begin(), nodes.end());

    int lastCol = INT_MIN;
    for(auto [col, row, val] : nodes) {         

        if(col != lastCol) {
            lastCol = col;
            res.push_back({});
        }
        res.back().push_back(val);
    }
    return res;
}

vector<vector<int>> verticalTraversal_cannonical2(TreeNode* root) {

    vector<vector<int>> res;
    if(!root) return res;

    // instead of collecting data
    // and then sorting it
    // we use maps to keep data sorted
    // TC will be the same

    // we use map to keep data sorted
    // since the sorting order is col, row, val
    // we use col as the first key
    // we use multiset, to order elements, but also allow duplicates

    //  col,    row,          val
    map<int, map<int, multiset<int>>> nodes;

    // use level order traversal
    // need a queue
    // we need the row, col information to be stored as well
    queue<pair<TreeNode*, pair<int, int>>> q;
    q.push({root, {0,0}});

    while(!q.empty()) {
        auto front = q.front();
        q.pop();

        TreeNode* node = front.first;
        int col = front.second.first;
        int row = front.second.second;

        nodes[col][row].insert(node->data);

        if(node->left) q.push({node->left, {col-1, row+1}});

        if(node->right) q.push({node->right, {col+1, row+1}});
    }

    // put sorted data into res

    for(auto& [col, rows] : nodes) {
        vector<int> vertical;
        for(auto& [row, values] : rows) {
            // values are multiset<int>
            // insert range
            vertical.insert(vertical.end(), values.begin(), values.end());
        }
        res.push_back(vertical);
    }
    return res;
}

// -------------------------------------------------------------------
void dfs(TreeNode* node, int row, int col, vector<tuple<int, int, int>>& coords) {
    if(!node)
        return;

    coords.push_back({col, row, node->data});

    dfs(node->left, row+1, col-1, coords);
    dfs(node->right, row+1, col+1, coords);    
}

vector<vector<int>> verticalTraversal(TreeNode* root) {
    vector<vector<int>> ans;
    if(!root)
        return ans;
    
    vector<tuple<int, int, int>> coords;
    dfs(root, 0, 0, coords);
    
    sort(coords.begin(), coords.end());

    // create an empty vector for each new col
    int currentCol = INT_MIN;

    for (auto [col, row, val] : coords) {

        // create an empty vector for each new col
        if (col != currentCol) {
            currentCol = col;
            ans.push_back({});
        }

        ans.back().push_back(val);
    }

    return ans;
}
// -------------------------------------------------------------------

void print(const vector<vector<int>>& res) {
    cout << "[ ";
    for(auto& vec : res) {
        cout << "[ ";
        for(int x : vec) cout << x << " ";
        cout << "] ";
    }
    cout << "]\n";
}

int main() {
    // root = [3, 9, 20, null, null, 15, 7]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    print(verticalTraversal(root));
    print(verticalTraversal_cannonical1(root));
    // print(verticalTraversal_cannonical2(root));
    return 0;
}