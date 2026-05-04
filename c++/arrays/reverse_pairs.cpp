#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int reversePairs_brute(vector<int>& nums) {
        // brute force
        // n^2 compare each
        int n = nums.size();
        int count=0;
        for(int i=0; i<n-1; i++){
            for(int j=1; j<n; j++){
                if(nums[i] > 2*nums[j]){
                    count++;
                }
            }
        }
        return count;
    }

    void count_pairs(vector<int>& nums, int start, int mid, int end, int& ans) {
        int j=mid+1;

        for(int i=start; i<=mid; i++){
            // while (j <= end && nums[i] > 2 * nums[j]) j++;
            while (j <= end && (long long)nums[i] > 2LL * nums[j]) j++;
            ans += (j-mid)-1;
        }

        // 5,6,7,8,9, 1,2,3,4

        // 5>2*1, Y j++
        // 5>2*2  Y j++
        // 5>2*3  N
        //     ans +=
        // 6>2*3  N
        //     ans +=

        // 7>2*3  Y j++
        // 7>2*4  N
        //     ans
        // 8>2*4  N
        //     ans
        // 9>2*4  Y j++
        //     ans+=
    }

    void merge(vector<int>& nums, int start, int mid, int end) {
        vector<int> temp;

        int i = start;
        int j = mid+1;

        while(i<=mid && j<=end){
            if(nums[i] <= nums[j]){
                temp.push_back(nums[i++]);
            }
            else{
                temp.push_back(nums[j++]);
            }
        }
        while(i<=mid) temp.push_back(nums[i++]);
        while(j<=end) temp.push_back(nums[j++]);

        // copy back
        i=start;
        for(auto x: temp){
            nums[i++] = x;
        }
    }

    void merge_sort(vector<int>& nums, int start, int end, int& ans) {
        if(start >= end) return;        

        int mid = start + (end-start)/2;
        merge_sort(nums, start, mid, ans);
        merge_sort(nums, mid+1, end, ans);
        count_pairs(nums, start, mid, end, ans);
        merge(nums, start, mid, end);        
    }

    int reversePairs(vector<int>& nums) {
        int ans=0;
        merge_sort(nums, 0, nums.size()-1, ans);
        return ans;
    }
};

void print(vector<int>& v){
    for(auto x:v) cout << x << " ";
    cout << endl;
}

int main(){
    Solution sol;
    vector<int> v = {6, 4, 1, 2, 7};
    // cout <<  sol.reversePairs_brute(v) << endl;  
    cout <<  sol.reversePairs(v) << endl;  
    

    print(v);

    return 0;
}