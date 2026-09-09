/*
4Sum II
    [https://leetcode.com/problems/4sum-ii/description/]

Given four integer arrays nums1, nums2, nums3, and nums4 all of 
length n, return the number of tuples (i, j, k, l) such that:

0 <= i, j, k, l < n
nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
 

Example 1:

    Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
    Output: 2
    Explanation:
    The two tuples are:
    1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + 
    (-2) + (-1) + 2 = 0
    2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + 
    (-1) + (-1) + 0 = 0

Example 2:

    Input: nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
    Output: 1

*/

/*
we need 4 pointers
all are bounded by n, same len for all arrays

each pointer is from a distinct array

the brute force is 4 loops
    for i
        for j
            for k
                for l

    TC n^4

    we want
        A+B+C+D == 0
        A+B == -(C+D)

    for every A
        for every B
            store sum
    
    for every C
        for every D
            check if -(C+D) exists

*/

#include <vector>
#include <unordered_map>
using namespace std;
int fourSumCount(vector<int>& A,
                 vector<int>& B,
                 vector<int>& C,
                 vector<int>& D) {

    unordered_map<int, int> freq;

    for (int a : A) {
        for (int b : B) {
            freq[a + b]++;
        }
    }

    int count = 0;

    for (int c : C) {
        for (int d : D) {
            count += freq[-(c + d)];
        }
    }

    return count;
}