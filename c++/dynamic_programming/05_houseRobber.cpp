#include <iostream>
#include <vector>
using namespace std;
/*
house robber:

money = {1, 5, 2, 1, 6};

if we add information about if 
first was picked then dont pick last?

this can work in the recursive solution
because of global state

but for dp how do we know if the fist element 
or last element is picked in the same iteration

f[i] = max(f[i-1], a[i] + f[i-2])
*/

/*
GPT suggestions

    The first and last house cannot both be picked
    So every valid solution must fall into one of two cases:

    rob houses from index 1 → n-1
    rob houses from index 0 → n-2

    can we reuse the same dp array
*/



int max_sum_non_adjacent(int start, int end, vector<int> &money) {
    int prev1 = 0;
    int prev2 = 0;

    for(int i=start; i<=end; i++) {
        int curr = max(prev1, money[i] + prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int houseRobber(vector<int>& money) {
    int n = money.size();
    int omit_first = max_sum_non_adjacent(1, n-1, money);
    int omit_last = max_sum_non_adjacent(0, n-2, money);
    return max(omit_first, omit_last);
}

int main() {
    vector<int> money = {2, 1, 4, 9};
    cout << houseRobber(money) << endl;

    money = {1, 5, 2, 1, 6};
    cout << houseRobber(money) << endl;
    return 0;
}