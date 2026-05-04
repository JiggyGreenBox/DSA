#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int divisor_sum(vector<int> &nums, int divisor, int limit) {
    int sum=0;

    float div = static_cast<float>(divisor);

    if(divisor>0){
        for(int i=0;i<nums.size(); i++){
            // cout << ceil(nums[i]/div) <<endl; 
            sum += ceil(nums[i]/div);

            if(sum > limit) return limit+1;
        }
    }
    return sum;
}

int smallestDivisor(vector<int> &nums, int limit) {

    int max_num = 0;
    for(auto num : nums){
        if(num>max_num) max_num = num;
    }

    // code improvement
    #include <algorithm>
    int high = *max_element(nums.begin(), nums.end());
    // return iterator to max
    // Get iterator to max element
    auto it = std::max_element(nums.begin(), nums.end());
    // if we needed the distance we would need to calculate it
    // Compute index
    int index = std::distance(nums.begin(), it);



    int start = 1;
    // int end = limit;
    int end = max_num;    
    int ans = -1;

    while(start <= end){
        int mid = start + (end-start)/2;

        int sum = divisor_sum(nums, mid, limit);

        cout << mid;
        cout << " | ";
        cout << sum;
        cout << endl; 
        cout << endl;

        // if sum is too large,
        // we increase the divisor to reduce the sum
        if(sum > limit){
            start = mid+1; 
        }
        else{
            // sum is smaller than the limit 
            // we reduce the divisor to increase the sum
            ans = mid;
            end = mid-1;            
        }
    }
    return ans;
}

int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    int limit = 8;
    // cout << divisor_sum(v, 2, 8) << endl;
    // cout << smallestDivisor(v, limit) << endl;
    


    v = {8,4,2,3};
    limit = 10;
    // cout << smallestDivisor(v, limit) << endl;


    v = {8,4,2,3};
    limit = 4;
    cout << smallestDivisor(v, limit) << endl;


    return 0;
}

// need some notes here on static cast

// The divisor lies in the range [1,max(nums)].
// wrongly assumed the answer is in 1..limit

https://www.pornhub.com/view_video.php?viewkey=65c9abc29b03c
https://www.pornhub.com/view_video.php?viewkey=67fd44450c021
https://www.pornhub.com/view_video.php?viewkey=688bf43522bab
https://www.pornhub.com/view_video.php?viewkey=6886a6cc366ce