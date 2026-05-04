#include <bits/stdc++.h>
using namespace std;
class Solution {
public:

	int get_bouquets(int n, vector<int>& nums, int target_flower_per_bouquet, int bloom_day) {
		// for each nums
		int bouquet_count = 0;
		int flowers_per_bouquet = 0;

		for(int i=0; i<n; i++){      

			if(nums[i] <= bloom_day){
				flowers_per_bouquet++;
				if(flowers_per_bouquet >= target_flower_per_bouquet){
					bouquet_count++;
					flowers_per_bouquet=0;
				}
			}
			else{
				flowers_per_bouquet = 0;
			}			
		}
		return bouquet_count;
  	}

	int roseGarden(int n,vector<int> nums, int k, int m) {
		// k == target_flower_per_bouquet
		// m == target_bouquet_count
		// early exit condition
		//    if k*m < n, not possible    
		cout << k*m << endl;
		cout << n << endl;
		if((k*m) > n) return -1;

		// ans in [min(n)..max(n)]
		int max_bloom_day = nums[0];
		int min_bloom_day = nums[0];
		for(int x: nums){
			if(x > max_bloom_day) max_bloom_day = x;
			if(x < min_bloom_day) min_bloom_day = x;
		}

		int low = min_bloom_day, high = max_bloom_day;
		int ans = -1;
		// =======================================================
		// GPT CORRECTION
		// if mid works still look for a lower feasible solution
		// =======================================================
		// cout << "low: " << low
		// 	 << " high: " << high
		// 	 << endl;
		while(low <= high){
			int mid = low + (high-low)/2;

			cout << "low: " << low
			 << " mid: " << mid
			 << " high: " << high
			 << endl;
			
			int b_count = get_bouquets(n, nums, k, mid);
			cout << "b_count: " << b_count << endl;

			
			// if(b_count == m) return mid;
			// else if(b_count < m) low = mid + 1;
			// else high = mid - 1;

			if(b_count >= m){
				ans = mid; 		// either b_count == m , or b_count too big
								// in both cases we look for a smaller solution
				high = mid-1;
			}
			else{
				// b_count is too small
				low = mid + 1;
			}
		}
		return ans;
  	}
};

class Solution2 {
public:
    int get_bouquets(int n, const vector<int>& nums, int k, int bloom_day) {
        int bouquet_count = 0, flowers = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] <= bloom_day) {
                flowers++;
                if (flowers == k) {
                    bouquet_count++;
                    flowers = 0;
                }
            } else {
                flowers = 0;
            }
        }
        return bouquet_count;
    }

    int roseGarden(int n, vector<int>& nums, int k, int m) {
        if ((long long)k * m > n) return -1;

        int low = *min_element(nums.begin(), nums.end());
        int high = *max_element(nums.begin(), nums.end());
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int b_count = get_bouquets(n, nums, k, mid);

            if (b_count >= m) {
                ans = mid;        // mid works, but maybe there's a smaller one
                high = mid - 1;
            } else {
                low = mid + 1;    // need more days
            }
        }
        return ans;
    }
};


int main(){
	vector<int> nums = {7, 7, 7, 7, 13, 11, 12, 7};
	int m = 2;
	int k = 3;

	nums = {642822109,590192314};
	m=1;k=1;

	Solution sol;
	cout << sol.roseGarden(nums.size(), nums, k, m) << endl;

	Solution2 sol2;
	cout << sol2.roseGarden(nums.size(), nums, k, m) << endl;

	return 0;
}