#include <iostream>
#include <vector>
using namespace std;


vector<int> nCr(int n) {
    long long val = 1; // nC0 = 1
    vector<int> ans;

    for(int i=0; i<=n; i++) {
        ans.push_back(val);
        val = val * (n-i) / (i+1);
    }

    return ans;
}

vector<int> pascalTriangleII(int r) {
    return nCr(r-1);
}

void print(const vector<int> &v) {
    cout << "[ ";
    for(int x : v) cout << x << " ";
    cout << "]" << endl;
}
int main() {

    print(pascalTriangleII(5));
    print(pascalTriangleII(4));

    return 0;
}