#include <iostream>
#include <vector>
using namespace std;

/*

for each idx we could check each idx before to get the best price
we will see that only the previous min is important

0 <= arr[i] <= 106

prev_min = arr[0]
max_prof = 0
for(i..n-1)
    prof = arr[i] - prev_min
    max_prof = max(max_prof, prof)
    prev_min = min(prev_min, arr[i])
return max_prof
*/
int stockBuySell1(vector<int> arr, int n) {
    int max_profit = 0;
    if(n <= 1) return 0; // cant buy and sell on the same day

    int prev_min = arr[0];
    for(int i=1; i<n; i++) {
        int prof = arr[i] - prev_min;
        max_profit = max(max_profit, prof);
        prev_min = min(prev_min, arr[i]);
    }
    return max_profit;
}

int main() {
    vector<int> v = {10, 7, 5, 8, 11, 9};
    cout << stockBuySell1(v, v.size()) << endl;
    v = {5, 4, 3, 2, 1};
    cout << stockBuySell1(v, v.size()) << endl;
    return 0;
}