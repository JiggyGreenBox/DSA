#include <iostream>
#include <vector>
using namespace std;


int max_sum_k(const vector<int>& nums, int k) {
    int n = nums.size();
    int max_sum = 0;
    for(int i=0; i<n; i++) {
        int sum = 0;
        for(int j=i; j<n; j++) {
            sum += nums[j];
            if(sum > k) break;
            max_sum = max(max_sum, sum);
        }
    }
    return max_sum;
}

int main() {
    cout << max_sum_k({11, 12, 13, 14, 15, 16, 17, 18}, 15) << endl;
    return 0;
}