#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

/*
Book Allocation Problem

    Given an array nums of n integers, where nums[i] represents the 
    number of pages in the i-th book, and an integer m representing the 
    number of students, allocate all the books to the students so that 
    each student gets at least one book, each book is allocated to only 
    one student, and the allocation is contiguous.


    Allocate the books to m students in such a way that the maximum 
    number of pages assigned to a student is minimized. If the allocation 
    of books is not possible, return -1.


    Example 1

        Input: nums = [12, 34, 67, 90], m=2
        Output: 113

        Explanation: The allocation of books will be 12, 34, 67 | 90. One 
        student will get the first 3 books and the other will get the last 
        one.

    Example 2

        Input: nums = [25, 46, 28, 49, 24], m=4
        Output: 71

        Explanation: The allocation of books will be 25, 46 | 28 | 49 | 24.

    Example 3

        Input: nums = [15, 17, 20], m=2
        Output: 32
*/

bool feasible(int mid, vector<int> &nums, int m) {
    int students = 1;
    int pages = 0;

    for(int num : nums) {
        if(num + pages <= mid)
            pages += num;
        else {
            students++;
            pages = num;
        }
    }
    return students <= m;
}

int findPages(vector<int> &nums, int m)  {

    if (m > nums.size())
        return -1;

    int l = *max_element(nums.begin(), nums.end());
    int r = accumulate(nums.begin(), nums.end(), 0);

    int ans = -1;

    while(l < r) {
        int mid = l + (r-l)/2;
        if(feasible(mid, nums, m)) {            
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    return l;
}


int main() {
    vector<int> v = {12, 34, 67, 90};
    int m = 2;
    cout << findPages(v, m) << endl;


    v = {25, 46, 28, 49, 24};
    m = 4;
    cout << findPages(v, m) << endl;

    return 0;
}