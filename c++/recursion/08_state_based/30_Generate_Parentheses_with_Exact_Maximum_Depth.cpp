#include <bits/stdc++.h>
using namespace std;

void helper(
    int open,
    int close,
    int depth,
    int maxDepth,
    int k,
    string &curr,
    vector<string> &res
) {
    if (open == 0 && close == 0) {
        if (maxDepth == k)
            res.push_back(curr);
        return;
    }

    // Add '('
    if (open > 0 && depth < k) {
        curr.push_back('(');

        helper(
            open - 1,
            close,
            depth + 1,
            max(maxDepth, depth + 1),
            k,
            curr,
            res
        );

        curr.pop_back();
    }

    // Add ')'
    if (close > open) {
        curr.push_back(')');

        helper(
            open,
            close - 1,
            depth - 1,
            maxDepth,
            k,
            curr,
            res
        );

        curr.pop_back();
    }
}

vector<string> gen(int n, int k) {
    string curr;
    vector<string> res;

    helper(n, n, 0, 0, k, curr, res);

    return res;
}

int main() {
    auto x = gen(3, 2);
    return 0;
}

/*

we generate all combinations
but we are only allowed a certain depth

( open+1
) close -1

then max opens allowed is k
    n=3, k=2
    (())() allowed
    ((())) not allowed



the trick is 
    track balance / depth
    and max balance/depth
*/