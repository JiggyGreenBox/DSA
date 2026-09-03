// trapping rainwater, in stackqueue
/*
trapping rainwater wants to find water above each bar
    left, right vectors
    stack
    2 pointer

container with max water wants to find max area between any 2 bars
    2 pointer
*/

#include <vector>
using namespace std;

int maxArea(vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;

    int ans = 0;

    while (left < right) {
        int width = right - left;
        int h = min(height[left], height[right]);

        ans = max(ans, width * h);

        // Move the shorter wall
        if (height[left] < height[right]) {
            left++;
        }
        else {
            right--;
        }
    }

    return ans;
}