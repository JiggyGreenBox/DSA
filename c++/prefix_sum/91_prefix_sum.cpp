#include <iostream>
#include <vector>

using namespace std;

int sum(vector<int>& v, int L, int R) {
    vector<int> prefix_sum = v;

    prefix_sum[0] = v[0];
    for(int i=1; i<v.size(); i++){
        prefix_sum[i] += prefix_sum[i-1];
    }

    cout << "[ ";
    for(auto x:prefix_sum) cout << x << " ";
    cout << "]" << endl;

    // int sum;
    // if(L==0){
    //     sum = prefix_sum[R];
    // }
    // else{
    //     sum = prefix_sum[R] - prefix_sum[L-1];
    // }

    int sum = prefix_sum[R] - (L>0 ? prefix_sum[L-1] : 0);
     

    return sum;
}

int main() {
    vector<int> v = {1, 1, 1, 1, 1};

    // queries
    // (1,3), (0,4)
    cout << sum(v, 1, 3) << endl; // 3
    cout << sum(v, 0, 4) << endl; // 5
    return 0;
}