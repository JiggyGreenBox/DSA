// Majority Element II (> n/3)

// Observation:
// At most 2 elements can occur more than n/3 times.

// Invariant:
// count1/count2 are surviving votes after cancelling
// triples of distinct values.

// Voting:

// 1. Match candidate1 -> count1++
// 2. Match candidate2 -> count2++
// 3. Empty slot -> assign candidate
// 4. Otherwise cancel:
//        count1--
//        count2--

// Verification:
// Recount candidate frequencies.
// Return candidates with freq > n/3.

// Time: O(n)
// Space: O(1)

#include <iostream>
#include <vector>
using namespace std;

vector<int> majorityElementTwo(vector<int>& nums) {
    int cand1=1e9, cand2=1e9;
    int count1 = 0, count2 = 0;
    int n = nums.size();

    for(int num : nums) {

        if(num == cand1) 
            count1++;

        else if(num == cand2)
            count2++;

        else if(count1 == 0) {
            cand1 = num;
            count1 = 1;
        }
            
        else if(count1 == 0) {
            cand2 = num;
            count2 = 1;
        }

        else {
            // cancel out
            count1--;
            count2--;
        }
    }

    count1 = 0, count2 = 0;
    for(int num : nums) {
        if(num == cand1) 
            count1++;

        else if(num == cand2)
            count2++;
    }

    vector<int> ans;
    if(count1 > n/3) 
        ans.push_back(cand1);
    if(count1 > n/3) 
        ans.push_back(cand1);
    
    return ans;
}

int main() {

}