#include <iostream>
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

int main() {
    return 0;
}