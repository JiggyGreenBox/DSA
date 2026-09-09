#include <bits/stdc++.h>
using namespace std;

/*
Merge Without Extra Space
    [https://www.geeksforgeeks.org/problems/merge-two-sorted-arrays-1587115620/1]

Given two sorted arrays a[] and b[] of size n and m respectively, the 
task is to merge them in sorted order without using any extra space. 
Modify a[] so that it contains the first n elements and modify b[] so 
that it contains the last m elements.

Examples:

Input: a[] = [2, 4, 7, 10], b[] = [2, 3]
Output: a[] = [2, 2, 3, 4], b[] = [7, 10]
Explanation: After merging the two non-decreasing arrays, we get, [2, 
2, 3, 4, 7, 10]

Input: a[] = [1, 5, 9, 10, 15, 20], b[] = [2, 3, 8, 13]
Output: a[] = [1, 2, 3, 5, 8, 9], b[] = [10, 13, 15, 20]
Explanation: After merging two sorted arrays we get [1, 2, 3, 5, 8, 
9, 10, 13, 15, 20].

Input: a[] = [0, 1], b[] = [2, 3]
Output: a[] = [0, 1], b[] = [2, 3]
Explanation: After merging two sorted arrays we get [0, 1, 2, 3].

*/

// [1,2,3,4,5] [6,7]

// [1,2,3,4,5,] [6,7]
//          i    j

// if we use a 2 pointer solution
//     keep i to larger
//     j to lower
//     after each swap of i to j we need sort


/*
gap algorithm
    treat both arrays as 1 array

    then swap based on gap
        and reduce the gap

    we want ceil(n+m/2)
    and gap reduces by ceil(gap/2)

    why ceil?
        if we had 7 elements across 2 arrays
        then 7/2 = 3.5
        so we'd like 4 as a good way to check for a swap

    ceil of (x/2) = x+1/2
    ceil(m+n/2) == (m+n+1)/2

    ceil(gap/2) = (gap+1)/2
*/

void merge(vector<int>& a, vector<int>& b) {
    int n = a.size();
    int m = b.size();

    for(int gap = (n + m + 1) / 2; gap > 0; gap = (gap + 1) / 2) {
        int i = 0;
        int j = gap;

        while(j < n + m) {
            // both in a
            if(i < n && j < n) {
                if(a[i] > a[j])
                    swap(a[i], a[j]);
            }
            // i in a, j in b
            else if(i < n && j >= n) {
                if(a[i] > b[j - n])
                    swap(a[i], b[j - n]);
            }
            // both in b
            else {
                if(b[i - n] > b[j - n])
                    swap(b[i - n], b[j - n]);
            }

            i++;
            j++;
        }

        if(gap == 1)
            break;
    }
}

// merge with extra space would be O(n+m)
// but also space of O(n+m)
// this trades that for O(m+n)log(n+m)
// N = n + m, gap = N/2,N/4, N/8
// logN

// why stop at gap == 1
// because gap == 0 is useless and also cap cant reach 0 because of ceil
// so compare at gap == 1 then break
int main() {

    return 0;
}




// [-5, -2, 4, 5, 0, 0, 0]          [-3, 1, 8]
// [-5, -2, 4, 5, 0, 0, 0]          [-3, 1, 8]
// i                                  j

// i<=j i++

// -2<-3
//     swap i, j, i++
// [-5, -3, -2, 5, 0, 0, 0]          [4, 1, 8]
//              i                     j


// target=-3, idx=2
// [-5, -2, 4, 5, 0, 0, 0] -> [-5, -2, -3, 4, 5, 0, 0]

// shift i=2
//     while j==n-1; j>i; j--
//         nums[j] = nums[j-1]

