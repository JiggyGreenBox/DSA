#include <bits/stdc++.h>
using namespace std;
class Solution {
public:

    bool canPlace(vector<int> &nums, int mid, int target){

      int last_cow_pos = nums[0];
      int cows_placed = 1;

      for(int i=1; i<nums.size(); i++) {

        // cout << "last_cow_pos + mid: (" << last_cow_pos
		// 	 << " + " << mid
		// 	 << ") = " << (mid + last_cow_pos)
        //      << " <= " << nums[i]
		// 	 << endl;

        if(last_cow_pos + mid <= nums[i]) {
          last_cow_pos = nums[i];
          cows_placed++;
          if(cows_placed >= target){
            cout << " at mid=" << mid
                 << " cows_placed: "
                 << cows_placed 
                 << endl;
            return true;
          } 
        }
      }
      cout << " at mid=" << mid
                 << " cows_placed: "
                 << cows_placed 
                 << endl;
      return false;
    }

    int aggressiveCows(vector<int> &nums, int k) {

      sort(nums.begin(), nums.end());
      int low = nums[0];
      int high = nums[nums.size()-1];
      int ans = -1;

      while(low <= high){
        int mid = low + (high-low)/2;

        cout << "low: " << low
			 << " mid: " << mid
			 << " high: " << high
			 << endl;
        if(canPlace(nums, mid, k)){
          // mid works, look for greater ans
          ans = mid;
          low = mid + 1;
        }
        else{
          high = mid - 1;
        }
      }
      return ans;
    }
};

int main(){
    Solution sol;

    vector<int> nums = {0, 3, 4, 7, 10, 9};
    int k = 4;

    cout << sol.aggressiveCows(nums, k) << endl;


    nums = {4, 2, 1, 3, 6};
    k = 2;

    string s(50, '=');
    cout << s << endl;

    cout << sol.aggressiveCows(nums, k) << endl;

    return 0;
}