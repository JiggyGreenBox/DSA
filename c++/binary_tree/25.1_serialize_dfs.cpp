#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

/*
this version creates a lot of temporary strings
    Every + creates a new string.
*/
string serialize_slow(TreeNode* root) {
    // every element should have a comma at the end
    // we need to search for commas
    //      because nodes can have very large values, 9999999,11111111,
    // use null, to represent missing values

    // if theres data add the comma in the function call
    if(!root) return "null,";
    return to_string(root->data) + "," + 
           serialize_slow(root->left) +
           serialize_slow(root->right);
}


//--------------------------------------------------
// Serialize (DFS Preorder)
//--------------------------------------------------

void serializeHelper(TreeNode* root, string &s) {

    if (!root) {
        s += "null,";
        return;
    }

    s += to_string(root->data) + ",";

    serializeHelper(root->left, s);
    serializeHelper(root->right, s);
}

string serialize(TreeNode* root) {

    string s;
    serializeHelper(root, s);

    return s;
}

//--------------------------------------------------
// Deserialize
//--------------------------------------------------

TreeNode* deserializeHelper(string& data, int& pos) {
    // use pos to process data at a position

    // search for a null
    // creates a temp string, lots of allocation
    // if(data.substr(pos,5) == "null,") {
    if (data.compare(pos, 5, "null,") == 0) {
        pos += 5;
        return nullptr;
    }

    // this points to the comma after the number
    int comma = data.find(",", pos); // search for char, pos is starting position

    int value = stoi(data.substr(pos, comma - pos));

    pos = comma + 1; // go +1 ahead of the curr comma

    TreeNode* node = new TreeNode(value);

    node->left = deserializeHelper(data, pos);
    node->right = deserializeHelper(data, pos);

    return node;
}

TreeNode* deserialize(string data) {
    int pos = 0;
    return deserializeHelper(data, pos);
}

int main() {
    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(2);
    // root->right = new TreeNode(3);
    // root->right->left = new TreeNode(4);
    // cout << serialize(root) << endl;
    // TreeNode* node = deserialize(serialize(root));

    // string s = "110001";
    // cout << s.find('1',0) << endl;
    // cout << s.find('1',1) << endl;
    // cout << s.find('1',2) << endl;

    // s = "1,2222,";
    // int pos = 2;
    // int next = s.find(',', pos);
    // cout << s.substr(pos, next-pos) << endl; // end is non-inclusive

    // s = "0,123,45";
    // pos = 2;
    // int comma = s.find(',', pos+1);
    // cout << comma << endl;
    // cout << s.substr(pos, comma-pos) << endl;
    return 0;
}