#include <iostream>
#include <climits>
#include <vector>
using namespace std;

/*
Median of 2 sorted arrays

    Given two sorted arrays arr1 and arr2 of size m and n respectively, 
    return the median of the two sorted arrays.

    The median is defined as the middle value of a sorted list of 
    numbers. In case the length of the list is even, the median is the 
    average of the two middle elements.


    Example 1

        Input: arr1 = [2, 4, 6], arr2 = [1, 3, 5]
        Output: 3.5

        Explanation: The array after merging arr1 and arr2 will be [ 1, 2, 3, 
        4, 5, 6 ]. As the length of the merged list is even, the median is 
        the average of the two middle elements. Here two medians are 3 and 4. 
        So the median will be the average of 3 and 4, which is 3.5.

    Example 2

        Input: arr1 = [2, 4, 6], arr2 = [1, 3]
        Output: 3.0

        Explanation: The array after merging arr1 and arr2 will be [ 1, 2, 3, 
        4, 6 ]. The median is simply 3.

    Example 3

        Input: arr1 = [2, 4, 5], arr2 = [1, 6]
        Output: 4.0

*/

/*
Median of 2 sorted arrays
    approach 1
        use a vector to store both arrays using 2 pointer
        if size of set id even 4 [0,1,2,3]
            return (double)(a[n/2] + a[(n/2)-1]) / 2        

    1,2,4
        3,5,6,7

        1,2,3,4,5,6,7
            4
               
            
    we want middle of both arrays
        if they were merged

    how do we simulate a merge with merging
        [1,2,3]
            [4,5,6]
                3.5

        if both were merged we would take (h1 + l2 / 2) if they were equal
        or if(size1 > size2) h2 or l1

    but can be swapped
        [1,3,4]
            [2,5,6]
                3.5
    now 3 and 4 are in array 1
        answer is in min(arr1, arr2) and max(arr1, arr2)
        1..6

        (m1 + m2)/2 ?
        allow m1 to cross into arr2 and m2 to cross into arr1

    
this approach doesnt work
use partitions

[1 2 | 4]
[3 | 5  6]
        
        
*/ 


double median(vector<int> &arr1, vector<int> &arr2) {

}

/*
Why binary search the smaller array?

    A = 1000 elements
    B = 5 elements
        half = 502

            cutA = 700
            cutB = 502 - 700 = -198

        cutB will be valid
        and searching the smaller array will be faster
            Time = O(log(min(n,m)))

why (total + 1) / 2

    for even
        1 2 | 3 4
        
        median 2

    for odd
        1 2 3 | 4 5

        medican 3

    can 1 formula give both
        take adv of int div

    5+1 / 2 = 3, correct
    4+1 / 2 = 2, correct


correct partition:
    if (leftA <= rightB && leftB <= rightA) {

    if nothing is selected from leftA, intMin allows it to pass validation
    same for leftB

    and likewise int_max for rightB, rightA


return (max(leftA, leftB) + min(rightA, rightB)) / 2.0; // why?
    left side and right side has been partitioned correctly


    1 2      8 9
    3 4 5    6 7

    we want 

    max of left
        max(2,5) = 5
    
    min of right
        min(6,8) = 6

    5 + 6 / 2
*/

double findMedianSortedArrays(vector<int>& A, vector<int>& B) {

    // Always binary search the smaller array
    // why?
    if (A.size() > B.size())
        return findMedianSortedArrays(B, A);

    int n1 = A.size();
    int n2 = B.size();

    int total = n1 + n2;
    int half = (total + 1) / 2; // why?
    

    int l = 0;
    int r = n1;

    while (l <= r) {

        int cutA = l + (r - l) / 2;
        int cutB = half - cutA;
        // cutB = k - cutA; kth largest

        // why?
        int leftA  = (cutA == 0)  ? INT_MIN : A[cutA - 1];
        int rightA = (cutA == n1) ? INT_MAX : A[cutA];

        int leftB  = (cutB == 0)  ? INT_MIN : B[cutB - 1];
        int rightB = (cutB == n2) ? INT_MAX : B[cutB];

        // Correct partition
        if (leftA <= rightB && leftB <= rightA) {

            // return max(leftA,leftB); kth largest

            if (total & 1)
                return max(leftA, leftB);

            return (max(leftA, leftB) + min(rightA, rightB)) / 2.0; // why?
        }

        // Took too many elements from A
        else if (leftA > rightB) {
            r = cutA - 1;
        }

        // Took too few elements from A
        else {
            l = cutA + 1;
        }
    }

    return 0.0; // Never reached for valid input
}

int main() {
    return 0;
}