#include <vector>
using namespace std;

void helper(int idx, int k, int n, vector<int> &curr, vector<vector<int>> &ans) {

    if(curr.size() == k) {
        if(n==0)
            ans.push_back(curr);
        return;
    }

    for(int i=idx; i<10; i++) {

        if(i > n)
            continue;

        curr.push_back(i);
        helper(i+1, k, n-i, curr, ans);
        curr.pop_back();
    }
}

vector<vector<int>> combinationSum3(int k, int n) {
    vector<vector<int>> ans;
    vector<int> curr;
    helper(1, k, n, curr, ans);
    return ans;
}

int main() {
    auto x = combinationSum3(3, 9);
    return 0;
}