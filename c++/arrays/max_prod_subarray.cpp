#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

int max_prod_subarray(vector<int>& nums) {

    string header(20, '=');
    cout << header << std::endl;
    for(auto x: nums) cout << x << " ";
    cout << endl;

    int n = nums.size();
    if(n<1) return 0;

    int ans         = nums[0];
    int max_so_far  = nums[0];
    int min_so_far  = nums[0];
 
    cout << "\tmax_so_far: " << max_so_far << endl;
    cout << "\tmin_so_far: " << min_so_far << endl;
    cout << "\tans: " << ans << endl;

    for(int i=1; i<n; ++i) {
        
        // int local_max = max( nums[i], max( max_so_far * nums[i], min_so_far * nums[i] ) );
        int temp_max = max({ nums[i], max_so_far * nums[i], min_so_far * nums[i]});
        
        cout << "\tmax_so_far: " << temp_max << endl;
        
        min_so_far = min({ nums[i], max_so_far * nums[i], min_so_far * nums[i] });
        cout << "\tmin_so_far: " << min_so_far << endl;

        max_so_far = temp_max;

        ans = max(ans, max_so_far);
        cout << "\tans: " << ans << endl;
    }

    cout << ans << endl;
    cout << header << endl;
    return ans;
}

int main(){
    vector<int> v = {};
    v = {5,4,3,2,1};
    cout << max_prod_subarray(v) << endl;

    v = {2, 3, 4, 5};
    cout << max_prod_subarray(v) << endl;

    v = {7};
    cout << max_prod_subarray(v) << endl;

    v = {-2, -3, -4};
    cout << max_prod_subarray(v) << endl;

    v = {-2, -3, -4, -5};
    cout << max_prod_subarray(v) << endl;

    v = {0, 2, 3, -2, 4};
    cout << max_prod_subarray(v) << endl;

    v = {2, 3, -2, 4, 0};
    cout << max_prod_subarray(v) << endl;

    v = {2, 3, 4, -5, 6, 7};
    cout << max_prod_subarray(v) << endl;

    
    return 0;
}