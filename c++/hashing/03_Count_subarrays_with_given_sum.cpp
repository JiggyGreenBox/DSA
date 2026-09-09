#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int subarraySum(const vector<int> &nums, int k) {
    unordered_map<int, int> mpp; // sum, freq
    int count = 0;
    int sum = 0;
    mpp[0] = 1;
    for(int num : nums) {
        sum += num;

        if(mpp.find(sum - k) != mpp.end()) {
            count += mpp[sum - k];
        }

        mpp[sum]++;
    }
    return count;
}

int main() {
    cout << subarraySum({1,1,1,1,1,1}, 3) << endl;
    cout << subarraySum({0,0,0,0}, 0) << endl;
    return 0;
}