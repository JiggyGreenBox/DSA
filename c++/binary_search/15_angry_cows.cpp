#include <bits/stdc++.h>
using namespace std;
class Solution {
public:

	bool canPlace(vector<int> &nums, int dist, int target){

		int last = nums[0];
		int placed = 1;

		for(int i=1; i<nums.size(); i++) {

			if(nums[i] - last >=  + dist) {

				last = nums[i];
				placed++;

				if(placed >= target){
					return true;
				} 
			}
		}	  
		return false;
	}

	int aggressiveCows(vector<int> &nums, int k) {

	  int n = nums.size();

	  sort(nums.begin(), nums.end());
	  int l = 1;
	  int r = nums[n-1] - nums[0];
	  int ans = 0;

	  while(l <= r){
		int mid = l + (r-l)/2;
		
		if(canPlace(nums, mid, k)){
		  // mid works, look for greater ans
		  ans = mid;
		  l = mid + 1; // look for a larger distance
		}
		else{
		  r = mid - 1;
		}
	  }
	  return ans;
	}
};

int main(){
	Solution sol;

	vector<int> nums = {0, 3, 4, 7, 10, 9}; // 3
	int k = 4;

	cout << sol.aggressiveCows(nums, k) << endl;


	nums = {4, 2, 1, 3, 6}; // 5
	k = 2;

	string s(50, '=');
	cout << s << endl;

	cout << sol.aggressiveCows(nums, k) << endl;

	return 0;
}