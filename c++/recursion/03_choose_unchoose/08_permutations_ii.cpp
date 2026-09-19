/*
Permutations II
    [https://leetcode.com/problems/permutations-ii/description/]

Given a collection of numbers, nums, that might contain duplicates, 
return all possible unique permutations in any order.

 

Example 1:

    Input: nums = [1,1,2]
    Output:
    [[1,1,2],
    [1,2,1],
    [2,1,1]]

Example 2:

    Input: nums = [1,2,3]
    Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]


*/

/*
[1,1,2]

1,1,2
    1,1,2 duplicate not added
1,2,1
2,1,1
    2,1,1 duplicate not added
*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> ans;
    vector<int> current;

    void backtrack(vector<int>& nums, vector<bool>& used) {
        // Complete permutation
        if (current.size() == nums.size()) {
            ans.push_back(current);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {

            // Already used in current permutation
            if (used[i])
                continue;

            // Skip duplicate choice at this level
            if (i > 0 &&
                nums[i] == nums[i - 1] &&
                !used[i - 1])
                continue;

            // there are 2 duplicates not used
            // check back later deeper in recursion
            if(i>0 && nums[i] == nums[i-1] && !used[i-1])
                continue;

            // Choose
            used[i] = true;
            current.push_back(nums[i]);

            backtrack(nums, used);

            // Unchoose
            current.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<bool> used(nums.size(), false);

        backtrack(nums, used);

        return ans;
    }
};

int main() {
    vector<int> nums = {1,1,2};
    Solution s;
    auto x = s.permuteUnique(nums);
    int y = 5;
    return 0;
}

/*
what is happening
    we sort, so duplicates are next to each other

index:  0   1   2
value:  1   1   2
        1a  1b

at the beginning we have 3 choices
        []
      / | \
    1a 1b  2

1a first:
[1a, 1b, 2] → [1,1,2]
[1a, 2, 1b] → [1,2,1]

1b first:
[1b, 1a, 2] → [1,1,2]
[1b, 2, 1a] → [1,2,1]


Use the first 1 before the second 1.

if (i > 0 &&
    nums[i] == nums[i - 1] &&
    !used[i - 1])
    continue;


if current = [1a]
    1a used
    1b is unused
    2 is unused

we must allow
    [1a,1b,]

think of 1a, 1b as siblings at the same level
    we only want to choose 1 of them

                []
             /  |  \
           1a  1b   2
           |
         [1a]
        /    \
      1b      2

1b is no longer a sibling of 1a
    so its allowed

how???

                 Can I choose nums[i]?
                         |
                Is nums[i] duplicate?
                    /          \
                  NO            YES
                               |
                      Was previous duplicate
                         used already?
                         /          \
                       YES           NO
                        ↓             ↓
                     ALLOW          SKIP



this means that if a duplicate is found, and it was not used
we cant safely choose, check again later

if a prev duplicate is found, and the prev duplicate is used
    we can use this one

*/